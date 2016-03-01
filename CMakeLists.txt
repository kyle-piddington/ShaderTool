cmake_minimum_required (VERSION 3.0)

project (ShaderTool)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g  -O3")


include_directories(include)
add_subdirectory(thirdparty/glfw)

#Get Source variables
include_directories ("${PROJECT_SOURCE_DIR}/lib")

file(GLOB_RECURSE ShaderTool_SOURCES "src/*.cpp" "src/*.cc")

file(GLOB_RECURSE ShaderTool_HEADERS "src/*.h")

#Recursivly include directories
set (ShaderTool_INCLUDE_DIRS "")
foreach (_headerFile ${ShaderTool_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND ShaderTool_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES ShaderTool_INCLUDE_DIRS)
include_directories(${ShaderTool_INCLUDE_DIRS})
#Required flags
#LIB=-DGL_GLEXT_PROTOTYPES -lglut -lGL -lGLU
#LIB_OSX=-framework GLUT -framework OpenGL


FIND_LIBRARY(SOIL_LIB SOIL PATHS lib)
FIND_LIBRARY(GLEW_LIB GLEW PATHS lib)
list(APPEND EXTRA_LIBS ${SOIL_LIB} ${GLEW_LIB})

#Find OpenGL
IF(APPLE)
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
   FIND_LIBRARY(GLUT_LIBRARY GLUT)
   FIND_LIBRARY(CF_LIBRARY CoreFoundation)
   MARK_AS_ADVANCED (OpenGL_LIBRARY
                     GLUT_LIBRARY
                     CF_LIBRARY)
   SET(APPEND EXTRA_LIBS ${OpenGL_LIBRARY} ${CF_LIBRARY})
ELSE()
   FIND_LIBRARY(GL_LIBRARY GL)
   set( CMAKE_CXX_FLAGS "-DGL_GLEXT_PROTOTYPES" )
   SET(EXTRA_LIBS ${GL_LIBRARY} )
ENDIF()

list(REMOVE_ITEM ShaderTool_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(ShaderTool_lib STATIC ${ShaderTool_SOURCES})


#Add C++ 11
add_executable(ShaderTool ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(ShaderTool ShaderTool_lib ${EXTRA_LIBS} glfw)
if (APPLE)
    target_link_libraries(ShaderTool "-framework OpenGL -framework CoreFoundation -framework CoreServices")
endif()

#Copy Resources
add_custom_command(TARGET ShaderTool POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:ShaderTool>/assets)




