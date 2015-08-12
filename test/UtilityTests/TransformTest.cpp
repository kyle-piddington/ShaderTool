#include <gtest/gtest.h>
#include <Keyboard.h>
#include <Transform.h>
TEST(Transform,translate)
{
   Transform t;
   t.setPosition(glm::vec3(1.0,2.0,3.0));
   EXPECT_EQ(t.getPosition().x,1.0);
   EXPECT_EQ(t.getPosition().y,2.0);
   EXPECT_EQ(t.getPosition().z,3.0);
   t.translate(glm::vec3(1.0,2.0,3.0));
   EXPECT_EQ(t.getPosition().x,2.0);
   EXPECT_EQ(t.getPosition().y,4.0);
   EXPECT_EQ(t.getPosition().z,6.0);

}
TEST(Transform,transformApplicationOrder)
{
   Transform t;
   t.setPosition(glm::vec3(1.0,2.0,3.0));
   t.setRotation(glm::vec3(M_PI,M_PI/4,M_PI/8));
   glm::vec4 vec(0.0,0.0,0.0,1.0);
   glm::vec4 nextVec =  t.getMatrix() * vec;
   EXPECT_EQ(1.0,nextVec.x);
   EXPECT_EQ(2.0,nextVec.y);
   EXPECT_EQ(3.0,nextVec.z);
}

TEST(Transform,basicRotation)
{
   Transform t;
   t.setRotation(glm::vec3(M_PI,0,0));
   EXPECT_NEAR(glm::vec3(0.0,0.0,1.0).x,t.forward().x,1.0e-6);
   EXPECT_NEAR(glm::vec3(0.0,0.0,1.0).y,t.forward().y,1.0e-6);
   EXPECT_NEAR(glm::vec3(0.0,0.0,1.0).z,t.forward().z,1.0e-6);

   t.rotate(glm::vec3(M_PI,0,0));
   EXPECT_NEAR(glm::vec3(0.0,0.0,-1.0).x,t.forward().x,1.0e-6);
   EXPECT_NEAR(glm::vec3(0.0,0.0,-1.0).y,t.forward().y,1.0e-6);
   EXPECT_NEAR(glm::vec3(0.0,0.0,-1.0).z,t.forward().z,1.0e-6);

}

TEST(Transform, angleAxis)
{
   Transform t;
   t.setRotation(M_PI/2.0,glm::vec3(0.0,1.0,0.0));
   EXPECT_NEAR(glm::vec3(-1.0,0.0,0.0).x,t.forward().x,1.0e-6);
   EXPECT_NEAR(glm::vec3(-1.0,0.0,0.0).y,t.forward().y,1.0e-6);
   EXPECT_NEAR(glm::vec3(-1.0,0.0,0.0).z,t.forward().z,1.0e-6);

   EXPECT_NEAR(glm::vec3(0.0,1.0,0.0).x,t.up().x,1.0e-6);
   EXPECT_NEAR(glm::vec3(0.0,1.0,0.0).y,t.up().y,1.0e-6);
   EXPECT_NEAR(glm::vec3(0.0,1.0,0.0).z,t.up().z,1.0e-6);

   t.rotate(M_PI/2.0,t.forward());

   EXPECT_NEAR(glm::vec3(0.0,0.0,1.0).x,t.up().x,1.0e-6);
   EXPECT_NEAR(glm::vec3(0.0,0.0,1.0).y,t.up().y,1.0e-6);
   EXPECT_NEAR(glm::vec3(0.0,0.0,1.0).z,t.up().z,1.0e-6);
}

TEST(Transform, lookAt)
{
   Transform t;
   t.setPosition(glm::vec3(2,4,6));
   t.lookAt(glm::vec3(1,2,3));
   glm::vec3 expectedFw = glm::normalize(glm::vec3(1,2,3)-glm::vec3(2,4,6));
   EXPECT_NEAR(expectedFw.x,t.forward().x,1.0e-6);
   EXPECT_NEAR(expectedFw.y,t.forward().y,1.0e-6);
   EXPECT_NEAR(expectedFw.z,t.forward().z,1.0e-6);
}


