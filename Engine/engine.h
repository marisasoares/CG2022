//
// Created by miguel on 08/03/22.
//

#ifndef CG2022_ENGINE_H
#define CG2022_ENGINE_H
#endif //CG2022_ENGINE_H

#include <list>
#include "tinyxml.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>


//Classe de configuração da camera
class CameraConfig {
public:
    float cameraX;
    float cameraY;
    float cameraZ;
    float lookAtX;
    float lookAtY;
    float lookAtZ;
    float upX;
    float upY;
    float upZ;
    float fov;
    float near;
    float far;
};

//Ponto no espaço
class Point{
public:
    float x;
    float y;
    float z;
};

class Transformation{
public:
    /* 0 - Transform
     * 1 - Rotate
     * 2 - Scale
     * */
    int type;
    float x;
    float y;
    float z;
    float angle;
public:
    void applyTransformation();
};

//Modelo carregado de ficheiros .3d
class Model {
public:
    std::list<Point> points;
    std::list<Transformation> transformations{};
    void drawModel() const;
};

