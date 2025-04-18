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
// Ĭ�����������  
const float YAW = -90.0f;//�����ǣ���x�ᣩ
const float PITCH = 0.0f;//ƫ���ǣ���y�ᣩ
//const float SPEED = 10.5f;//�ƶ��ٶ�
//const float SENSITIVITY = 0.1f;//������
const float SPEED = 0.0f;//�ƶ��ٶ�
const float SENSITIVITY = 0.0f;//������
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
    float Yaw = 0.0, Pitch = 0.0;//�����ǣ���x�ᣩ��ƫ���ǣ���y�ᣩ
    float fov = 45.0f;//��Ұ ȫ�ֱ��� 
    
    void updateCameraVectors();
};