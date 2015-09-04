#ifndef __NullReloadManager_H__
#define __NullReloadManager_H__
#include "FSLiveReloadManager.h"
/**
 * NullReloadManager serves as an empty reloader when no service has been located. (AKA I haven't written one yet)
 * The reload manager will still run functions fine, but will not reload any assets.
 */
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
