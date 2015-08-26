#ifndef __NullReloadManager_H__
#define __NullReloadManager_H__
#include "FSLiveReloadManager.h"

class NullReloadManager : public FileSystem::FSLiveReloadManager
{
public:
   NullReloadManager();
   ~NullReloadManager();
   virtual int watchFile( ReloadableAsset *  file);
   virtual int unwatchFile(ReloadableAsset *  file);
   virtual void processEvents();
};
#endif
