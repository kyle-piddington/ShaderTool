# ShaderTool Alpha
###  0.1 -- Alpha

ShaderTool is a proposed learning environment for writing, testing, and debugging GLSL shaders. 

ShaderTool Alpha has the following features planned:

  - Loading and linking of a vertex/fragment shader pair.
  - Displaying one model with a render pass.
  - Default models, and support for loading more
  - Ability to load textures, and support for using a framebuffer
  - OpenGL Introspection and automagical uniform binding
  - Error console for OpenGL compiler errors
 
  
ShaderTool (alpha) is designed mostly as a learning tool, and is not currently planned to support multi-pass rendering. However multi-pass rendering remains a high priority feature!

### Version
0.1
### Third Party
Working with OpenGL always includes working with dependencies. ShaderTool uses the following third party extensions.
* [SOIL] - Simple image loading library for handling loading textures.
* [GLEW] - The OpenGL Extentsion Wrangler, used for loading OpenGL's core profiles. Shadertool does not use any extensions.
* [GLFW] - Used for windowing, input and output.
* [GLM] - Simple header-only math library used to handle vectors and matricies.
* [Catch] - Header-only testing library, used for unit testing several parts of the engine.
### Installation

After cloning the repository, run ```./build.sh``` (This is super untested)

### Questions?

Log an issue, or email me at kpidding@calpoly.edu with comments, concerns, questions, or more! 


   [SOIL]: <http://www.lonesock.net/soil.html>
   [GLEW]: <http://glew.sourceforge.net/>
   [GLFW]: <http://www.glfw.org/>
   [GLM]: <http://glm.g-truc.net/0.9.7/index.html>
   [Catch]: <https://github.com/philsquared/Catch>

