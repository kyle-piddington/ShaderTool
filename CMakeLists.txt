cmake_minimum_required (VERSION 3.0)

project (GraphicsEngine)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O3")
option(test "Build all tests." ON) # Makes boolean 'test' available.


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

FIND_LIBRARY(GLFW3_LIB glfw3)
FIND_LIBRARY(GLEW_LIB GLEW)
FIND_LIBRARY(SOIL_LIB SOIL)
FIND_LIBRARY(ASSIMP_LIB assimp)
list(APPEND EXTRA_LIBS ${GLFW_LIBRARIES} ${ASSIMP_LIB} ${GLEW_LIB} ${SOIL_LIB} ${GLFW3_LIB})

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

list(REMOVE_ITEM GraphicsEngine_SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_library(GraphicsEngine_lib ${GraphicsEngine_SOURCES})
#Add C++ 11
add_executable(GraphicsEngine ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(GraphicsEngine GraphicsEngine_lib)
target_link_libraries(GraphicsEngine ${EXTRA_LIBS})
if (APPLE)
    target_link_libraries(GraphicsEngine "-framework OpenGL -framework CoreFoundation -framework CoreServices")
endif()



if (test)
  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(lib/gtest)

  enable_testing()
  file(GLOB_RECURSE TEST_SRC_FILES "test/*.cpp")

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


  ##############
  # Unit Tests
  ##############
  #Gather all unit tests.
  file(GLOB_RECURSE TEST_SRC_FILES "test/*.cpp")

  #Add tests to the executable
  add_executable(GraphicsEngine_test ${PROJECT_SOURCE_DIR}/test/main.cpp ${TEST_SRC_FILES})

  # Standard linking to gtest executables (If you want to use GoogleTests's prebuilt main file).
  target_link_libraries(GraphicsEngine_test gtest)

  # Extra linking for the project.
  target_link_libraries(GraphicsEngine_test GraphicsEngine_lib)
  target_link_libraries(GraphicsEngine_test ${EXTRA_LIBS})

  #Add apple libs
  if (APPLE)
    target_link_libraries(GraphicsEngine_test "-framework OpenGL -framework CoreFoundation -framework CoreServices")
  endif()



endif()




