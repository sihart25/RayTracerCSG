//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Cylinder.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <gl/glut.h>
#pragma hdrstop
#include "Cylinder.h"
#include "Group.h"
#include "Reader.h"
#include "Disc.h"
#include "Transform.h"
#include "Ray.h"
#include "Intersects.h"
#include "Vectors.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read cylinder
bool Cylinder::read(istream &in, string &token, Group &group) {
    if (token == "Cylinder") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing cylinder opening brace");
        }
        Cylinder *cylinder = new Cylinder();
        group.push_back(cylinder);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (cylinder->_material.read(in, token)) {}
            else if (token == "Radius") {
                in >> cylinder->_radius;
            }
            else if (token == "Height") {
                in >> cylinder->_height;
            }
            else if (token == "Centre") {
                cylinder->_centre.readPosition(in);
            }
            else if (token == "Top") {
                in >> boolalpha >> cylinder->_top >> noboolalpha;
            }
            else if (token == "Bottom") {
                in >> boolalpha >> cylinder->_bottom >> noboolalpha;
            }
            else {
                throw string("Error : Invalid cylinder attribute = " + token);
            }
        }
        if (cylinder->_top) {
            Disc *disc = new Disc(cylinder->_transform, cylinder->_material,
                cylinder->_centre + Vectors(0.0, 0.0, cylinder->_height), cylinder->_radius);
            group.push_back(disc);
        }
        if (cylinder->_bottom) {
            Disc *disc = new Disc(cylinder->_transform, cylinder->_material,
                cylinder->_centre, cylinder->_radius);
            group.push_back(disc);
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform cylinder
void Cylinder::transform(Transform &transform) {
    _transform = transform;
    _transform.translate(_centre);
    _transform.scale(Vectors(_radius, _radius, _height));
}

//------------------------------------------------------------------------------
// preview cylinder
void Cylinder::preview() const {
    _material.preview();
    glPushMatrix();
    glMultMatrixd(_transform.forward().transpose()());
    GLUquadricObj *cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_FILL);
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    gluCylinder(cylinder, 1.0, 1.0, 1.0, 100, 50);
    gluDeleteQuadric(cylinder);
    glPopMatrix();
}

//------------------------------------------------------------------------------
// intersect with cylinder
void Cylinder::intersect(const Ray &ray, Intersects &intersects) const {
    Ray line;
    line = _transform.inverse().multiply(ray);
    Vectors k(0.0, 0.0, 1.0, 0.0);
    Vectors direction(line.direction().cross(k));
    Vectors position(line.position().cross(k));
    double a = direction.dot(direction);
    double b = direction.dot(position) * 2.0;
    double c = position.dot(position) - 1.0;
    double root = b * b - 4.0 * a * c;
    if (fabs(a) >= EPSILON && root >= 0.0) {
        double lambda = (-b - sqrt(root)) / (2.0 * a);
        double z = (line.position() + lambda * line.direction())(Z);
        if (z >= 0.0 && z <= 1.0) {
            intersects().push_back(Intersects::Intersect(lambda, this));
        }
        else {
            double lambda = (-b + sqrt(root)) / (2.0 * a);
            double z = (line.position() + lambda * line.direction())(Z);
            if (z >= 0.0 && z <= 1.0) {
                intersects().push_back(Intersects::Intersect(lambda, this));
            }
        }
    }
}

//------------------------------------------------------------------------------
// normal to cylinder
Vectors Cylinder::normal(const Vectors &intersect) const {
    return Vectors(intersect(X), intersect(Y), 0.0, 0.0);
}

//------------------------------------------------------------------------------
