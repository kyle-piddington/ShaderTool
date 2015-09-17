#include "Cube.h"
#include "Vertex.h"

#define cubeSize 0.5

Cube::Cube()
{
   float side = 1.0f;
   float side2 = side / 2.0f;

   float v[24*8] = {
        // Front
       -side2, -side2, side2, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        side2, -side2, side2, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        side2,  side2, side2, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
       -side2,  side2, side2, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

       // Right
        side2, -side2, side2,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        side2, -side2, -side2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        side2,  side2, -side2, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        side2,  side2, side2,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
       // Back
       -side2, -side2, -side2,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
       -side2,  side2, -side2,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        side2,  side2, -side2,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        side2, -side2, -side2,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
       // Left
       -side2, -side2, side2,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
       -side2,  side2, side2,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
       -side2,  side2, -side2, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
       -side2, -side2, -side2, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
       // Bottom
       -side2, -side2, side2,   0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
       -side2, -side2, -side2,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        side2, -side2, -side2,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        side2, -side2, side2,   0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
       // Top
       -side2,  side2, side2,    0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        side2,  side2, side2,    0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        side2,  side2, -side2,   0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
       -side2,  side2, -side2,   0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };



    GLuint el[] = {
        0,1,2,0,2,3,
        4,5,6,4,6,7,
        8,9,10,8,10,11,
        12,13,14,12,14,15,
        16,17,18,16,18,19,
        20,21,22,20,22,23
    };


   bufferData.setData(v,24*8);
   ElementBufferObject ebo;
   ebo.setData(el,36);
   cubeVao.addAttribute(0,bufferData,  8 *sizeof(float));
   cubeVao.addAttribute(1,bufferData,  8 * sizeof(float), 3 * sizeof(float));
   cubeVao.addAttribute(2, bufferData, 8 * sizeof(float), 6 * sizeof(float),2);
   cubeVao.addElementArray(ebo);
   numInds = ebo.getNumIndicies();

}

Cube::~Cube()
{
}

void Cube::render()
{
   cubeVao.bind();
   glDrawElements(GL_TRIANGLES, numInds, GL_UNSIGNED_INT, 0);
   cubeVao.unbind();

}