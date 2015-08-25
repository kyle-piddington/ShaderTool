#include "ReloadableAsset.h"
#include "ReloadLocator.h"

ReloadableAsset::ReloadableAsset(std::string path):
path(path)
{
   //Add the asset to the current manager.
   FileSystem::ReloadLocator::getService()->watchFile(this);
}
ReloadableAsset::~ReloadableAsset()
{
   FileSystem::ReloadLocator::getService()->unwatchFile(this);
}

std::string ReloadableAsset::getPath() const
{
   return path;
}


