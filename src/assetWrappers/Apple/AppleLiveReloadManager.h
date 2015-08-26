#ifndef __AppleLiveReloadManager_H__
#ifdef __APPLE__

#include "FSLiveReloadManager.h"
#include <CoreServices/CoreServices.h>
#include <vector>
#include <unordered_map>
class AppleReloadManager : public FileSystem::FSLiveReloadManager
{
public:
   AppleReloadManager();
   ~AppleReloadManager();
   virtual int watchFile( ReloadableAsset * file);
   virtual int unwatchFile( ReloadableAsset *  file);
   virtual void processEvents();
private:
   static void eventCallback(
      ConstFSEventStreamRef streamRef,
       void *clientCallBackInfo,
       size_t numEvents,
       void *eventPaths,
       const FSEventStreamEventFlags eventFlags[],
       const FSEventStreamEventId eventIds[]
    );
   FSEventStreamRef stream;
   static std::vector<std::string> pathsToReload;
   std::unordered_map<std::string, ReloadableAsset *  > assetMap;
   static pthread_mutex_t reloadMutex;
};
#endif
#endif