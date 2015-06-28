#include "TextLoader.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <easylogging++.h>
std::string TextLoader::LoadFullFile(std::string fileName)
{
   std::ifstream inputStr(fileName);
   std::string str = "";
   if(inputStr)
   {

      inputStr.seekg(0, std::ios::end);   
      str.reserve(inputStr.tellg());
      inputStr.seekg(0, std::ios::beg);

      str.assign((std::istreambuf_iterator<char>(inputStr)),
               std::istreambuf_iterator<char>());
      inputStr.close();
   }
   else
   {
      LOG(ERROR) << "Could not load file "  << fileName;
   }
   return str;
}