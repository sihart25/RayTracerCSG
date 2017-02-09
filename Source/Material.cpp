//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Material.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <gl/glut.h>
#pragma hdrstop
#include "Material.h"
#include "Colour.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read material
bool Material::read(istream &in, string &token) {
    if (token == "Material") {
        if (in >> token, token != "{") {
            throw string("Error : Missing material open brace");
        }
        while (in >> token, token != "}") {
            if (Reader::comment(in, token)) {}
            else if (token == "Ambient") {
                in >> _ambient;
            }
            else if (token == "Diffuse") {
                in >> _diffuse;
            }
            else if (token == "Specular") {
                in >> _specular;
            }
            else if (token == "Shininess") {
                in >> _shininess;
            }
            else if (token == "Emission") {
                in >> _emission;
            }
            else if (token == "Reflection") {
                in >> _reflection;
            }
            else if (token == "Refraction") {
                in >> _refraction;
            }
            else {
                throw string("Error : Invalid material attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// preview material
void Material::preview() const {
    GLfloat colour[COLOURS];
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambient.toGLfloat(colour));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse.toGLfloat(colour));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _specular.toGLfloat(colour));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, _emission.toGLfloat(colour));
}

//------------------------------------------------------------------------------
