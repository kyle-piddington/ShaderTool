#include <gtest/gtest.h>
#include <Keyboard.h>
#include <GLFW/glfw3.h>
TEST(Keyboard,testPress)
{
   Keyboard::setKeyStatus(5,GLFW_PRESS);
   Keyboard::update();
   EXPECT_EQ(Keyboard::isKeyDown(5),true);
   EXPECT_EQ(Keyboard::key(5),true);
   Keyboard::update();
   EXPECT_EQ(Keyboard::isKeyDown(5),true);
   EXPECT_EQ(Keyboard::key(5),false);
   Keyboard::setKeyStatus(5,GLFW_RELEASE);
   Keyboard::update();
   EXPECT_EQ(Keyboard::isKeyDown(5),false);
   EXPECT_EQ(Keyboard::key(5),false);
   EXPECT_EQ(Keyboard::isKeyUp(5),true);

}

