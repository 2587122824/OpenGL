#include "camera.h"
#include <GLM/glm.hpp>
#include <GLFW/glfw3.h>
#include <GLM/gtc/matrix_transform.hpp>

// constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    cameraPos = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}
// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    cameraPos = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    //�ƶ������
    float cameraSpeed = 55.5f * deltaTime; //������ǵ�deltaTime�ܴ󣬾���ζ����һ֡����Ⱦ�����˸���ʱ�䣬������һ֡���ٶ���Ҫ��ø�����ƽ����Ⱦ����ȥ��ʱ��
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        cameraPos += cameraFront * velocity;
    if (direction == BACKWARD)
        cameraPos -= cameraFront * velocity;
    if (direction == LEFT)
        cameraPos -= Right * velocity;
    if (direction == RIGHT)
        cameraPos += Right * velocity;
    cameraPos.y = 0.0f;//ȷ��ֻ��xzƽ�����ƶ�
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    //�������ϻ����½ǶȲ�����90��
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 90.0f)
        Zoom = 90.0f;
}
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    cameraFront = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(cameraFront, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    cameraUp = glm::normalize(glm::cross(Right, cameraFront));
}