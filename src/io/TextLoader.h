#ifndef __TEXT_LOADER_H__
#define __TEXT_LOADER_H__
#include <string>
class TextLoader
{
public:
   /**
    * Load a full file into a string
    * This method is meant to be used with small ASCII files, such as shaders.
    * @param 	fileName	the path to the file
    * @return	a string containing the full contents of a file.
    */
   static std::string LoadFullFile(std::string fileName);
};
#endif