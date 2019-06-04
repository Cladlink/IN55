#ifndef CAMERA_H
#define CAMERA_H

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QMatrix3x3>

class Camera
{
    QVector3D position;
    QVector3D viewDirection;
    const QVector3D UP;
    QVector2D oldMousePosition;
    static const float MOVEMENT_SPEED;
    QVector3D strafeDirection;
public:
    Camera();
    void mouseUpdate(const QVector2D& newMousePosition);
    QMatrix4x4 getWorldToViewMatrix() const;

    void moveForward();
    void moveBackward();
    void strafeLeft();
    void strafeRight();
    void moveUp();
    void moveDown();
    QVector3D getPosition() const { return position; }
};

#endif // CAMERA_H
