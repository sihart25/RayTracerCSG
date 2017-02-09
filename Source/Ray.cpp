//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Ray.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#pragma hdrstop
#include "Ray.h"
#include "Vectors.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// distance from this ray to a point
double Ray::distance(const Vectors &vector) const {
    return (vector - _position).cross(_direction).magnitude();
}

//------------------------------------------------------------------------------
// distance from this ray to another ray
double Ray::distance(const Ray &ray) const {
    // determine the perpendicular to and angle between this ray and another ray
    Vectors perp(_direction.cross(ray._direction));
    double sine = perp.magnitude();
    if (sine <= EPSILON) { // near parallel rays
        return (ray._position - _position).cross(_direction).magnitude();
    }
    else {
        return fabs((ray._position - _position).dot(perp /= sine));
    }
}

//------------------------------------------------------------------------------
// intersection of this ray with another ray
Vectors Ray::intersection(const Ray &ray) const {
    // determine the perpendicular to and angle between this ray and another ray
    Vectors perp(_direction.cross(ray._direction));
    double sine = perp.magnitude();
    if (sine <= EPSILON) { // near parallel rays
        return _position + 0.5 * (ray._position - _position);
    }
    else {
        // determine the ray coplanar to this ray and parallel to another ray
        double length = (ray._position - _position).dot(perp /= sine);
        Ray coplanar(ray._position - length * perp, ray._direction);
        // project to determine the intersection of this ray and the coplanar ray
        Vectors project = (coplanar._position - _position).
                          cross(_direction).cross(_direction);
        double lenA = (coplanar._position - _position).dot(project);
        double lenB = (coplanar._position + coplanar._direction - _position).dot(project);
        return coplanar._position + lenA / (lenA - lenB) * coplanar._direction +
               0.5 * length * perp;
    }
}

//------------------------------------------------------------------------------
// normalize this ray
Ray &Ray::normalize() {
    _direction.normalize();
    return *this;
}

//------------------------------------------------------------------------------
// unit vector of this ray
Ray Ray::unit() const {
    return Ray(_position, _direction.unit());
}

//------------------------------------------------------------------------------
// negate this ray
Ray &Ray::negate() {
    _direction.negate();
    return *this;
}

//------------------------------------------------------------------------------
// negative operator-
Ray Ray::operator-() const {
    return Ray(_position, -_direction);
}

//------------------------------------------------------------------------------
// stream out from this ray
void Ray::write(ostream &out) const {
    out << "(" << _position << "," << _direction << ")";
}

//------------------------------------------------------------------------------
// namespace definition
namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // stream out operator<<
    ostream &operator<<(ostream &out, const Ray &ray) {
        ray.write(out);
        return out;
    }

} // ComputerGraphics

//------------------------------------------------------------------------------
