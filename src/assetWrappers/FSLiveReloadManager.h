#ifndef __FSLiveReloadManager_H__
#define __FSLiveReloadManager_H__
#include "ReloadableAsset.h"
namespace FileSystem
{
   /**
    * FSLiveReloadManager is the current system's reloading manager.
    * CMake/Ifdefs will compile the platform-dependant C++ file to allow cross platform
    * reloading of assets, with a simple API.
    */
   class FSLiveReloadManager
   {
   public:

      virtual ~FSLiveReloadManager(){};
      /**
       * Add a new file to watch
       * @param  file the asset to watch
       * @return      0 if OK, -1 otherwise
       */
      virtual int watchFile(ReloadableAsset * file) = 0;


      virtual int unwatchFile(ReloadableAsset * file) = 0;


      /**
       * Respond to FS events, and notify the rest of the engine
       */
      virtual void processEvents() = 0;
   private:
   };


}
#endif