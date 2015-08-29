#include "TestReloadManager.h"

std::vector<ReloadableAsset *> TestReloadManager::assets;
TestReloadManager::TestReloadManager()
{

}
TestReloadManager::~TestReloadManager()
{

}
int TestReloadManager::watchFile(ReloadableAsset * file)
{
   assets.push_back(file);
   return 0;
}
int TestReloadManager::unwatchFile(ReloadableAsset * file)
{
   auto it = std::find(assets.begin(),assets.end(),file);
   if(it != assets.end())
   {
      assets.erase(it);
   }
   return 0;
}
void TestReloadManager::processEvents()
{
   for (std::vector<ReloadableAsset *>::iterator i = assets.begin(); i != assets.end(); ++i)
   {
      (*i)->reload();
   }
}