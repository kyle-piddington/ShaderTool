#ifndef __FILE_UTILS_H___
#define __FILE_UTILS_H___
struct FileUtils
{
   static bool fExists(std::string fileName)
   {
      std::ifstream infile(fileName);
      bool exists= infile.good();
      infile.close();
      return exists;
   }
};
#endif