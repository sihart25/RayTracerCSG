//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Camera.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#pragma hdrstop
#include "Camera.h"
#include "Reader.h"
#include "Vectors.h"
#include "Transform.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
Camera *Camera::_camera = 0;

//------------------------------------------------------------------------------
// clear camera
void Camera::clear() {
    _camera = 0;
}

//------------------------------------------------------------------------------
// static function to read camera
bool Camera::read(istream &in, string &token, vector<Camera *> &cameras) {
    if (token == "Camera") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing camera opening brace");
        }
        Camera *camera = new Camera();
        cameras.push_back(camera);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (token == "Rotation") {
                camera->_rotation.readDirection(in);
            }
            else if (token == "Distance") {
                in >> camera->_distance;
            }
            else if (token == "Centre") {
                camera->_centre.readPosition(in);
            }
            else if (token == "Position") {
                camera->_position.readPosition(in);
            }
            else if (token == "Direction") {
                camera->_direction.readDirection(in);
            }
            else if (token == "Up") {
                camera->_up.readDirection(in);
            }
            else if (token == "FieldOfView") {
                in >> camera->_fieldOfView;
            }
            else if (token == "Scale") {
                in >> camera->_scale;
            }
            else {
                throw string("Error : Invalid camera attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// static function to find next camera
void Camera::next(vector<Camera *> &_cameras) {
    if (_cameras.empty()) {
        _cameras.push_back(new Camera());
    }
    bool next = false;
    for (vector<Camera *>::const_iterator camera = _cameras.begin(); camera != _cameras.end();
        ++camera) {
        if (_camera == *camera) {
            next = true;
        }
        else if (next) {
            _camera = *camera;
            return;
        }
    }
    _camera = *_cameras.begin();
}

//------------------------------------------------------------------------------
// static function to move camera
void Camera::move(const Vectors &rotation, double distance, const Vectors &centre) {
    _camera->_rotation += rotation;
    _camera->_distance += _camera->_scale * distance;
    _camera->_centre += _camera->_scale * centre;
}

//------------------------------------------------------------------------------
// static function to transform by camera
void Camera::transform(Transform &transform) {
    _camera->transform(transform, true);
}

//------------------------------------------------------------------------------
// transform by this camera
void Camera::transform(Transform &transform, bool /*dummy*/) const {
    // spherical coordinate camera model
    transform.translate(Vectors(0.0, 0.0, _centre(Z)));
    transform.translate(Vectors(0.0, 0.0, -_distance));
    transform.rotate(-_rotation(Z), Vectors(0.0, 0.0, 1.0));
    transform.rotate(-_rotation(Y), Vectors(1.0, 0.0, 0.0));
    transform.rotate(-_rotation(X), Vectors(0.0, 1.0, 0.0));
    transform.translate(-_centre);
    // conventional camera model
    Vectors n = Vectors(-_direction.unit());
    Vectors u = Vectors(_up.cross(n).unit());
    Vectors v = Vectors(n.cross(u).unit());
    Vectors d = Vectors(-_position.dot(u), -_position.dot(v), -_position.dot(n));
    double angle = acos((u(X) + v(Y) + n(Z) - 1.0) / 2.0);
    double rsin = sin(angle);
    rsin = (fabs(rsin) < EPSILON) ? 1.0 : 1.0 / rsin;
    Vectors axis = Vectors(n(Y) - v(Z), u(Z) - n(X), v(X) - u(Y)) * rsin / 2.0;
    transform.translate(d);
    transform.rotate(angle / PI * 180.0, axis);
}

//------------------------------------------------------------------------------
