#ifndef __RELOAD_LOCATOR_H__
#define __RELOAD_LOCATOR_H__
#include "FSLiveReloadManager.h"
#include "NullReloadManager.h"
namespace FileSystem
{
  /**
   * ReloadLocator follows the serviceLocator pattern to provide access to a file system reloader.
   * Reloadlocator will either return a fully featured reloading service, or a placeholder if none have been provided.
   */
   class ReloadLocator
   {
   public:

      static void Initialize();
      /**
       * Retrieve an instance of a service
       * @return a FS service
       */
      static FSLiveReloadManager * getService();
      /**
       * Inject a service into the manager
       * @param service the new service
       */
      static void provide(FSLiveReloadManager* service);

      static void release();
   private:
      static FSLiveReloadManager * service;
      static NullReloadManager nullService;
   };
}
#endif