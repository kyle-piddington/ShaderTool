cmake_minimum_required (VERSION 3.0)

project (GraphicsEngine)
enable_testing()


#Get Source variables
include_directories ("${PROJECT_SOURCE_DIR}/lib")
SET( EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}" )
IF( NOT EIGEN3_INCLUDE_DIR )
    MESSAGE( FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
ENDIF()
INCLUDE_DIRECTORIES ( "${EIGEN3_INCLUDE_DIR}" )
INCLUDE_DIRECTORIES ( "${PROJECT_SOURCE_DIR}/include" )

file(GLOB_RECURSE GraphicsEngine_SOURCES "src/*.cpp" "src/*.cc")

file(GLOB_RECURSE GraphicsEngine_HEADERS "src/*.h")

#Recursivly include directories
set (GraphicsEngine_INCLUDE_DIRS "")
foreach (_headerFile ${GraphicsEngine_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND GraphicsEngine_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES GraphicsEngine_INCLUDE_DIRS)
include_directories(${GraphicsEngine_INCLUDE_DIRS})
#Required flags
#LIB=-DGL_GLEXT_PROTOTYPES -lglut -lGL -lGLU
#LIB_OSX=-framework GLUT -framework OpenGL

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS})


FIND_LIBRARY(GLEW_LIB GLEW)
FIND_LIBRARY(SOIL_LIB SOIL)
list(APPEND EXTRA_LIBS ${GLFW_LIBRARIES} ${GLEW_LIB} ${SOIL_LIB})

IF(APPLE)
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
   FIND_LIBRARY(GLUT_LIBRARY GLUT)
   FIND_LIBRARY(CF_LIBRARY CoreFoundation)
   MARK_AS_ADVANCED (OpenGL_LIBRARY
                     GLUT_LIBRARY
                     CF_LIBRARY)
   SET(APPEND EXTRA_LIBS ${OpenGL_LIBRARY} ${GLUT_LIBRARY} ${CF_LIBRARY})

ELSE()
   FIND_LIBRARY(GL_LIBRARY GL)
   FIND_LIBRARY(GLU_LIBRARY GLU)
   set( CMAKE_CXX_FLAGS "-DGL_GLEXT_PROTOTYPES" )
   SET(EXTRA_LIBS ${GLUT_LIBRARY} ${GL_LIBRARY} ${GLU_LIBRARY})
ENDIF()


#GoogleTest Support
add_subdirectory("lib/gtest")

SET(GraphicsEngine_Test_SOURCES ${GraphicsEngine_SOURCES})
list(REMOVE_ITEM GraphicsEngine_Test_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}) 
set(GraphicsEngine_Test GraphicsEngine_test)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE TEST_SRC_FILES "test/*.cpp")



add_executable(${GraphicsEngine_Test} ${GraphicsEngine_Test_SOURCES} ${TEST_SRC_FILES})
if (APPLE)
  target_link_libraries(${GraphicsEngine_Test} "-framework OpenGL -framework CoreFoundation")
endif()

target_link_libraries(${GraphicsEngine_Test} ${EXTRA_LIBS} gtest)
add_test( ${GraphicsEngine_Test} ${GraphicsEngine_Test} )

#Add C++ 11
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g ")
add_executable (GraphicsEngine ${GraphicsEngine_SOURCES})
target_link_libraries(GraphicsEngine ${EXTRA_LIBS})

if (APPLE)
  target_link_libraries(GraphicsEngine "-framework OpenGL -framework CoreFoundation")
endif()




