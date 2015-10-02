#include "PingPongFrameBuffer.h"
#include <stdio.h>
PingPongFramebuffer::PingPongFramebuffer():
isBuffer1Active(true)
{

}

PingPongFramebuffer::PingPongFramebuffer(FramebufferConfiguration config) :
isBuffer1Active(true)
{
   init(config);
}

void PingPongFramebuffer::init(FramebufferConfiguration config)
{
   buffer1.init(config);
   buffer2.init(config);
}

Framebuffer & PingPongFramebuffer::getActiveBuffer()
{
 
   return isBuffer1Active ? buffer1 : buffer2;
}

Framebuffer & PingPongFramebuffer::getPassiveBuffer()
{
   return isBuffer1Active ? buffer2 : buffer1;
}
void PingPongFramebuffer::swap()
{
   isBuffer1Active = !isBuffer1Active;
}