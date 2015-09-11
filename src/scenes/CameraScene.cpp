#include "CameraScene.h"
// void CameraScene::handleCameraInput()
// {
//    glm::vec3 translate(0.0);
//    glm::vec3 rotate(0.0);
//    if(Keyboard::isKeyDown(GLFW_KEY_W))
//    {
//       translate += camera.transform.forward() * Cam_Speed;
//    }
//    if(Keyboard::isKeyDown(GLFW_KEY_S))
//    {
//       translate -= camera.transform.forward() * Cam_Speed;
//    }
//    if(Keyboard::isKeyDown(GLFW_KEY_A))
//    {
//       translate-= camera.transform.right() * Cam_Speed;
//    }
//    if(Keyboard::isKeyDown(GLFW_KEY_D))
//    {
//       translate+= camera.transform.right() * Cam_Speed;
//    }
//    if(Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT))
//    {

//       rotate.x = (Mouse::getLastY() - Mouse::getY())/(float)(getContext()->getWindowHeight())/2.0 * Cam_Rot_Speed;
//       rotate.y = (Mouse::getLastX() - Mouse::getX())/(float)(getContext()->getWindowWidth())/2.0 * Cam_Rot_Speed;
//       pitch += rotate.x;
//       yaw += rotate.y;
//       rotate.z = 0;
//    }
//    camera.translate(translate);
//    camera.setRotation(glm::vec3(pitch,yaw,0));
// }


CameraScene::CameraScene(Context * ctx):
EmptyScene(),
 pitch(0),
 yaw(0),
 camera(ctx->getWindowWidth(), ctx->getWindowHeight())
{

}
CameraScene::~CameraScene()
{
   
}
void CameraScene::update()
{
   camera.update(getContext());
}
