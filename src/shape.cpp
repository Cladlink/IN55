 #include "shape.h"

Shape::Shape()
{

}

Shape::Shape(string _path)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    this->setPath(_path);

    // Initializes forme geometry and transfers it to VBOs
    initGeometry();
}

Shape::~Shape()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    delete[] this->verticesShape;
    delete[] this->indicesShape;
}
//! [0]

void Shape::initGeometry()
{
////! [1]
    load_obj();
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(this->verticesShape, nbrVertices * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(this->indicesShape, nbrIndices * sizeof(GLushort));
//! [1]
}

//! [2]
void Shape::drawGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int uvLocation = program->attributeLocation("vertexUV");
    program->enableAttributeArray(uvLocation);
    program->setAttributeBuffer(uvLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
}

void Shape::update(QOpenGLShaderProgram *program, QVector3D _color){

    arrayBuf.bind();
    for (int i=0; i<nbrVertices-1; i++) {
        this->verticesShape[i].color = _color;
    }

    arrayBuf.allocate(this->verticesShape, nbrVertices * sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(this->indicesShape, nbrIndices * sizeof(GLushort));
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int colorLocation = program->attributeLocation("color");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    int uvLocation = program->attributeLocation("vertexUV");
    program->enableAttributeArray(uvLocation);
    program->setAttributeBuffer(uvLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, nbrIndices, GL_UNSIGNED_SHORT, 0);
}
//! [2]

void Shape::load_obj(){
    string filename = this->getPath();
    QVector<QVector3D> vertices;
    QVector3D normals;
    QVector<GLushort> elements;

    filename = QCoreApplication::applicationDirPath().toStdString() + "/../../" + filename;
    ifstream in(filename, ios::in);
    if (!in)
    {
        cerr << "Cannot open " << filename << endl; exit(1);
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            QVector3D v;
            float a, b, c;
            s >> a;
            s >> b;
            s >> c;
            v.setX(a);
            v.setY(b);
            v.setZ(c);
            vertices.push_back(v);
        }
        else if (line.substr(0,2) == "f ")
        {
            string s(line.substr(2));
            regex rgx { R"(\d{1,3}\/\/\d{1,3})" };
            smatch matches;

            while(s.size() != 0){
                regex_search(s, matches, rgx);
                string value = matches[0].str();
                string vertexString;
                for(int i=0; value[i] != '/'; i++) {
                        vertexString += value[i];
                }
                int vertexInt = stoi(vertexString);
                elements.push_back((GLushort)vertexInt-1);
                if(s.size() > matches[0].length()+1){
                    s = s.substr(matches[0].length()+1);
                } else {
                    s = "";
                }
            }
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }

    nbrIndices = elements.size();
    nbrVertices = vertices.size();

    this->indicesShape = new GLushort[elements.size()];
    for(int i = 0; !elements.isEmpty(); i++){
        this->indicesShape[i] = elements.first();
        elements.pop_front();
    }

//    cout << "this->indicesShape : " << endl;

//    for (int i=0; i < nbrIndices; i++) {
//        cout << this->indicesShape[i] << endl;
//    }

    this->verticesShape = new VertexData[vertices.size()];
    for(int i = 0; !vertices.isEmpty(); i++){
        this->verticesShape[i].position = QVector3D(vertices[0].x(), vertices[0].y(), vertices[0].z());
        this->verticesShape[i].color = QVector3D(1.0f, 1.0f, 1.0f);
        vertices.pop_front();
    }

//    cout << "this->verticesShape : " << endl;

//    for (int i=0; i < nbrVertices; i++) {
//        cout << "point " << i << " : "<< endl;
//        cout << this->verticesShape[i].position.x() << endl;
//        cout << this->verticesShape[i].position.y() << endl;
//        cout << this->verticesShape[i].position.z() << endl;
//    }



//    normals.resize(vertices.size(), QVector3D(0.0, 0.0, 0.0));
//    for (int i = 0; i < elements.size(); i+=3)
//    {
//        GLushort ia = elements[i];
//        GLushort ib = elements[i+1];
//        GLushort ic = elements[i+2];
//        QVector3D normal = normalize(glm::cross(
//        QVector3D(vertices[ib]) - QVector3D(vertices[ia]),
//        QVector3D(vertices[ic]) - QVector3D(vertices[ia])));
//        normals[ia] = normals[ib] = normals[ic] = normal;
//    }
}

string Shape::getPath(){
    return path;
}

void Shape::setPath(string _path){
    this->path = _path;
}


