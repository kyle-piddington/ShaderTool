#ifndef __ERR_SCENE_H__
#define __ERR_SCENE_H__

#include "Texture2D.h"
#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "ElementBufferObject.h"
#include "EmptyScene.h"
class ErrorScene : public EmptyScene
{
public:
   ErrorScene();
   /**
    * Compile all needed programs, and return true if successful
    * @return 
    */
   virtual void initPrograms();
   virtual void initialBind();
   virtual void render();
   virtual void cleanup();

private:
   Program * errProgram;
   Texture2D errTexture;
   VertexArrayObject errVAO;
   //I really dislike leaving these out for grabs...
   VertexBuffer vbo;
   ElementBufferObject ebo;



};
#endif