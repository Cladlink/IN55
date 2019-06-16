#include "IGeometryEngine.h"

IGeometryEngine::IGeometryEngine(): indexBuf(QOpenGLBuffer::IndexBuffer)
{
}

IGeometryEngine::~IGeometryEngine()
{
}

QVector3D IGeometryEngine::randomColor()
{
    QVector3D ret;
    ret.setX(rand() / (float)RAND_MAX);
    ret.setY(rand() / (float)RAND_MAX);
    ret.setZ(rand() / (float)RAND_MAX);
    return ret;
}

void IGeometryEngine::initGeometry(Vertex *verticesShape,unsigned short *indicesShape)
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

    program->setUniformValue("axis",QVector3D(1.,0.,0.));

    program->setUniformValue("angle",0.f);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
}

void IGeometryEngine::update(QOpenGLShaderProgram *program,Vertex *verticesShape, unsigned short *indicesShape,
                             Vertex *verticesNormal, unsigned short *indicesNormal, QVector3D _color,
                             QMatrix4x4 _modelToProjectionMatrix, QMatrix4x4 _shapeModelToWorldMatrix,
                             QVector3D _position, QQuaternion _rotation, bool _showNormal, int _hideShapeNumber) {
    arrayBuf.bind();
    indexBuf.bind();

    if (_showNormal) {
        arrayBuf.allocate(verticesNormal, nbrVerticesNormal * sizeof(Vertex));
        indexBuf.allocate(indicesNormal, nbrIndicesNormal * sizeof(GLushort));
        glDrawElements(GL_LINES, nbrIndicesNormal, GL_UNSIGNED_SHORT, 0);
        //arrayBuf.release();
        //indexBuf.release();
    }

    for (int i=0; i<nbrVertices-1; i++) {
        verticesShape[i].color = _color;
    }
    arrayBuf.allocate(verticesShape, nbrVertices * sizeof(Vertex));
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

    program->setUniformValue("axis",_rotation.vector());

    program->setUniformValue("angle",_rotation.scalar());

    //qDebug() << _hideShapeNumber;

    program->setUniformValue("hideNumber",_hideShapeNumber);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
}

