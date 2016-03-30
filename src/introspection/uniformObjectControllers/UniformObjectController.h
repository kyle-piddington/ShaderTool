#ifndef __UniformObjectController_H__
#define __UniformObjectController_H__
#include "UniformObject.h"
/**
 * Provide access to query, control, and reload uniform objects
 */
class UniformObjectController
{
public:

   UniformObjectController(std::shared_ptr<UniformObject> object);
   virtual ~UniformObjectController();
   UniformObjectController(const UniformObjectController & other);
   /**
    * Uniform objects are considered equal if the name and type of a
    * shared object is equal.
    */
   virtual bool operator== (const UniformObjectController & other) const;
   const std::string & getName() const ;
   GLSLType::GLSLType getType() const;

   void assignObject(std::shared_ptr<UniformObject> object)
   {
      this->object = object;
   }

   virtual void refresh()
   {
   }

   template <class T>
   void bind(const T value)
   {
      object->bind(value);
   }

private:
   std::shared_ptr<UniformObject> object;


};
#endif