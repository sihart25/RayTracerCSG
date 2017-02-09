//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Sphere.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <gl/glut.h>
#pragma hdrstop
#include "Sphere.h"
#include "Group.h"
#include "Reader.h"
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
// static read sphere
bool Sphere::read(istream &in, string &token, Group &group) {
    if (token == "Sphere") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing sphere opening brace");
        }
        Sphere *sphere = new Sphere();
        group.push_back(sphere);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (sphere->_material.read(in, token)) {}
            else if (token == "Radius") {
                in >> sphere->_radius;
            }
            else if (token == "Centre") {
                sphere->_centre.readPosition(in);
            }
            else {
                throw string("Error : Invalid sphere attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform sphere
void Sphere::transform(Transform &transform) {
    _transform = transform;
    _transform.translate(_centre);
    _transform.scale(Vectors(_radius, _radius, _radius));
}

//------------------------------------------------------------------------------
// preview sphere
void Sphere::preview() const {
    _material.preview();
    glPushMatrix();
    glMultMatrixd(_transform.forward().transpose()());
    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, 1.0, 100, 50);
    gluDeleteQuadric(sphere);
    glPopMatrix();
}

//------------------------------------------------------------------------------
// intersect with sphere
void Sphere::intersect(const Ray &ray, Intersects &intersects) const {
    Ray line;
    line = _transform.inverse().multiply(ray);
    double a = line.direction().dot(line.direction());
    double b = line.direction().dot(line.position()) * 2.0;
    double c = line.position().dot(line.position()) - 1.0;
    double root = b * b - 4.0 * a * c;
    if (fabs(a) >= EPSILON && root >= 0.0) {
        root = sqrt(root);
        intersects().push_back(Intersects::Intersect((-b - root) / (2.0 * a), this));
        intersects().push_back(Intersects::Intersect((-b + root) / (2.0 * a), this));
    }
}

//------------------------------------------------------------------------------
// normal to sphere
Vectors Sphere::normal(const Vectors &intersect) const {
    return Vectors(intersect(X), intersect(Y), intersect(Z), 0.0);
}

//------------------------------------------------------------------------------
