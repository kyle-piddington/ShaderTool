#include "Keyboard.h"
#include <GLFW/glfw3.h>
#include <iostream>

enum Keystatus
{
   PRESS = 1,
   HOLD = 2,
   RELEASE = -1
};

short Keyboard::keyStatus[NUM_KEYS] = {RELEASE};
short Keyboard::bfrKeyStatus[NUM_KEYS] = {RELEASE};

bool Keyboard::isKeyDown(int key)
{
   return keyStatus[key] >= PRESS;
}
bool Keyboard::isKeyUp(int key)
{
   return keyStatus[key] == RELEASE;
}
bool Keyboard::key(int key)
{
   return keyStatus[key] == PRESS;
}

void Keyboard::setKeyStatus(int key, int action)
{
   if(action == GLFW_PRESS)
   {
      bfrKeyStatus[key] = PRESS;
   }
   else if(action == GLFW_RELEASE)
   {
      bfrKeyStatus[key] = RELEASE;
   }
}

void Keyboard::update()
{
   for(int i = 0; i < NUM_KEYS; i++)
   {
      if(bfrKeyStatus[i] == PRESS)
      {
         if(keyStatus[i] == PRESS)
         {
            keyStatus[i] = HOLD;
            bfrKeyStatus[i] = HOLD;
         }
         else
         {
            keyStatus[i] = PRESS;
         }
      }
      else if(bfrKeyStatus[i] == RELEASE)
      {
         keyStatus[i] = RELEASE;
      }

   }
}


