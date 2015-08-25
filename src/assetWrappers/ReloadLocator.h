#ifndef __RELOAD_LOCATOR_H__
#define __RELOAD_LOCATOR_H__
#include "FSLiveReloadManager.h"
#include "NullReloadManager.h"
namespace FileSystem
{
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