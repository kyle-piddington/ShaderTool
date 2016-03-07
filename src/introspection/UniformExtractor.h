#ifndef __UNIFORM_EXTRACTOR_H__
#define __UNIFORM_EXTRACTOR_H__
#include <Program.h>
#include <UniformObject.h>
#include <vector>
class UniformExtractor
{

public:
   UniformExtractor();
   ~UniformExtractor();
   std::vector< std::shared_ptr<UniformObject> > extract(GLuint pID);

private:
   void init();
 
   struct UniformTreeBuilder
   {
      std::shared_ptr<UniformObject> obj;
      std::vector<std::shared_ptr < UniformObject > > children;
   };



};
#endif