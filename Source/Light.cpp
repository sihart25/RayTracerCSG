//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Light.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <gl/glut.h>
#pragma hdrstop
#include "Light.h"
#include "Group.h"
#include "Reader.h"
#include "Transform.h"
#include "Colour.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
int Light::_count = 0;

//------------------------------------------------------------------------------
// static function to read light
bool Light::read(istream &in, string &token, Group &group) {
    if (token == "Light") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing light opening brace");
        }
        Light *light = new Light();
        group.push_back(light);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (token == "Centre") {
                light->_centre.readPosition(in);
            }
            else if (token == "Ambient") {
                in >> light->_ambient;
            }
            else if (token == "Diffuse") {
                in >> light->_diffuse;
            }
            else if (token == "Specular") {
                in >> light->_specular;
            }
            else if (token == "Infinite") {
                in >> boolalpha >> light->_infinite >> noboolalpha;
            }
            else {
                throw string("Error : Invalid light attribute = " + token);
            }
        }
        if (light->_infinite) {
            light->_centre.setDirection();
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform light
void Light::transform(Transform &transform) {
    _position = transform.forward().multiply(_centre);
}

//------------------------------------------------------------------------------
// preview light
void Light::preview() const {
    GLfloat position[DIM];
    GLfloat colour[COLOURS];
    glLightfv(GL_LIGHT[_count], GL_POSITION, _position.toGLfloat(position));
    glLightfv(GL_LIGHT[_count], GL_AMBIENT, _ambient.toGLfloat(colour));
    glLightfv(GL_LIGHT[_count], GL_DIFFUSE, _diffuse.toGLfloat(colour));
    glLightfv(GL_LIGHT[_count], GL_SPECULAR, _specular.toGLfloat(colour));
    glEnable(GL_LIGHT[_count]);
    if (_count == GL_LIGHT7) {
        _count = GL_LIGHT0;
    }
    else {
        ++_count;
    }
}

//------------------------------------------------------------------------------
