#ifndef __RELOADABLE_ASSET_H__
#define __RELOADABLE_ASSET_H__ value
#include <string>
class ReloadableAsset
{
   public:
      ReloadableAsset(std::string path); //Construct a new asset
      virtual ~ReloadableAsset() = 0;
      virtual void reload() = 0; //Reload this asset
      virtual std::string getPath() const;
   private:
      std::string path;
};

#endif