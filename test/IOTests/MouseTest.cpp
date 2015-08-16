#include <gtest/gtest.h>
#include <Mouse.h>
#include <GLFW/glfw3.h>
TEST(Mouse,testPress)
{
   Mouse::setButtonStatus(5,GLFW_PRESS);
   Mouse::update();
   EXPECT_EQ(Mouse::pressed(5),true);
   EXPECT_EQ(Mouse::clicked(5),true);
   Mouse::update();
   EXPECT_EQ(Mouse::pressed(5),true);
   EXPECT_EQ(Mouse::clicked(5),false);
   Mouse::setButtonStatus(5,GLFW_RELEASE);
   Mouse::update();
   EXPECT_EQ(Mouse::pressed(5),false);
   EXPECT_EQ(Mouse::clicked(5),false);
   EXPECT_EQ(Mouse::released(5),true);
}


TEST(Mouse, testPosition)
{
   Mouse::updateMousePos(10,20);
   EXPECT_EQ(0,Mouse::getLastX());
   EXPECT_EQ(0,Mouse::getLastY());
   EXPECT_EQ(10,Mouse::getX());
   EXPECT_EQ(20,Mouse::getY());
   Mouse::updateMousePos(20,30);
   EXPECT_EQ(10,Mouse::getLastX());
   EXPECT_EQ(20,Mouse::getLastY());
   EXPECT_EQ(20,Mouse::getX());
   EXPECT_EQ(30,Mouse::getY());
   
}