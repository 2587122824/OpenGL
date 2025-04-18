#pragma once
#include <iostream>
#include <GLM/glm.hpp>
#include <GL/glew.h>
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
// 默认摄像机参数  
const float YAW = -90.0f;//俯仰角（绕x轴）
const float PITCH = 0.0f;//偏航角（绕y轴）
//const float SPEED = 10.5f;//移动速度
//const float SENSITIVITY = 0.1f;//灵敏度
const float SPEED = 0.0f;//移动速度
const float SENSITIVITY = 0.0f;//灵敏度
const float ZOOM = 45.0f;//
class Camera
{
public:
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // constructor with scalar value
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
    glm::mat4 GetViewMatrix();
private:
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw = 0.0, Pitch = 0.0;//俯仰角（绕x轴），偏航角（绕y轴）
    float fov = 45.0f;//视野 全局变量 
    
    void updateCameraVectors();
};