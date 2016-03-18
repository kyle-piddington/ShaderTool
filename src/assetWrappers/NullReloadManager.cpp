#include "NullReloadManager.h"
#include <easylogging++.h>
NullReloadManager::NullReloadManager()
{

}
NullReloadManager::~NullReloadManager()
{

}
int NullReloadManager::watchFile(ReloadableAsset *  file)
{
   LOG(INFO) << "No live reloading service provided, asset '" << file->getPath() << "' will not reload";
   return 0;
}
int NullReloadManager::unwatchFile(ReloadableAsset *  file)
{
   return 0;
}
void NullReloadManager::processEvents()
{
   
}