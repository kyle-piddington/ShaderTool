#ifdef __APPLE__
#include "AppleLiveReloadManager.h"

AppleReloadManager::AppleReloadManager()
{
   //Register with file system
}

AppleReloadManager::~AppleReloadManager()
{
   //Unregister from file system
}

int AppleReloadManager::watchFile(const ReloadableAsset *  file)
{
   //Add to FS events
   return -1;
}
int AppleReloadManager::unwatchFile(const ReloadableAsset *  file)
{
   //remove from FS events
   return -1;
}
void AppleReloadManager::processEvents()
{
   //Update any changed Reloadables
}
#endif
