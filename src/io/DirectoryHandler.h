#ifndef __DIRECTORY_HANDLER_H__
#define __DIRECTORY_HANDLER_H__
#include <vector>
struct DirectoryHandler
{
   /**
    * Return a series of paths of files in a directory,
    * without the . and .. entries.
    */
   static std::vector<std::string> listDirectory(std::string directory);

   static std::vector<std::string> listDirectory(std::string directory, std::string extension);
};
#endif