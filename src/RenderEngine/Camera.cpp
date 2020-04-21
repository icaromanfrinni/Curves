#include "Camera.h"

// default Constructor
Camera::Camera() : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), FieldOfView(FOV)
{
    Position = glm::vec3(0.0f, 0.0f, 25.0f);
    View = glm::vec3(0.0f, 0.0f, 0.0f);
    LookAt = glm::normalize(View - Position);
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = YAW;
    Pitch = PITCH;
    updateCameraVectors();
}

// destructor
Camera::~Camera()
{
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, View, Up);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == UP)
    {
        Position += Up * velocity;
        View += Up * velocity;
    }
    if (direction == DOWN)
    {
        Position -= Up * velocity;
        View -= Up * velocity;
    }
    if (direction == RIGHT)
    {
        Position += Right * velocity;
        View += Right * velocity;
    }
    if (direction == LEFT)
    {
        Position -= Right * velocity;
        View -= Right * velocity;
    }
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    glm::vec3 front = View - Position;
    Position += front * yoffset * MouseSensitivity;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    LookAt = glm::normalize(front);

    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(LookAt, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, LookAt));
}