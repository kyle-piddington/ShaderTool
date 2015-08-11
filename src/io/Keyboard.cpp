#include "Keyboard.h"
#include <GLFW/glfw3.h>

char Keyboard::keyStatus[NUM_KEYS];
char Keyboard::bfrKeyStatus[NUM_KEYS];

bool Keyboard::isKeyDown(int key)
{
   return keyStatus[key] > 0;
}
bool Keyboard::isKeyUp(int key)
{
   return keyStatus[key] == 0;
}
bool Keyboard::key(int key)
{
   return keyStatus[key] == 1;
}

void Keyboard::setKeyStatus(int key, int action)
{
   if(action == GLFW_PRESS)
   {
      bfrKeyStatus[key] = 1;
   }
   else if(action == GLFW_RELEASE)
   {
      bfrKeyStatus[key] = 0;
   }
}

void Keyboard::update()
{
   for(int i = 0; i < NUM_KEYS; i++)
   {
      if(bfrKeyStatus[i] == 1)
      {
         if(keyStatus[i] == 1)
         {
            keyStatus[i] = 2;
         }
         else
         {
            keyStatus[i] = 1;
         }
      }
      else
      {
         keyStatus[i] = 0;
      }
   }
}


