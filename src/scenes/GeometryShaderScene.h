#include "VertexArrayObject.h"

#include "EmptyScene.h"

class GeometryShaderScene : public EmptyScene
{
public:
   GeometryShaderScene(Context * ctx);
   void initPrograms();
   void initialBind();
   void render();
private:
   Program * geomProgram;
   VertexArrayObject vao;
};