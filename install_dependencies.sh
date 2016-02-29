#/bin/bash
#Download the latest versions of GLEW, GLFW, and SOIL
CDIR=$(pwd)
if [ ! -d lib ] ; then
	mkdir lib
fi

if [ ! -d include ] ; then
	mkdir include
fi
if [ ! -d thirdparty ] ; then
	mkdir thirdparty
fi

if [ ! -d thirdparty/soil ] ; then 
   wget http://www.lonesock.net/files/soil.zip -O thirdparty/soil.zip
   unzip thirdparty/soil.zip -d thirdparty/soil
   rm thirdparty/soil.zip
   mkdir thirdparty/soil/Simple\ OpenGL\ Image\ Library/projects/makefile/obj
   make -C thirdparty/soil/Simple\ OpenGL\ Image\ Library/projects/makefile
   ln -s thirdparty/soil/Simple\ OpenGL\ Image\ Library/lib/libSOIL.a lib/libSOIL.a
   if [ ! -d include/SOIL ] ; then 
   	mkdir include/SOIL
   fi
   ln -s $CDIR/thirdparty/soil/Simple\ OpenGL\ Image\ Library/src/SOIL.h include/SOIL/SOIL.h
fi
   
if [ ! -d thirdparty/glew ] ; then
   git clone https://github.com/nigels-com/glew.git thirdparty/glew
   make -C thirdparty/glew extensions
   make -C thirdparty/glew 
   ln -s   $PATH/thirdparty/glew/lib/libGLEW.a lib/libGLEW.a
   ln -s   $PATH/thirdparty/glew/include/GL include/GL
fi

if [ ! -d thirdparty/glfw ] ; then
   git clone https://github.com/glfw/glfw.git thirdparty/glfw
fi

if [ ! -d thirdparty/glm ] ; then
   git clone https://github.com/g-truc/glm.git thirdparty/glm
   ln -s $CDIR/thirdparty/glm/glm include/glm
fi

