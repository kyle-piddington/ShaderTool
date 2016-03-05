#ifndef __STRUCT_UNIFORM_OBJECT__
#define __STRUCT_UNIFORM_OBJECT__

#include "UniformObject.h"
#include <unordered_map>
/**
 * The Struct uniform object is used to hold multiple uniform objects.
 * The struct object can be queried by name.
 */
class StructUniformObject : public UniformObject
{
public:
   StructUniformObject(std::string name);

   /**
    * Retrieve an element from a struct uniform Object
    * @param  id  name of the member
    * @return    Uniform object if valid.
    */
   virtual const UniformObject & get(std::string id) const;
   /**
    * Retrieve an element from an array Uniform Object
    * @param  id the idx in the array
    * @return    Uniform object if valid
    * @throw GLSLTypeError if this object is not an array.
    */
   virtual const UniformObject & get(int id) const
   {
     throw GLSLType::GLSLIndexException("Attempting to index struct uniform object.");
   }

   /**
    * Add a uniform object to this struct.
    * @param obj the object to add.
    */
   void addUniformObject(std::shared_ptr<UniformObject> obj);


private:
   std::unordered_map<std::string, std::shared_ptr<UniformObject> > attributes;


};
#endif