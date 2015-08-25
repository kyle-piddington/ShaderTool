#ifndef __AppleLiveReloadManager_H__
#ifdef __APPLE__

#include "FSLiveReloadManager.h"

class AppleReloadManager : public FileSystem::FSLiveReloadManager
{
public:
   AppleReloadManager();
   ~AppleReloadManager();
   virtual int watchFile(const ReloadableAsset * file);
   virtual int unwatchFile(const ReloadableAsset *  file);
   virtual void processEvents();
};
#endif
#endif