ShapeData IGeometryEngine::makeArrow() {
    ShapeData ret;
    Vertex stackVerts[] =
    {
        // Top side of arrow head
        QVector3D(+0.00f, +0.25f, -0.25f),         // 0
        QVector3D(+1.00f, +0.00f, +0.00f),		  // Color
        QVector3D(+0.00f, +1.00f, +0.00f),         // Normal
        QVector3D(+0.50f, +0.25f, -0.25f),         // 1
        QVector3D(+1.00f, +0.00f, +0.00f),		  // Color
        QVector3D(+0.00f, +1.00f, +0.00f),         // Normal
        QVector3D(+0.00f, +0.25f, -1.00f),         // 2
        QVector3D(+1.00f, +0.00f, +0.00f),		  // Color
        QVector3D(+0.00f, +1.00f, +0.00f),         // Normal
        QVector3D(-0.50f, +0.25f, -0.25f),         // 3
        QVector3D(+1.00f, +0.00f, +0.00f),		  // Color
        QVector3D(+0.00f, +1.00f, +0.00f),         // Normal
        // Bottom side of arrow head
        QVector3D(+0.00f, -0.25f, -0.25f),         // 4
        QVector3D(+0.00f, +0.00f, +1.00f),		  // Color
        QVector3D(+0.00f, -1.00f, +0.00f),         // Normal
        QVector3D(+0.50f, -0.25f, -0.25f),         // 5
        QVector3D(+0.00f, +0.00f, +1.00f),		  // Color
        QVector3D(+0.00f, -1.00f, +0.00f),         // Normal
        QVector3D(+0.00f, -0.25f, -1.00f),         // 6
        QVector3D(+0.00f, +0.00f, +1.00f),		  // Color
        QVector3D(+0.00f, -1.00f, +0.00f),         // Normal
        QVector3D(-0.50f, -0.25f, -0.25f),         // 7
        QVector3D(+0.00f, +0.00f, +1.00f),		  // Color
        QVector3D(+0.00f, -1.00f, +0.00f),         // Normal
        // Right side of arrow tip
        QVector3D(+0.50f, +0.25f, -0.25f),         // 8
        QVector3D(+0.60f, +1.00f, +0.00f),		  // Color
        QVector3D(0.83205032f, 0.00f, -0.55470026f), // Normal
        QVector3D(+0.00f, +0.25f, -1.00f),         // 9
        QVector3D(+0.60f, +1.00f, +0.00f),		  // Color
        QVector3D(0.83205032f, 0.00f, -0.55470026f), // Normal
        QVector3D(+0.00f, -0.25f, -1.00f),         // 10
        QVector3D(+0.60f, +1.00f, +0.00f),		  // Color
        QVector3D(0.83205032f, 0.00f, -0.55470026f), // Normal
        QVector3D(+0.50f, -0.25f, -0.25f),         // 11
        QVector3D(+0.60f, +1.00f, +0.00f),		  // Color
        QVector3D(0.83205032f, 0.00f, -0.55470026f), // Normal
        // Left side of arrow tip
        QVector3D(+0.00f, +0.25f, -1.00f),         // 12
        QVector3D(+0.00f, +1.00f, +0.00f),		  // Color
        QVector3D(-0.55708605f, 0.00f, -0.37139067f), // Normal
        QVector3D(-0.50f, +0.25f, -0.25f),         // 13
        QVector3D(+0.00f, +1.00f, +0.00f),		  // Color
        QVector3D(-0.55708605f, 0.00f, -0.37139067f), // Normal
        QVector3D(+0.00f, -0.25f, -1.00f),         // 14
        QVector3D(+0.00f, +1.00f, +0.00f),		  // Color
        QVector3D(-0.55708605f, 0.00f, -0.37139067f), // Normal
        QVector3D(-0.50f, -0.25f, -0.25f),         // 15
        QVector3D(+0.00f, +1.00f, +0.00f),		  // Color
        QVector3D(-0.55708605f, 0.00f, -0.37139067f), // Normal
        // Back side of arrow tip
        QVector3D(-0.50f, +0.25f, -0.25f),         // 16
        QVector3D(+0.50f, +0.50f, +0.50f),		  // Color
        QVector3D(+0.00f, +0.00f, +1.00f),         // Normal
        QVector3D(+0.50f, +0.25f, -0.25f),         // 17
        QVector3D(+0.50f, +0.50f, +0.50f),		  // Color
        QVector3D(+0.00f, +0.00f, +1.00f),         // Normal
        QVector3D(-0.50f, -0.25f, -0.25f),         // 18
        QVector3D(+0.50f, +0.50f, +0.50f),		  // Color
        QVector3D(+0.00f, +0.00f, +1.00f),         // Normal
        QVector3D(+0.50f, -0.25f, -0.25f),         // 19
        QVector3D(+0.50f, +0.50f, +0.50f),		  // Color
        QVector3D(+0.00f, +0.00f, +1.00f),         // Normal
        // Top side of back of arrow
        QVector3D(+0.25f, +0.25f, -0.25f),         // 20
        QVector3D(+1.00f, +0.00f, +0.00f),		  // Color
        QVector3D(+0.00f, +1.00f, +0.00f),         // Normal
        QVector3D(+0.25f, +0.25f, +1.00f),         // 21
        QVector3D(+1.00f, +0.00f, +0.00f),		  // Color
        QVector3D(+0.00f, +1.00f, +0.00f),         // Normal
        QVector3D(-0.25f, +0.25f, +1.00f),         // 22
        QVector3D(+1.00f, +0.00f, +0.00f),		  // Color
        QVector3D(+0.00f, +1.00f, +0.00f),         // Normal
        QVector3D(-0.25f, +0.25f, -0.25f),         // 23
        QVector3D(+1.00f, +0.00f, +0.00f),		  // Color
        QVector3D(+0.00f, +1.00f, +0.00f),         // Normal
        // Bottom side of back of arrow
        QVector3D(+0.25f, -0.25f, -0.25f),         // 24
        QVector3D(+0.00f, +0.00f, +1.00f),		  // Color
        QVector3D(+0.00f, -1.00f, +0.00f),         // Normal
        QVector3D(+0.25f, -0.25f, +1.00f),         // 25
        QVector3D(+0.00f, +0.00f, +1.00f),		  // Color
        QVector3D(+0.00f, -1.00f, +0.00f),         // Normal
        QVector3D(-0.25f, -0.25f, +1.00f),         // 26
        QVector3D(+0.00f, +0.00f, +1.00f),		  // Color
        QVector3D(+0.00f, -1.00f, +0.00f),         // Normal
        QVector3D(-0.25f, -0.25f, -0.25f),         // 27
        QVector3D(+0.00f, +0.00f, +1.00f),		  // Color
        QVector3D(+0.00f, -1.00f, +0.00f),         // Normal
        // Right side of back of arrow
        QVector3D(+0.25f, +0.25f, -0.25f),         // 28
        QVector3D(+0.60f, +1.00f, +0.00f),		  // Color
        QVector3D(+1.00f, +0.00f, +0.00f),         // Normal
        QVector3D(+0.25f, -0.25f, -0.25f),         // 29
        QVector3D(+0.60f, +1.00f, +0.00f),		  // Color
        QVector3D(+1.00f, +0.00f, +0.00f),         // Normal
        QVector3D(+0.25f, -0.25f, +1.00f),         // 30
        QVector3D(+0.60f, +1.00f, +0.00f),		  // Color
        QVector3D(+1.00f, +0.00f, +0.00f),         // Normal
        QVector3D(+0.25f, +0.25f, +1.00f),         // 31
        QVector3D(+0.60f, +1.00f, +0.00f),		  // Color
        QVector3D(+1.00f, +0.00f, +0.00f),         // Normal
        // Left side of back of arrow
        QVector3D(-0.25f, +0.25f, -0.25f),         // 32
        QVector3D(+0.00f, +1.00f, +0.00f),		  // Color
        QVector3D(-1.00f, +0.00f, +0.00f),         // Normal
        QVector3D(-0.25f, -0.25f, -0.25f),         // 33
        QVector3D(+0.00f, +1.00f, +0.00f),		  // Color
        QVector3D(-1.00f, +0.00f, +0.00f),         // Normal
        QVector3D(-0.25f, -0.25f, +1.00f),         // 34
        QVector3D(+0.00f, +1.00f, +0.00f),		  // Color
        QVector3D(-1.00f, +0.00f, +0.00f),         // Normal
        QVector3D(-0.25f, +0.25f, +1.00f),         // 35
        QVector3D(+0.00f, +1.00f, +0.00f),		  // Color
        QVector3D(-1.00f, +0.00f, +0.00f),         // Normal
        // Back side of back of arrow
        QVector3D(-0.25f, +0.25f, +1.00f),         // 36
        QVector3D(+0.50f, +0.50f, +0.50f),		  // Color
        QVector3D(+0.00f, +0.00f, +1.00f),         // Normal
        QVector3D(+0.25f, +0.25f, +1.00f),         // 37
        QVector3D(+0.50f, +0.50f, +0.50f),		  // Color
        QVector3D(+0.00f, +0.00f, +1.00f),         // Normal
        QVector3D(-0.25f, -0.25f, +1.00f),         // 38
        QVector3D(+0.50f, +0.50f, +0.50f),		  // Color
        QVector3D(+0.00f, +0.00f, +1.00f),         // Normal
        QVector3D(+0.25f, -0.25f, +1.00f),         // 39
        QVector3D(+0.50f, +0.50f, +0.50f),		  // Color
        QVector3D(+0.00f, +0.00f, +1.00f),         // Normal
    };

    GLushort stackIndices[] = {
        0, 1, 2, // Top
        0, 2, 3,
        4, 6, 5, // Bottom
        4, 7, 6,
        8, 10, 9, // Right side of arrow tip
        8, 11, 10,
        12, 15, 13, // Left side of arrow tip
        12, 14, 15,
        16, 19, 17, // Back side of arrow tip
        16, 18, 19,
        20, 22, 21, // Top side of back of arrow
        20, 23, 22,
        24, 25, 26, // Bottom side of back of arrow
        24, 26, 27,
        28, 30, 29, // Right side of back of arrow
        28, 31, 30,
        32, 33, 34, // Left side of back of arrow
        32, 34, 35,
        36, 39, 37, // Back side of back of arrow
        36, 38, 39,
    };

    ret.numVertices = sizeof(stackVerts) / sizeof(*stackVerts);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

    ret.numIndices = sizeof(stackIndices) / sizeof(*stackIndices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, stackIndices, sizeof(stackIndices));
    return ret;
}

