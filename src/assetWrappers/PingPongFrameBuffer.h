#ifndef __PINGPONG_BUFFER_H_
#define __PINGPONG_BUFFER_H_
#include "Framebuffer.h"
/**
 * Create a swappable framebuffer
 */
class PingPongFramebuffer
{
public:
   PingPongFramebuffer();
   PingPongFramebuffer(FramebufferConfiguration config);

   void init(FramebufferConfiguration config);

   Framebuffer & getActiveBuffer();
   Framebuffer & getPassiveBuffer();
   void swap();

private:
   Framebuffer buffer1;
   Framebuffer buffer2;

   bool isBuffer1Active;

};
#endif