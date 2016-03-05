#ifndef __UNIFORM_OBJECT_H__
#define __UNIFORM_OBJECT_H__
#include "GLSLType.h"
#include <glm/glm.hpp>

class UniformObject
{
private:
   friend class Program;
   std::string name;
   GLint id;
   GLSLType::GLSLType type;

   void throwTypeError(std::string givenType) const;
      //Protected setID method allows Program to update the id on a rebind, without changing the type.
      //This method is protected to discourage manually setting the ID's
   void setID(int i);
public:

   UniformObject():
   id(-1),
   name("Invald"),
   type(GLSLType::GLSLInvalidType)
   {

   }
   UniformObject(std::string name, GLSLType::GLSLType t, GLint id = -1):
   id(id),
   name(name),
   type(t)
   {

   }

   static UniformObject InvalidObject;

   GLint getID() const;

   void bind(int i) const;
   void bind(float f) const;
   void bind(bool b) const;
   void bind(double d) const;
   void bind(const glm::vec2 & v) const;
   void bind(const glm::vec3 & v) const;
   void bind(const glm::vec4 & v) const;
   void bind(const glm::mat2 & m) const;
   void bind(const glm::mat3 & m) const;
   void bind(const glm::mat4 & m) const;


   /*Some Uniform objects are sub-queriable. Subclasses will take care of querying*/
   /**
    * Retrieve an element from aa struct uniform Object
    * @param  id  name of the member
    * @return    Uniform object if valid.
    */
   virtual const UniformObject & get(std::string id) const
   {
      throw GLSLType::GLSLIndexException("Attempting to index plain simple data");
   }
   /**
    * Retrieve an element from an array Uniform Object
    * @param  id the idx in the array
    * @return    Uniform object if valid
    * @throw GLSLTypeError if this object is not an array.
    */
   virtual const UniformObject & get(int id) const
   {
     throw GLSLType::GLSLIndexException("Attempting to index plain simple data");
   }

   virtual const UniformObject & operator[](int id) const
   {
      return get(id);
   }

   virtual const UniformObject & operator[](std::string id) const
   {
      return get(id);
   }

   /**
    * See if this uniform is valid;
    * @return true if valid.
   */
   bool isValid() const;

   /**
    * See if this uniform object represents an array
    * @return true if the object is an array
    */
   bool isArray() const;
   /**
    * See if this uniform object represents a struct.
    * @return true if the object is a struct.
    */
   bool isStruct() const;

   /**
    * Get the name of this unifrom
    */
   const std::string & getName()
   {
      return name;
   }
};
#endif

