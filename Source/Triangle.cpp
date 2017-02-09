//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Triangle.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <gl/glut.h>
#pragma hdrstop
#include "Triangle.h"
#include "Group.h"
#include "Reader.h"
#include "Transform.h"
#include "Vectors.h"
#include "Ray.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read triangle
bool Triangle::read(istream &in, string &token, Group &group) {
    if (token == "Triangle") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing triangle opening brace");
        }
        Triangle *triangle = new Triangle();
        group.push_back(triangle);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (triangle->_material.read(in, token)) {}
            else if (token == "VertexA") {
                triangle->_vertexA.readPosition(in);
            }
            else if (token == "VertexB") {
                triangle->_vertexB.readPosition(in);
            }
            else if (token == "VertexC") {
                triangle->_vertexC.readPosition(in);
            }
            else if (token == "Centre") {
                triangle->_centre.readPosition(in);
            }
            else {
                throw string("Error : Invalid triangle attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform triangle
void Triangle::transform(Transform &transform) {
    _transform = transform;
    _transform.translate(_centre);
}

//------------------------------------------------------------------------------
// preview triangle
void Triangle::preview() const {
    _material.preview();
    glPushMatrix();
    glMultMatrixd(_transform.forward().transpose()());
    glBegin(GL_TRIANGLES);
    if (_smooth) {
        glNormal3d(_normalA(X), _normalA(Y), _normalA(Z));
        glVertex3d(_vertexA(X), _vertexA(Y), _vertexA(Z));
        glNormal3d(_normalB(X), _normalB(Y), _normalB(Z));
        glVertex3d(_vertexB(X), _vertexB(Y), _vertexB(Z));
        glNormal3d(_normalC(X), _normalC(Y), _normalC(Z));
        glVertex3d(_vertexC(X), _vertexC(Y), _vertexC(Z));
    }
    else {
        Vectors n(normal(Vectors()));
        glNormal3d(n(X), n(Y), n(Z));
        glVertex3d(_vertexA(X), _vertexA(Y), _vertexA(Z));
        glVertex3d(_vertexB(X), _vertexB(Y), _vertexB(Z));
        glVertex3d(_vertexC(X), _vertexC(Y), _vertexC(Z));
    }
    glEnd();
    glPopMatrix();
}

//------------------------------------------------------------------------------
// intersect with triangle
void Triangle::intersect(const Ray &ray, Intersects &intersects) const {
    Ray line;
    line = _transform.inverse().multiply(ray);
    Vectors ab(_vertexB - _vertexA);
    Vectors ac(_vertexC - _vertexA);
    double denominator = line.direction().cross(ab).dot(ac);
    if (fabs(denominator) >= EPSILON) {
        Vectors pa(_vertexA - line.position());
        double reciprocal = 1.0 / denominator;
        double lambda = pa.cross(ab).dot(ac) * reciprocal;
        double beta = -pa.cross(ac).dot(line.direction()) * reciprocal;
        double gamma = pa.cross(ab).dot(line.direction()) * reciprocal;
        double alpha = 1.0 - beta - gamma;
        if (alpha >= 0.0 && beta >= 0.0 && gamma >= 0.0) {
            intersects().push_back(Intersects::Intersect(lambda, this));
        }
    }
}

//------------------------------------------------------------------------------
// normal to triangle
Vectors Triangle::normal(const Vectors &intersect) const {
    Vectors ab(_vertexB - _vertexA);
    Vectors ac(_vertexC - _vertexA);
    Vectors direction(ab.cross(ac));
    if (_smooth) {
        double denominator = direction.cross(ab).dot(ac);
        double reciprocal = (fabs(denominator) < EPSILON) ? 1.0 : 1.0 / denominator;
        Vectors pa(_vertexA - intersect);
        double beta = -pa.cross(ac).dot(direction) * reciprocal;
        double gamma = pa.cross(ab).dot(direction) * reciprocal;
        double alpha = 1.0 - beta - gamma;
        return alpha * _normalA + beta * _normalB + gamma * _normalC;
    }
    else {
        return direction;
    }
}

//------------------------------------------------------------------------------
