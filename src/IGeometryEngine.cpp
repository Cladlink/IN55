#include "IGeometryEngine.h"

IGeometryEngine::IGeometryEngine(): indexBuf(QOpenGLBuffer::IndexBuffer)
{
}

IGeometryEngine::~IGeometryEngine()
{
}

void IGeometryEngine::initGeometry(Vertex *verticesShape, unsigned short *indicesShape)
{
    arrayBuf.bind();
    arrayBuf.allocate(verticesShape, nbrVertices * sizeof(Vertex));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indicesShape, nbrIndices * sizeof(GLushort));
}

void IGeometryEngine::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(Vertex));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(Vertex));

    offset += sizeof(QVector3D);

    int uvLocation = program->attributeLocation("normal");
    program->enableAttributeArray(uvLocation);
    program->setAttributeBuffer(uvLocation, GL_FLOAT, offset, 3, sizeof(Vertex));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
}

void IGeometryEngine::update(QOpenGLShaderProgram *program,Vertex *verticesShape, unsigned short *indicesShape, QVector3D _color,
                             QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                             QVector3D _position) {
    arrayBuf.bind();
    for (int i=0; i<nbrVertices-1; i++) {
        verticesShape[i].color = _color;
    }
    arrayBuf.allocate(verticesShape, nbrVertices * sizeof(Vertex));

    indexBuf.bind();
    indexBuf.allocate(indicesShape, nbrIndices * sizeof(GLushort));

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(Vertex));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(Vertex));

    offset += sizeof(QVector3D);

    int normalLocation = program->attributeLocation("normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(Vertex));

    program->setUniformValue("modelToProjectionMatrix", _modelToProjectionMatrix);

    program->setUniformValue("modelToWorldMatrix",_shapeModelToWorldMatrix);

    program->setUniformValue("translation",QVector4D(_position,1.f));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
}
