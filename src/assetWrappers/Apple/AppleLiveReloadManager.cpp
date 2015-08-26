#ifdef __APPLE__
#include "AppleLiveReloadManager.h"
#include <easyLogging++.h>
#include <CoreFoundation/CoreFoundation.h>
#include <stdlib.h> 
std::vector<std::string> AppleReloadManager::pathsToReload;
pthread_mutex_t AppleReloadManager::reloadMutex;

void AppleReloadManager::eventCallback( 
    ConstFSEventStreamRef streamRef,
    void *clientCallBackInfo,
    size_t numEvents,
    void *eventPaths,
    const FSEventStreamEventFlags eventFlags[],
    const FSEventStreamEventId eventIds[])
{
   int i;
   char **paths = (char**) eventPaths;
   {
      for (i=0; i<numEvents; i++)
      {

         pathsToReload.push_back(std::string(paths[i]));
      }
   }
}     

AppleReloadManager::AppleReloadManager()
{
   //Register with file system

    CFStringRef mypath = CFSTR("assets");
    CFArrayRef pathsToWatch = CFArrayCreate(NULL, (const void **)&mypath, 1, NULL);
    FSEventStreamContext  *callbackInfo = NULL; // could put stream-specific data here.
    auto myCallbackFunction = AppleReloadManager::eventCallback;
    CFAbsoluteTime latency = 3.0; /* Latency in seconds */
    /* Create the stream, passing in a callback */
    stream = FSEventStreamCreate(NULL,
        myCallbackFunction,
        callbackInfo,
        pathsToWatch,
        kFSEventStreamEventIdSinceNow, /* Or a previous event ID */
        latency,
        kFSEventStreamCreateFlagFileEvents /* Flags explained in reference */
    );
   FSEventStreamScheduleWithRunLoop(stream, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
   FSEventStreamStart(stream);
   pthread_mutex_init(&AppleReloadManager::reloadMutex, NULL);
}

AppleReloadManager::~AppleReloadManager()
{
   //Unregister from file system
   FSEventStreamStop(stream);
   FSEventStreamUnscheduleFromRunLoop(stream,CFRunLoopGetCurrent(),kCFRunLoopDefaultMode);
   FSEventStreamInvalidate(stream);
   FSEventStreamRelease(stream);

   //Destory the lock
   pthread_mutex_destroy(&AppleReloadManager::reloadMutex);
}

int AppleReloadManager::watchFile(ReloadableAsset *  file)
{
   char resolved_path[PATH_MAX];
   realpath(file->getPath().c_str(),resolved_path);
   std::string stringPath(resolved_path);
   if(assetMap.find(stringPath) == assetMap.end())
   {
      assetMap[stringPath] = file;
      LOG(INFO) << "Apple reloading now watching " << stringPath;
   }
   else
   {
      LOG(WARNING) << "Tried to watch " << file->getPath() << " twice, check your resource managers!";
   }
   return 0;
}
int AppleReloadManager::unwatchFile(ReloadableAsset *  file)
{
   char resolved_path[PATH_MAX];
   realpath(file->getPath().c_str(),resolved_path);
   std::string stringPath(resolved_path);
  
   if(assetMap.find(stringPath) == assetMap.end())
   {

      LOG(WARNING) << "Tried to remove " << stringPath << " but was never watching";
   }
   else
   {
      assetMap.erase(file->getPath());
   }
   return 0;
}
void AppleReloadManager::processEvents()
{
   if(pathsToReload.size() > 0)
   {
      std::vector<std::string> reloadedFiles = pathsToReload;
      //Lock and unlock here
      pthread_mutex_lock(&AppleReloadManager::reloadMutex);
      pathsToReload.clear();
      pthread_mutex_unlock(&AppleReloadManager::reloadMutex);
      //Update any changed Reloadables
      for (std::vector<std::string>::iterator i = reloadedFiles.begin(); i != reloadedFiles.end(); ++i)
      {
         LOG(INFO) << "Trying to reload asset " << *i;
         if(assetMap.find(*i) != assetMap.end())
         {
            LOG(INFO) << "Reloading asset " << *i;
            assetMap[*i]->reload();
         }


      }
   }
}
#endif
