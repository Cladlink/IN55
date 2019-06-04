#include "camera.h"

const float Camera::MOVEMENT_SPEED = 0.1f;

Camera::Camera() :
    position(-3.11094999f, 2.23070025f, -2.86016989f),
    viewDirection(0.663740635f, -0.492421985f, 0.562995136f),
    UP(0.0f, 1.0f, 0.0f)
{
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
