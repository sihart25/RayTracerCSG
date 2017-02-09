//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Transformation.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#pragma hdrstop
#include "Transformation.h"
#include "Group.h"
#include "Reader.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read transformation
bool Transformation::read(istream &in, string &token, Group &group) {
    if (token == "Transformation") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing transformation opening brace");
        }
        Transformation *transformation = new Transformation();
        group.push_back(transformation);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (token == "Translate") {
                transformation->_translate.readDirection(in);
            }
            else if (token == "Axis") {
                transformation->_axis.readDirection(in);
            }
            else if (token == "Angle") {
                in >> transformation->_angle;
            }
            else if (token == "Spin") {
                in >> transformation->_spin;
            }
            else if (token == "PolarAngle") {
                in >> transformation->_polarTheta >> transformation->_polarPhi >>
                    transformation->_polarAngle;
            }
            else if (token == "PolarSpin") {
                in >> transformation->_polarSpin;
            }
            else if (token == "EulerAngle") {
                in >> transformation->_theta >> transformation->_phi >> transformation->_psi;
            }
            else if (token == "EulerSpin") {
                in >> transformation->_thetaSpin >> transformation->_phiSpin >> transformation->_psiSpin;
            }
            else if (token == "Scale") {
                transformation->_scale.readDirection(in);
            }
            else {
                throw string("Error : Invalid transformation attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// transform by this transformation
void Transformation::transform(Transform &transform) {
    transform.translate(_translate);
    transform.rotate(_angle, _axis);
    transform.rotate(_polarTheta, _polarPhi, _polarAngle);
    transform.euler(_theta, _phi, _psi);
    transform.scale(_scale);
    spin(_angle, _spin);
    spin(_polarAngle, _polarSpin);
    spin(_theta, _thetaSpin);
    spin(_phi, _phiSpin);
    spin(_psi, _psiSpin);
}

//------------------------------------------------------------------------------
// spin an angle
void Transformation::spin(double &angle, double spin) const {
    angle += spin;
    angle -= 360.0 * floor(angle / 360.0);
}

//------------------------------------------------------------------------------
