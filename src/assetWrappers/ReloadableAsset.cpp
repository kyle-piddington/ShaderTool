#include "ReloadableAsset.h"
#include "ReloadLocator.h"

ReloadableAsset::ReloadableAsset()
{

}

ReloadableAsset::ReloadableAsset(std::string path)
{
   //Add the asset to the current manager.
   init(path);
}

void ReloadableAsset::init(std::string name)
{
   path = name;
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


