#ifndef __ARRAY_UNIFORM_OBJECT_H__
#define __ARRAY_UNIFORM_OBJECT_H__

#include "UniformObject.h"
#include <vector>
/**
 * The Struct uniform object is used to hold multiple uniform objects.
 * The struct object can be queried by name.
 */
class ArrayUniformObject : public UniformObject
{
public:
   ArrayUniformObject(std::string name, const std::vector< std::shared_ptr<UniformObject> > & arrayObjects);

   /**
    * Retrieve an element from an array uniform Object
    * @param  id  name of the member
    * @return    Uniform object if valid.
    */
   virtual const UniformObject & get(std::string id) const
   {
      throw GLSLType::GLSLIndexException("Attemting to use string indexing on an array");
   }
   /**
    * Retrieve an element from an array Uniform Object
    * @param  id the idx in the array
    * @return    Uniform object if valid
    * @throw GLSLTypeError if this object is not an array.
    */
   virtual const UniformObject & get(int id) const;

   /** 
    * Get the size of the uniform array.
    * @return the size.
    */
   int size() const;



private:
   std::vector< std::shared_ptr<UniformObject> > elements;


};
#endif