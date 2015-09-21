#include <gtest/gtest.h>
#include "Framebuffer.h"

TEST(TestFramebufferCreation, NoAttachmentConfiguration)
{
   Framebuffer buffer(FramebufferConfiguration(10,10));
   EXPECT_TRUE(buffer.isCompleted());
   buffer.deleteFramebuffer();  
}

TEST(TestFramebufferCreation, testDefaultRenderbuffer)
{
   Framebuffer buffer(FramebufferConfiguration::DefaultFramebuffer(10,10));
   EXPECT_TRUE(buffer.isCompleted());
   buffer.deleteFramebuffer();
}



