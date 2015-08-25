#include "ReloadLocator.h"

namespace FileSystem
{
   FSLiveReloadManager * ReloadLocator::service;
   NullReloadManager ReloadLocator::nullService;
  
   void ReloadLocator::Initialize()
   {
      service = &nullService;
   }
   FSLiveReloadManager * ReloadLocator::getService()
   {
      return service;
   }
         /**
          * Inject a service into the manager
          * @param service the new service
          */
   void ReloadLocator::provide(FSLiveReloadManager* injectedService)
   {
      if(injectedService == NULL)
      {
         service = &nullService;
      }
      else
      {
         service = injectedService;
      }
   }

   void ReloadLocator::release()
   {
      if(service != nullptr){
         delete service;
      }
      
   }
}
