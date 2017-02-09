//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Primitive.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#pragma hdrstop
#include "Primitive.h"
#include "Group.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Disc.h"
#include "Triangle.h"
#include "Mesh.h"
#include "Vectors.h"
#include "Ray.h"
#include "Colour.h"
#include "Light.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read primitive
bool Primitive::read(istream &in, string &token, Group &group) {
    if (Sphere::read(in, token, group)) {
        return true;
    }
    else if (Cylinder::read(in, token, group)) {
        return true;
    }
    else if (Plane::read(in, token, group)) {
        return true;
    }
    else if (Disc::read(in, token, group)) {
        return true;
    }
    else if (Triangle::read(in, token, group)) {
        return true;
    }
    else if (Mesh::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// reflect from primitive
bool Primitive::reflect(const Vectors &intersect, const Ray &ray, Ray &reflect, Colour &colour) const {
    colour *= _material.reflection();
    if (colour(R) > EPSILON || colour(G) > EPSILON || colour(B) > EPSILON) {
        // the intersect is transformed to object coordinates by the inverse matrix
        Vectors position(intersect);
        position = _transform.inverse().multiply(position);
        // the normal is transformed to eye coordinates by the inverse transpose matrix
        Vectors direction(normal(position));
        direction = _transform.inverse().transpose().multiply(direction).normalize();
        reflect = Ray(intersect, -ray.direction() - 2.0 *
            direction.cross(-ray.direction()).cross(direction));
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// refract from primitive
bool Primitive::refract(const Vectors &intersect, const Ray &ray, Ray &refract, Colour &colour) const {
    colour *= _material.refraction();
    if (colour(R) > EPSILON || colour(G) > EPSILON || colour(B) > EPSILON) {
        // the intersect is transformed to object coordinates by the inverse matrix
        Vectors position(intersect);
        position = _transform.inverse().multiply(position);
        // the normal is transformed to eye coordinates by the inverse transpose matrix
        Vectors direction(normal(position));
        direction = _transform.inverse().transpose().multiply(direction).normalize();
        // still to do
        // add refraction here...
        Vectors refractDirection(ray.direction());
        refract = Ray(intersect, refractDirection);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// light primitive
Colour Primitive::light(const Vectors &intersect, const Group &group,
                  const Colour &reflect, const Colour &refract, bool shadows) const {
    Colour colour = reflect * _material.reflection() + refract * _material.refraction();
    // the intersect is transformed to object coordinates by the inverse matrix
    Vectors position(intersect);
    position = _transform.inverse().multiply(position);
    // the normal is transformed to eye coordinates by the inverse transpose matrix
    Vectors direction(normal(position));
    direction = _transform.inverse().transpose().multiply(direction).normalize();
    // the normal is negated for two sided lighting
    Vectors cameraVector(0.0, 0.0, 0.0, 1.0);
    cameraVector -= intersect;
    if (cameraVector.normalize().dot(direction) < 0.0) {
        direction.negate();
    }
    for (vector<Light *>::const_iterator light = group.lights().begin(); light != group.lights().end();
        ++light) {
        colour += (*light)->ambient() * _material.ambient();
        Vectors lightVector((*light)->position());
        // point or directional light source
        double distance = INFINITY;
        if (!(*light)->infinite()) {
            lightVector -= intersect;
            distance = 1.0;
        }
        // test primitive is closer than light for shadows
        Ray ray(intersect, lightVector);
        if (!shadows || shadow(ray, group, distance)) {
            double intensity = lightVector.normalize().dot(direction);
            // apply diffuse and specular lighting if light is visible at the intersect
            if (intensity >= 0.0) {
                colour += intensity * (*light)->diffuse() * _material.diffuse();
                double intensity = (lightVector + cameraVector).unit().dot(direction);
                if (intensity >= 0.0) {
                    colour += pow(intensity, _material.shininess()) *
                              (*light)->specular() * _material.specular();
                }
            }
        }
    }
    colour += _material.emission();
    return colour;
}

//------------------------------------------------------------------------------
// shadow primitive
bool Primitive::shadow(const Ray &ray, const Group &group, double distance) const {
    Intersects intersects;
    for (vector<Shape *>::const_iterator shape = group.shapes().begin(); shape != group.shapes().end();
        ++shape) {
        intersects().clear();
        (*shape)->intersect(ray, intersects);
        for (vector<Intersects::Intersect>::const_iterator intersect = intersects().begin();
            intersect != intersects().end(); ++intersect) {
            if ((*intersect)() > EPSILON) {
                if ((*intersect)() < distance) {
                    return false;
                }
                break;
            }
        }
    }
    return true;
}

//------------------------------------------------------------------------------
