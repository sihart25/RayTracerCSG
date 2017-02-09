//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Scene.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <gl/glut.h>
#pragma hdrstop
#include "Scene.h"
#include "Reader.h"
#include "Group.h"
#include "Transform.h"
#include "Colour.h"
#include "Light.h"
#include "Ray.h"
#include "Vectors.h"
#include "Intersects.h"
#include "Shape.h"
#include "Primitive.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read scene
void Scene::read(const string &filename) {
    Reader::read(filename, _group, _screen);
    next();
}

//------------------------------------------------------------------------------
// update scene
void Scene::update() {
    // clear and update containers of lights, shapes and primitives
    Group::lights().clear();
    Group::shapes().clear();
    Group::primitives().clear();
    _group.update(_group, false);
    // transform screen and groups
    Transform transform;
    _screen.transform(transform);
    _group.transform(transform);
}

//------------------------------------------------------------------------------
// preview scene
void Scene::preview() const {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(_screen.fieldOfView(), _screen.aspectRatio(), 0.1, INFINITY);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background()(R), background()(G), background()(B), background()(A));
    for (int count = 0; count < GL_LIGHTS; ++count) {
        glDisable(GL_LIGHT[count]);
    }
    Light::count() = 0;
    _group.preview();
}

//------------------------------------------------------------------------------
// render scene
void Scene::render(int recursion, bool reflection, bool shadow, bool refraction, int samples /*= 1*/)
    const {
    srand(0);
    double dX = _screen.aspectRatio() / (double)width();
    double dY = 1.0 / (double)height();
    Colour *screen = _screen();
    double z = -0.5 / tan(0.5 * _screen.fieldOfView() / 180.0 * PI);
    for (int v = -height() / 2; v < height() / 2; ++v) {
        for (int u = -width() / 2; u < width() / 2; ++u) {
            *screen = Colour();
            for (int sample = 0; sample < samples * samples; ++sample) {
                double dU = 0.5;
                double dV = 0.5;
                if (sample) {
                    dU = (sample % samples + (double)rand() / (double)RAND_MAX) / (double)samples;
                    dV = (sample / samples + (double)rand() / (double)RAND_MAX) / (double)samples;
                }
                Ray ray;
                ray.direction() = Vectors(((double)u + dU) * dX, ((double)v + dV) * dY, z, 0.0);
                Colour colour(1.0, 1.0, 1.0);
                colour = cast(ray, colour, recursion, reflection, shadow, refraction);
                *screen += colour;
            }
            *screen++ /= samples ? (double)(samples * samples) : 1.0;
        }
    }
}

//------------------------------------------------------------------------------
// cast ray into scene
Colour Scene::cast(const Ray &ray, const Colour &colour, int recursion, bool reflection, bool shadow,
    bool refraction) const {
    Intersects::Intersect nearIntersect;
    Intersects intersects;
    for (vector<Shape *>::const_iterator shape = _group.shapes().begin();
        shape != _group.shapes().end(); ++shape) {
        intersects().clear();
        (*shape)->intersect(ray, intersects);
        for (vector<Intersects::Intersect>::const_iterator intersect = intersects().begin();
            intersect != intersects().end(); ++intersect) {
            if ((*intersect)() > EPSILON) {
                if ((*intersect)() < nearIntersect()) {
                    nearIntersect = *intersect;
                }
                break;
            }
        }
    }
    Colour returnedColour;
    if (nearIntersect.primitive()) {
        Vectors intersect(ray.position() + nearIntersect() * ray.direction());
        Colour reflectColour;
        Colour refractColour;
        if (recursion-- > 0) {
            if (reflection) {
                Ray reflectRay;
                Colour nestedColour(colour);
                if (nearIntersect.primitive()->reflect(intersect, ray, reflectRay, nestedColour)) {
                    reflectColour =
                        cast(reflectRay, nestedColour, recursion, reflection, shadow, refraction);
                }
            }
            if (refraction) {
                Ray refractRay;
                Colour nestedColour(colour);
                if (nearIntersect.primitive()->refract(intersect, ray, refractRay, nestedColour)) {
                    refractColour =
                        cast(refractRay, nestedColour, recursion, reflection, shadow, refraction);
                }
            }
        }
        returnedColour =
            nearIntersect.primitive()->light(intersect, _group, reflectColour, refractColour, shadow);
    }
    else {
        returnedColour = _screen.background();
    }
    return returnedColour;
}

//------------------------------------------------------------------------------
// display scene
void Scene::display() const {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5, 0.5, -0.5, 0.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(background()(R), background()(G), background()(B), background()(A));
    double dX = 1.0 / (double)width();
    double dY = 1.0 / (double)height();
    Colour *colour = _screen();
    for (int i = -height() / 2; i < height() / 2; ++i) {
        for (int j = -width() / 2; j < width() / 2; ++j) {
            GLfloat array[COLOURS];
            glColor4fv((colour++)->toGLfloat(array));
            glRectd(j * dX, i * dY, (j + 1) * dX, (i + 1) * dY);
        }
    }
}

//------------------------------------------------------------------------------
