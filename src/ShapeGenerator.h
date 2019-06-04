#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H

#include "ShapeData.h"
#include <QMatrix3x3>

typedef unsigned int uint;

class ShapeGenerator
{
    static ShapeData makePlaneVerts(uint dimensions);
    static ShapeData makePlaneIndices(uint dimensions);
    static ShapeData makePlaneUnseamedIndices(uint tesselation);

    // Teapot helpers
    static void generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid);
    static void moveLid(int grid, float *v, const QMatrix4x4 &lidTransform);
    static void buildPatchReflect(int patchNum,
        float *B, float *dB,
        float *v, float *n,
        float *tc, unsigned short *el,
        int &index, int &elIndex, int &tcIndex, int grid,
        bool reflectX, bool reflectY);
    static void buildPatch(QVector3D patch[][4],
        float *B, float *dB,
        float *v, float *n, float *tc,
        unsigned short *el,
        int &index, int &elIndex, int &tcIndex,
        int grid, QMatrix3x3 reflect,
        bool invertNormal);
    static void getPatch(int patchNum, QVector3D patch[][4], bool reverseV);
    static void computeBasisFunctions(float * B, float * dB, int grid);
    static QVector3D evaluate(int gridU, int gridV, float *B, QVector3D patch[][4]);
    static QVector3D evaluateNormal(int gridU, int gridV,
        float *B, float *dB, QVector3D patch[][4]);
public:
    static ShapeData makeTriangle();
    static ShapeData makeCube();
    static ShapeData makeArrow();
    static ShapeData makePlane(uint dimensions = 10);
    static ShapeData makeTeapot(uint tesselation = 10);
    //static ShapeData makeTeapot(uint tesselation = 10, const QMatrix4x4 &lidTransform = null);
    static ShapeData makeSphere(uint tesselation = 20);
    static ShapeData makeTorus(uint tesselation = 20);
    static ShapeData generateNormals(const ShapeData& data);
};

#endif // SHAPEGENERATOR_H
