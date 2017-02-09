//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Disc.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <gl/glut.h>
#pragma hdrstop
#include "Disc.h"
#include "Group.h"
#include "Reader.h"
#include "Transform.h"
#include "Ray.h"
#include "Composite.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read disc
bool Disc::read(istream &in, string &token, Group &group) {
    if (token == "Disc") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing disc opening brace");
        }
        Disc *disc = new Disc();
        group.push_back(disc);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (disc->_material.read(in, token)) {}
            else if (token == "Radius") {
                in >> disc->_radius;
            }
            else if (token == "Centre") {
                disc->_centre.readPosition(in);
            }
            else {
                throw string("Error : Invalid disc attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform disc
void Disc::transform(Transform &transform) {
    _transform = transform;
    _transform.translate(_centre);
    _transform.scale(Vectors(_radius, _radius, 1.0));
}

//------------------------------------------------------------------------------
// preview disc
void Disc::preview() const {
    _material.preview();
    glPushMatrix();
    glMultMatrixd(_transform.forward().transpose()());
    GLUquadricObj *disc = gluNewQuadric();
    gluQuadricDrawStyle(disc, GLU_FILL);
    gluQuadricNormals(disc, GLU_SMOOTH);
    gluDisk(disc, 0.0, 1.0, 100, 50);
    gluDeleteQuadric(disc);
    glPopMatrix();
}

//------------------------------------------------------------------------------
// intersect with disc
void Disc::intersect(const Ray &ray, Intersects &intersects) const {
    Ray line;
    line = _transform.inverse().multiply(ray);
    double a = line.direction()(Z);
    double b = line.position()(Z);
    if (fabs(a) >= EPSILON) {
        double lambda = -b / a;
        double x = (line.position() + lambda * line.direction())(X);
        double y = (line.position() + lambda * line.direction())(Y);
        if (x * x + y * y <= 1.0) {
            intersects().push_back(Intersects::Intersect(lambda, this));
        }
    }
}

//------------------------------------------------------------------------------
// normal to disc
Vectors Disc::normal(const Vectors &/*intersect*/) const {
    return Vectors(0.0, 0.0, 1.0, 0.0);
}

//------------------------------------------------------------------------------