ShapeData IGeometryEngine::makeCube() {
    ShapeData ret;
    Vertex stackVerts[] =
    {
        QVector3D(-1.0f, +1.0f, +1.0f),  // 0
        QVector3D(+1.0f, +0.0f, +0.0f),	// Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, +1.0f),  // 1
        QVector3D(+0.0f, +1.0f, +0.0f),	// Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, -1.0f),  // 2
        QVector3D(+0.0f, +0.0f, +1.0f),  // Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, +1.0f, -1.0f),  // 3
        QVector3D(+1.0f, +1.0f, +1.0f),  // Color
        QVector3D(+0.0f, +1.0f, +0.0f),  // Normal

        QVector3D(-1.0f, +1.0f, -1.0f),  // 4
        QVector3D(+1.0f, +0.0f, +1.0f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(+1.0f, +1.0f, -1.0f),  // 5
        QVector3D(+0.0f, +0.5f, +0.2f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(+1.0f, -1.0f, -1.0f),  // 6
        QVector3D(+0.8f, +0.6f, +0.4f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 7
        QVector3D(+0.3f, +1.0f, +0.5f),  // Color
        QVector3D(+0.0f, +0.0f, -1.0f),  // Normal

        QVector3D(+1.0f, +1.0f, -1.0f),  // 8
        QVector3D(+0.2f, +0.5f, +0.2f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, +1.0f, +1.0f),  // 9
        QVector3D(+0.9f, +0.3f, +0.7f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 10
        QVector3D(+0.3f, +0.7f, +0.5f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, -1.0f),  // 11
        QVector3D(+0.5f, +0.7f, +0.5f),  // Color
        QVector3D(+1.0f, +0.0f, +0.0f),  // Normal

        QVector3D(-1.0f, +1.0f, +1.0f),  // 12
        QVector3D(+0.7f, +0.8f, +0.2f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, +1.0f, -1.0f),  // 13
        QVector3D(+0.5f, +0.7f, +0.3f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 14
        QVector3D(+0.4f, +0.7f, +0.7f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 15
        QVector3D(+0.2f, +0.5f, +1.0f),  // Color
        QVector3D(-1.0f, +0.0f, +0.0f),  // Normal

        QVector3D(+1.0f, +1.0f, +1.0f),  // 16
        QVector3D(+0.6f, +1.0f, +0.7f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(-1.0f, +1.0f, +1.0f),  // 17
        QVector3D(+0.6f, +0.4f, +0.8f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 18
        QVector3D(+0.2f, +0.8f, +0.7f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 19
        QVector3D(+0.2f, +0.7f, +1.0f),  // Color
        QVector3D(+0.0f, +0.0f, +1.0f),  // Normal

        QVector3D(+1.0f, -1.0f, -1.0f),  // 20
        QVector3D(+0.8f, +0.3f, +0.7f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, -1.0f),  // 21
        QVector3D(+0.8f, +0.9f, +0.5f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(-1.0f, -1.0f, +1.0f),  // 22
        QVector3D(+0.5f, +0.8f, +0.5f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
        QVector3D(+1.0f, -1.0f, +1.0f),  // 23
        QVector3D(+0.9f, +1.0f, +0.2f),  // Color
        QVector3D(+0.0f, -1.0f, +0.0f),  // Normal
    };

    ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

    unsigned short stackIndices[] = {
        0,   1,  2,  0,  2,  3, // Top
        4,   5,  6,  4,  6,  7, // Front
        8,   9, 10,  8, 10, 11, // Right
        12, 13, 14, 12, 14, 15, // Left
        16, 17, 18, 16, 18, 19, // Back
        20, 22, 21, 20, 23, 22, // Bottom
    };
    ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, stackIndices, sizeof(stackIndices));

    return ret;
}

ShapeData IGeometryEngine::makePlaneVerts(uint dimensions)
{
    ShapeData ret;
    ret.numVertices = dimensions * dimensions;
    int half = dimensions / 2;
    ret.vertices = new Vertex[ret.numVertices];
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            Vertex& thisVert = ret.vertices[i * dimensions + j];
            thisVert.position.setX(j - half);
            thisVert.position.setZ(i - half);
            thisVert.position.setY(0);
            thisVert.normal = QVector3D(0.0f, 1.0f, 0.0f);
            thisVert.color = randomColor();
        }
    }
    return ret;
}

ShapeData IGeometryEngine::makePlaneIndices(uint dimensions)
{
    ShapeData ret;
    ret.numIndices = (dimensions - 1) * (dimensions - 1) * 2 * 3; // 2 triangles per square, 3 indices per triangle
    ret.indices = new unsigned short[ret.numIndices];
    int runner = 0;
    for (int row = 0; row < dimensions - 1; row++)
    {
        for (int col = 0; col < dimensions - 1; col++)
        {
            ret.indices[runner++] = dimensions * row + col;
            ret.indices[runner++] = dimensions * row + col + dimensions;
            ret.indices[runner++] = dimensions * row + col + dimensions + 1;

            ret.indices[runner++] = dimensions * row + col;
            ret.indices[runner++] = dimensions * row + col + dimensions + 1;
            ret.indices[runner++] = dimensions * row + col + 1;
        }
    }
    assert(runner = ret.numIndices);
    return ret;
}

ShapeData IGeometryEngine::makePyramide()
{
    ShapeData ret;

    Vertex myPyr[] =
    {
        {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 0
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //2 -> 1
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //1 -> 2

        {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 3
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //4 -> 4
        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //3 -> 5

        {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 6
        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //3 -> 7
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //2 -> 8

        {QVector3D(0.f, 1.f, 0.f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.5f, 1.0f)}, //0 -> 9
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //1 -> 10
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //4 -> 11

        {QVector3D(-0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 0.0f)}, //1 -> 12
        {QVector3D(0.5f, -0.5f, -0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 0.0f)}, //2 -> 13
        {QVector3D(0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(1.0f, 1.0f)}, //3 -> 14
        {QVector3D(-0.5f, -0.5f, 0.5f), QVector3D(1.0f, 0.0f,0.0f), QVector2D(0.0f, 1.0f)}
    };
    ret.numVertices = NUM_ARRAY_ELEMENTS(myPyr);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, myPyr, sizeof(myPyr));

    GLushort indices[] = { 0,1,2,
                           3,4,5,
                           6,7,8,
                           9,10,11,
                           15,12,13,
                           13,14,15};
    ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, indices, sizeof(indices));

    return ret;
}

ShapeData IGeometryEngine::makeSphere(uint tesselation) {
    ShapeData ret = makePlaneVerts(tesselation);
    ShapeData ret2 = makePlaneIndices(tesselation);
    ret.indices = ret2.indices;
    ret.numIndices = ret2.numIndices;

    uint dimensions = tesselation;
    const float RADIUS = 1.0f;
    const double CIRCLE = PI * 2;
    const double SLICE_ANGLE = CIRCLE / (dimensions - 1);
    for (size_t col = 0; col < dimensions; col++)
    {
        double phi = -SLICE_ANGLE * col;
        for (size_t row = 0; row < dimensions; row++)
        {
            double theta = -(SLICE_ANGLE / 2.0) * row;
            size_t vertIndex = col * dimensions + row;
            Vertex& v = ret.vertices[vertIndex];
            v.position.setX(RADIUS * cos(phi) * sin(theta));
            v.position.setY(RADIUS * sin(phi) * sin(theta));
            v.position.setZ(RADIUS * cos(theta));
            v.normal = v.position;
            v.normal.normalize();
        }
    }
    return ret;
}

ShapeData IGeometryEngine::makeTorus(uint tesselation)
{
    /*ShapeData ret;
    uint dimensions = tesselation * tesselation;
    ret.numVertices = dimensions;
    ret.vertices = new Vertex[ret.numVertices];
    float sliceAngle = 360 / tesselation;
    const float torusRadius = 1.0f;
    const float pipeRadius = 0.5f;
    for (uint round1 = 0; round1 < tesselation; round1++)
    {
        // Generate a circle on the xy plane, then
        // translate then rotate it into position
        glm::mat4 transform =
            glm::rotate(glm::mat4(), round1 * sliceAngle, glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(), glm::vec3(torusRadius, 0.0f, 0.0f));
        glm::mat3 normalTransform = (glm::mat3)transform;
        for (uint round2 = 0; round2 < tesselation; round2++)
        {
            Vertex& v = ret.vertices[round1 * tesselation + round2];
            glm::vec4 glmVert(
                pipeRadius * cos(glm::radians(sliceAngle * round2)),
                pipeRadius * sin(glm::radians(sliceAngle * round2)),
                0,
                1.0f);
            glm::vec4 glmVertPrime = transform * glmVert;
            v.position = (glm::vec3)glmVertPrime;
            v.normal = glm::normalize(normalTransform * (glm::vec3)glmVert);
            v.color = randomColor();
        }
    }

    ShapeData ret2 = makePlaneUnseamedIndices(tesselation);
    ret.numIndices = ret2.numIndices;
    ret.indices = ret2.indices;
    return ret;*/

    ShapeData ret;
    uint dimensions = tesselation * tesselation;
    ret.numVertices = dimensions;
    ret.vertices = new Vertex[ret.numVertices];
    float sliceAngle = 360 / tesselation;
    const float torusRadius = 1.0f;
    const float pipeRadius = 0.5f;
    for (uint round1 = 0; round1 < tesselation; round1++)
    {
        // Generate a circle on the xy plane, then
        // translate then rotate it into position
        QMatrix4x4 transform;
        transform.translate(QVector3D(torusRadius, 0.0f, 0.0f));
        transform.rotate(round1 * sliceAngle, QVector3D(0.0f, 1.0f, 0.0f));

        for (uint round2 = 0; round2 < tesselation; round2++)
        {
            Vertex& v = ret.vertices[round1 * tesselation + round2];
            QVector4D glmVert(
                pipeRadius * cos(qDegreesToRadians(sliceAngle * round2)),
                pipeRadius * sin(qDegreesToRadians(sliceAngle * round2)),
                0,
                1.0f);
            QVector4D glmVertPrime = transform * glmVert;
            v.position = (QVector3D)glmVertPrime;
            v.normal = transform.mapVector((QVector3D)glmVert);
            v.normal.normalize();
            v.color = randomColor();
        }
    }

    ShapeData ret2 = makePlaneUnseamedIndices(tesselation);
    ret.numIndices = ret2.numIndices;
    ret.indices = ret2.indices;
    return ret;
}

ShapeData IGeometryEngine::makeTeapot(uint tesselation, const QMatrix4x4 &lidTransform) {
    ShapeData ret;

    ret.numVertices = 32 * (tesselation + 1) * (tesselation + 1);
    uint faces = tesselation * tesselation * 32;
    float* vertices = new float[ret.numVertices * 3];
    float* normals = new float[ret.numVertices * 3];
    float* textureCoordinates = new float[ret.numVertices * 2];
    ret.numIndices = faces * 6;
    ret.indices = new unsigned short[ret.numIndices];

    generatePatches(vertices, normals, textureCoordinates, ret.indices, tesselation);
    moveLid(tesselation, vertices, lidTransform);

    // Adapt/convert their data format to mine
    ret.vertices = new Vertex[ret.numVertices];
    for (uint i = 0; i < ret.numVertices; i++)
    {
        Vertex& v = ret.vertices[i];
        v.position.setX(vertices[i * 3 + 0]);
        v.position.setY(vertices[i * 3 + 1]);
        v.position.setZ(vertices[i * 3 + 2]);
        v.normal.setX(normals[i * 3 + 0]);
        v.normal.setY(normals[i * 3 + 1]);
        v.normal.setZ(normals[i * 3 + 2]);
        v.color = randomColor();
    }
    return ret;
}

ShapeData IGeometryEngine::makePlaneUnseamedIndices(uint tesselation)
{
    ShapeData ret;
    uint dimensions = tesselation * tesselation;
    ret.numIndices = dimensions * 2 * 3; // 2 triangles per square, 3 indices per triangle
    ret.indices = new unsigned short[ret.numIndices];
    int runner = 0;
    for (int row = 0; row < tesselation; row++)
    {
        // This code is crap but works, and I'm not in the mood right now to clean it up
        for (int col = 0; col < tesselation; col++)
        {
            // Bottom left triangle
            ret.indices[runner++] = tesselation * row + col;
            // One row down unless it's the bottom row,
            ret.indices[runner++] = (row + 1 == tesselation ? 0 : tesselation * row + tesselation) + col;
            // Move to vert right of this one unless it's the last vert,
            // which we connect to the first vert in the row
            // the % dimensions at the end accounts for the last row hooking to the first row
            ret.indices[runner++] = (tesselation * row + col + tesselation + (col + 1 == tesselation ? -tesselation + 1 : 1)) % dimensions;

            // Upper right triangle
            ret.indices[runner++] = tesselation * row + col;
            if (col + 1 == tesselation && row + 1 == tesselation)
            {
                // Very last vert
                ret.indices[runner++] = 0;
            }
            else if (col + 1 == tesselation)
            {
                // Last vert on this row
                // Check if we need to connect it to zeroeth row or the next row
                if (row + 1 == tesselation)
                {
                    // Tie to zeroeth row
                    ret.indices[runner++] = col + 1;
                }
                else
                {
                    // Tie to next row
                    ret.indices[runner++] = tesselation * row + col + 1;
                }
            }
            else
            {
                // Regular interior vert
                // the % dimensions at the end accounts for the last row hooking to the first row
                ret.indices[runner++] = (tesselation * row + col + tesselation + 1) % dimensions;
            }
            ret.indices[runner++] = tesselation * row + col + (col + 1 == tesselation ? -col : 1);
        }
    }
    return ret;
}

void IGeometryEngine::generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid) {
    float * B = new float[4 * (grid + 1)];  // Pre-computed Bernstein basis functions
    float * dB = new float[4 * (grid + 1)]; // Pre-computed derivitives of basis functions

    int idx = 0, elIndex = 0, tcIndex = 0;

    // Pre-compute the basis functions  (Bernstein polynomials)
    // and their derivatives
    computeBasisFunctions(B, dB, grid);

    // Build each patch
    // The rim
    buildPatchReflect(0, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    // The body
    buildPatchReflect(1, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    buildPatchReflect(2, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    // The lid
    buildPatchReflect(3, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    buildPatchReflect(4, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    // The bottom
    buildPatchReflect(5, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, true, true);
    // The handle
    buildPatchReflect(6, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
    buildPatchReflect(7, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
    // The spout
    buildPatchReflect(8, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);
    buildPatchReflect(9, B, dB, v, n, tc, el, idx, elIndex, tcIndex, grid, false, true);

    delete[] B;
    delete[] dB;
}

void IGeometryEngine::buildPatchReflect(int patchNum,
    float *B, float *dB,
    float *v, float *n,
    float *tc, unsigned short *el,
    int &index, int &elIndex, int &tcIndex, int grid,
    bool reflectX, bool reflectY)
{
    QVector3D patch[4][4];
    QVector3D patchRevV[4][4];
    getPatch(patchNum, patch, false);
    getPatch(patchNum, patchRevV, true);

    // Patch without modification
    buildPatch(patch, B, dB, v, n, tc, el,
        index, elIndex, tcIndex, grid, QMatrix3x3(), true);

    float dataArrayX[9] = {-1.0f,0.f,0.f,0.0f, 1.0f, 0.0f,0.0f, 0.0f, 1.0f};
    float* data;
    data = dataArrayX;
    QMatrix3x3 matX = QMatrix3x3(data);
    // Patch reflected in x
    if (reflectX) {
        buildPatch(patchRevV, B, dB, v, n, tc, el,
            index, elIndex, tcIndex, grid, matX, false);
    }

    float dataArrayY[9] = {1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, 0.0f, 1.0f};
    data = dataArrayY;
    QMatrix3x3 matY = QMatrix3x3(data);
    // Patch reflected in y
    if (reflectY) {
        buildPatch(patchRevV, B, dB, v, n, tc, el,
            index, elIndex, tcIndex, grid, matY, false);
    }

    float dataArrayXY[9] = {-1.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,0.0f, 0.0f, 1.0f};
    data = dataArrayXY;
    QMatrix3x3 matXY = QMatrix3x3(data);
    // Patch reflected in x and y
    if (reflectX && reflectY) {
        buildPatch(patch, B, dB, v, n, tc, el,
            index, elIndex, tcIndex, grid, matXY, true);
    }
}

void IGeometryEngine::buildPatch(QVector3D patch[][4],
    float *B, float *dB,
    float *v, float *n, float *tc,
    unsigned short *el,
    int &index, int &elIndex, int &tcIndex, int grid, QMatrix3x3 reflect,
    bool invertNormal)
{
    int startIndex = index / 3;
    float tcFactor = 1.0f / grid;

    for (int i = 0; i <= grid; i++)
    {
        for (int j = 0; j <= grid; j++)
        {
            QMatrix4x4 temp = QMatrix4x4(reflect);
            QVector3D pt = temp.mapVector(evaluate(i, j, B, patch));
            QVector3D norm = temp.mapVector(evaluateNormal(i, j, B, dB, patch));
            if (invertNormal)
                norm = -norm;

            v[index] = pt.x();
            v[index + 1] = pt.y();
            v[index + 2] = pt.z();

            n[index] = norm.x();
            n[index + 1] = norm.y();
            n[index + 2] = norm.z();

            tc[tcIndex] = i * tcFactor;
            tc[tcIndex + 1] = j * tcFactor;

            index += 3;
            tcIndex += 2;
        }
    }

    for (int i = 0; i < grid; i++)
    {
        int iStart = i * (grid + 1) + startIndex;
        int nextiStart = (i + 1) * (grid + 1) + startIndex;
        for (int j = 0; j < grid; j++)
        {
            el[elIndex] = iStart + j;
            el[elIndex + 1] = nextiStart + j + 1;
            el[elIndex + 2] = nextiStart + j;

            el[elIndex + 3] = iStart + j;
            el[elIndex + 4] = iStart + j + 1;
            el[elIndex + 5] = nextiStart + j + 1;

            elIndex += 6;
        }
    }
}



void IGeometryEngine::getPatch(int patchNum, QVector3D patch[][4], bool reverseV)
{
    for (int u = 0; u < 4; u++) {          // Loop in u direction
        for (int v = 0; v < 4; v++) {     // Loop in v direction
            if (reverseV) {
                patch[u][v] = QVector3D(
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + (3 - v)]][0],
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + (3 - v)]][1],
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + (3 - v)]][2]
                    );
            }
            else {
                patch[u][v] = QVector3D(
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + v]][0],
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + v]][1],
                    TeapotData::cpdata[TeapotData::patchdata[patchNum][u * 4 + v]][2]
                    );
            }
        }
    }
}

void IGeometryEngine::computeBasisFunctions(float * B, float * dB, int grid) {
    float inc = 1.0f / grid;
    for (int i = 0; i <= grid; i++)
    {
        float t = i * inc;
        float tSqr = t * t;
        float oneMinusT = (1.0f - t);
        float oneMinusT2 = oneMinusT * oneMinusT;

        B[i * 4 + 0] = oneMinusT * oneMinusT2;
        B[i * 4 + 1] = 3.0f * oneMinusT2 * t;
        B[i * 4 + 2] = 3.0f * oneMinusT * tSqr;
        B[i * 4 + 3] = t * tSqr;

        dB[i * 4 + 0] = -3.0f * oneMinusT2;
        dB[i * 4 + 1] = -6.0f * t * oneMinusT + 3.0f * oneMinusT2;
        dB[i * 4 + 2] = -3.0f * tSqr + 6.0f * t * oneMinusT;
        dB[i * 4 + 3] = 3.0f * tSqr;
    }
}

QVector3D IGeometryEngine::evaluate(int gridU, int gridV, float *B, QVector3D patch[][4])
{
    QVector3D p(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            p += patch[i][j] * B[gridU * 4 + i] * B[gridV * 4 + j];
        }
    }
    return p;
}

QVector3D IGeometryEngine::evaluateNormal(int gridU, int gridV, float *B, float *dB, QVector3D patch[][4])
{
    QVector3D du(0.0f, 0.0f, 0.0f);
    QVector3D dv(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            du += patch[i][j] * dB[gridU * 4 + i] * B[gridV * 4 + j];
            dv += patch[i][j] * B[gridU * 4 + i] * dB[gridV * 4 + j];
        }
    }
    QVector3D temp;
    temp = temp.crossProduct(du,dv);
    temp.normalize();
    return temp;
}

void IGeometryEngine::moveLid(int grid, float *v, const QMatrix4x4 &lidTransform) {

    int start = 3 * 12 * (grid + 1) * (grid + 1);
    int end = 3 * 20 * (grid + 1) * (grid + 1);

    for (int i = start; i < end; i += 3)
    {
        QVector4D vert = QVector4D(v[i], v[i + 1], v[i + 2], 1.0f);
        vert = lidTransform * vert;
        v[i] = vert.x();
        v[i + 1] = vert.y();
        v[i + 2] = vert.z();
    }
}

ShapeData IGeometryEngine::generateNormals(const ShapeData& data)
{
    ShapeData ret;
    ret.numVertices = data.numVertices * 2;
    ret.vertices = new Vertex[ret.numVertices];
    QVector3D white(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < data.numVertices; i++)
    {
        uint vertIndex = i * 2;
        Vertex& v1 = ret.vertices[vertIndex];
        Vertex& v2 = ret.vertices[vertIndex + 1];
        const Vertex& sourceVertex = data.vertices[i];
        v1.position = sourceVertex.position;
        v2.position = sourceVertex.position + sourceVertex.normal;
        v1.color = v2.color = white;
    }

    ret.numIndices = ret.numVertices;
    ret.indices = new GLushort[ret.numIndices];
    for (int i = 0; i < ret.numIndices; i++)
        ret.indices[i] = i;
    return ret;
}
