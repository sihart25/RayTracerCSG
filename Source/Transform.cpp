//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Transform.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Transform.h"
#include "Vectors.h"
#include "Matrix.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// set this transform to the identity transform
Transform &Transform::identity() {
    _forward.identity();
    _inverse.identity();
    return *this;
}

//------------------------------------------------------------------------------
// scale this transform
Transform &Transform::scale(const Vectors &v) {
    Matrix m;
    m(X, X) = v(X);
    m(Y, Y) = v(Y);
    m(Z, Z) = v(Z);
    _forward.postMultiply(m);
    m(X, X) = (fabs(v(X)) < EPSILON) ? 0.0 : 1.0 / v(X);
    m(Y, Y) = (fabs(v(Y)) < EPSILON) ? 0.0 : 1.0 / v(Y);
    m(Z, Z) = (fabs(v(Z)) < EPSILON) ? 0.0 : 1.0 / v(Z);
    _inverse.preMultiply(m);
    return *this;
}

//------------------------------------------------------------------------------
// rotate this transform about an axis defined by spherical polar angles
Transform &Transform::rotate(double theta, double phi, double angle) {
    Angle t(theta);
    Angle p(phi);
    rotate(angle, Vectors(t.s() * p.c(), t.s() * p.s(), t.c()), true);
    return *this;
}

//------------------------------------------------------------------------------
// rotate this transform about an axis
Transform &Transform::rotate(double angle, const Vectors &axis, bool unit /*= false*/) {
    Matrix m;
    Angle a(angle);
    Vectors v = axis;
    if (!unit) {
        v.normalize();
    }
    m(X, X) = a.c() + (1.0 - a.c()) * v(X) * v(X);
    m(X, Y) = (1.0 - a.c()) * v(Y) * v(X) - a.s() * v(Z);
    m(X, Z) = (1.0 - a.c()) * v(Z) * v(X) + a.s() * v(Y);
    m(Y, X) = (1.0 - a.c()) * v(X) * v(Y) + a.s() * v(Z);
    m(Y, Y) = a.c() + (1.0 - a.c()) * v(Y) * v(Y);
    m(Y, Z) = (1.0 - a.c()) * v(Z) * v(Y) - a.s() * v(X);
    m(Z, X) = (1.0 - a.c()) * v(X) * v(Z) - a.s() * v(Y);
    m(Z, Y) = (1.0 - a.c()) * v(Y) * v(Z) + a.s() * v(X);
    m(Z, Z) = a.c() + (1.0 - a.c()) * v(Z) * v(Z);
    _forward.postMultiply(m);
    m = m.transpose();
    _inverse.preMultiply(m);
    return *this;
}

//------------------------------------------------------------------------------
// rotate this transform by euler angles
Transform &Transform::euler(double theta, double phi, double psi) {
    Matrix m;
    Angle a(theta);
    Angle b(phi);
    Angle c(psi);
    m(X, X) = b.c() * c.c();
    m(X, Y) = a.s() * b.s() * c.c() - a.c() * c.s();
    m(X, Z) = a.c() * b.s() * c.c() + a.s() * c.s();
    m(Y, X) = b.c() * c.s();
    m(Y, Y) = a.s() * b.s() * c.s() + a.c() * c.c();
    m(Y, Z) = a.c() * b.s() * c.s() - a.s() * c.c();
    m(Z, X) = -b.s();
    m(Z, Y) = a.s() * b.c();
    m(Z, Z) = a.c() * b.c();
    _forward.postMultiply(m);
    m = m.transpose();
    _inverse.preMultiply(m);
    return *this;
}

//------------------------------------------------------------------------------
// translate this transform
Transform &Transform::translate(const Vectors &v) {
    Matrix m;
    m(X, W) = v(X);
    m(Y, W) = v(Y);
    m(Z, W) = v(Z);
    _forward.postMultiply(m);
    m(X, W) = -v(X);
    m(Y, W) = -v(Y);
    m(Z, W) = -v(Z);
    _inverse.preMultiply(m);
    return *this;
}

//------------------------------------------------------------------------------
// projection of this transform
Transform &Transform::projection(double fieldOfView) {
    Matrix m;
    m(Z, Z) = 0.0;
    m(W, Z) = -tan(0.5 * fieldOfView / 180.0 * PI) / 0.5;
    m(W, W) = 0.0;
    _forward.preMultiply(m);
    return *this;
}

//------------------------------------------------------------------------------
// pre-multiply this transform
Transform &Transform::preMultiply(const Transform &transform) {
    _forward.preMultiply(transform._forward);
    _inverse.postMultiply(transform._inverse);
    return *this;
}

//------------------------------------------------------------------------------
// post-multiply this transform
Transform &Transform::postMultiply(const Transform &transform) {
    _forward.postMultiply(transform._forward);
    _inverse.preMultiply(transform._inverse);
    return *this;
}

//------------------------------------------------------------------------------
