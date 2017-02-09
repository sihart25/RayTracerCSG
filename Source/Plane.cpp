//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Plane.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <gl/glut.h>
#pragma hdrstop
#include "Plane.h"
#include "Group.h"
#include "Reader.h"
#include "Transform.h"
#include "Vectors.h"
#include "Ray.h"
#include "Intersects.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read plane
bool Plane::read(istream &in, string &token, Group &group) {
    if (token == "Plane") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing plane opening brace");
        }
        Plane *plane = new Plane();
        group.push_back(plane);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (plane->_material.read(in, token)) {}
            else if (token == "Width") {
                in >> plane->_width;
            }
            else if (token == "Height") {
                in >> plane->_height;
            }
            else if (token == "Infinite") {
                in >> boolalpha >> plane->_infinite >> noboolalpha;
            }
            else if (token == "Centre") {
                plane->_centre.readPosition(in);
            }
            else if (token == "Normal") {
                plane->_normal.readDirection(in);
            }
            else if (token == "Up") {
                plane->_up.readDirection(in);
            }
            else {
                throw string("Error : Invalid plane attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform plane
void Plane::transform(Transform &transform) {
    _transform = transform;
    _transform.translate(_centre);
    Vectors n = Vectors(_normal.unit());
    Vectors u = Vectors(_up.cross(n).unit());
    Vectors v = Vectors(n.cross(u).unit());
    double angle = acos((u(X) + v(Y) + n(Z) - 1.0) / 2.0);
    double rsin = sin(angle);
    rsin = (fabs(rsin) < EPSILON) ? 1.0 : 1.0 / rsin;
    Vectors axis = Vectors(v(Z) - n(Y), n(X) - u(Z), u(Y) - v(X)) * rsin / 2.0;
    _transform.rotate(angle / PI * 180.0, axis);
    _transform.scale(Vectors(0.5 * _width, 0.5 * _height, 1.0));
}

//------------------------------------------------------------------------------
// preview plane
void Plane::preview() const {
    _material.preview();
    glPushMatrix();
    glMultMatrixd(_transform.forward().transpose()());
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    double size = (_infinite) ? /*INFINITY*/ 1.0 : 1.0;
    glVertex3d(-size, -size, 0.0);
    glVertex3d(size, -size, 0.0);
    glVertex3d(size, size, 0.0);
    glVertex3d(-size, size, 0.0);
    glEnd();
    glPopMatrix();
}

//------------------------------------------------------------------------------
// intersect with plane
void Plane::intersect(const Ray &ray, Intersects &intersects) const {
    Ray line;
    line = _transform.inverse().multiply(ray);
    double a = line.direction()(Z);
    double b = line.position()(Z);
    if (fabs(a) >= EPSILON) {
        double lambda = -b / a;
        double x = (line.position() + lambda * line.direction())(X);
        double y = (line.position() + lambda * line.direction())(Y);
        if (_infinite || (fabs(x) <= 1.0 && fabs(y) <= 1.0)) {
            if (a < 0.0) {
                intersects().push_back(Intersects::Intersect(lambda, this));
            }
            else {
                intersects().push_back(Intersects::Intersect(-INFINITY, this));
                intersects().push_back(Intersects::Intersect(lambda, this));
            }
        }
    }
}

//------------------------------------------------------------------------------
// normal to plane
Vectors Plane::normal(const Vectors &/*intersect*/) const {
    return Vectors(0.0, 0.0, 1.0, 0.0);
}

//------------------------------------------------------------------------------
