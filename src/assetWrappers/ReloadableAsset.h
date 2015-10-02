#ifndef __RELOADABLE_ASSET_H__
#define __RELOADABLE_ASSET_H__ value
#include <string>
/**
 * The reloadableAsset interface allows assets to be reloaded when any change occurs. 
 * Any changes to the assets will cause a reload, effectivly allowing live editing to occur.
 */
class ReloadableAsset
{
   public:
      //Construct an asset, without binding a name
      ReloadableAsset();
      ReloadableAsset(std::string path); //Construct a new asset
      void init(std::string path);
      virtual ~ReloadableAsset() = 0;
      virtual void reload() = 0; //Reload this asset
      virtual std::string getPath() const;
   private:
      std::string path;
};

#endif