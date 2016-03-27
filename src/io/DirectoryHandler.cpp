#include "DirectoryHandler.h"
#include <dirent.h>
#include <string>
#include <iostream>
#include <easyLogging++.h>

bool extensionMatches(std::string fName, std::string extension)
{
   bool matches = true;
   if(fName.size() > extension.size())
   {
      for(int i = 0; i < extension.size(); i++)
      {
         matches &= fName[fName.size() - extension.size() + i] == extension[i];
      }
   }
   else
   {
      matches = false;
   }
   return matches;

}

std::vector<std::string> DirectoryHandler::listDirectory(std::string directory, std::string extension)
{
   DIR * dir;
   struct dirent * ent;
   bool checkExn = extension.size() > 0;
   std::vector<std::string> paths;
   if((dir = opendir(directory.c_str())) != NULL)
   {
      while((ent = readdir(dir)) != NULL)
      {
         std::string fName = std::string(ent->d_name);
         if(fName != "." && fName != "..")
         {
            if(!checkExn || extensionMatches(fName, extension))
            {
               paths.push_back(fName);
            }
         }
      }
      closedir(dir);
   }
   else
   {
      LOG(ERROR) << "Could not open directory " + directory;
   }
   return paths;

}
std::vector<std::string> DirectoryHandler::listDirectory(std::string directory)
{
   return DirectoryHandler::listDirectory(directory, std::string());

}