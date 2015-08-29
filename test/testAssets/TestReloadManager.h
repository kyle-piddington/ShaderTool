#ifndef __TEST_RELOAD_MANAGER_H_
#define __TEST_RELOAD_MANAGER_H_

/**
 * Test Reload manager will always cause watched files to reload on
 * process events
 */

#include <vector>
#include "FSLiveReloadManager.h"

class TestReloadManager : public FileSystem::FSLiveReloadManager{
public:
   TestReloadManager();
   ~TestReloadManager();
   virtual int watchFile( ReloadableAsset * file);
   virtual int unwatchFile( ReloadableAsset *  file);
   virtual void processEvents();

private:
   static std::vector<ReloadableAsset *> assets;


};
#endif