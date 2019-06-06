#include "Camera.h"

const float Camera::MOVEMENT_SPEED = 0.1f;

Camera::Camera() {
    this->position = QVector3D(0.f, 3.f, 5.f);
    this->viewDirection = QVector3D(0.f, -0.5f, -1.f);
}

void Camera::mouseUpdate(const QVector2D& newMousePosition)
{
    QVector2D mouseDelta = newMousePosition - oldMousePosition;
    if (mouseDelta.length() > 50.0f)
    {
        oldMousePosition = newMousePosition;
        return;
    }
    const float ROTATIONAL_SPEED = 0.5f;
    strafeDirection = strafeDirection.crossProduct(viewDirection,UP);
    QMatrix4x4 rotator;
    rotator.rotate(-mouseDelta.y() * ROTATIONAL_SPEED, strafeDirection);
    rotator.rotate(-mouseDelta.x() * ROTATIONAL_SPEED, UP);

    viewDirection = rotator.mapVector(viewDirection);

    oldMousePosition = newMousePosition;
}

QMatrix4x4 Camera::getWorldToViewMatrix() const
{
    QMatrix4x4 lookAt;
    lookAt.lookAt(position, position + viewDirection, UP);
    return lookAt;
}

void Camera::moveForward()
{
    position += MOVEMENT_SPEED * viewDirection;
}

void Camera::moveBackward()
{
    position += -MOVEMENT_SPEED * viewDirection;
}

void Camera::strafeLeft()
{
    position += -MOVEMENT_SPEED * strafeDirection;
}

void Camera::strafeRight()
{
    position += MOVEMENT_SPEED * strafeDirection;
}

void Camera::moveUp()
{
    position += MOVEMENT_SPEED * UP;
}

void Camera::moveDown()
{
    position += -MOVEMENT_SPEED * UP;
}
