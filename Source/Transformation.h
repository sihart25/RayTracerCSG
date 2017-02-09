//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Transformation.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Transformation_h
#define Transformation_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Object.h"
#include "Group.h"
#include "Transform.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Transformation : public Object {

    public:

        Transformation() : _translate(0.0, 0.0, 0.0), _axis(0.0, 0.0, 1.0), _angle(0.0), _spin(0.0),
            _polarTheta(0.0), _polarPhi(0.0), _polarAngle(0.0), _polarSpin(0.0),
            _theta(0.0), _phi(0.0), _psi(0.0), _thetaSpin(0.0), _phiSpin(0.0), _psiSpin(0.0),
            _scale(1.0, 1.0, 1.0) {}
        static bool read(istream &in, string &token, Group &group);
        virtual void update(Group &group, bool composite) {}
        virtual void transform(Transform &transform);
        virtual void preview() const {}

    private:

        void spin(double &angle, double spin) const;
        virtual void write(ostream &out) const { out << "Transformation" << endl; }

        Vectors _translate;
        Vectors _axis;
        double _angle;
        double _spin;
        double _polarTheta;
        double _polarPhi;
        double _polarAngle;
        double _polarSpin;
        double _theta;
        double _phi;
        double _psi;
        double _thetaSpin;
        double _phiSpin;
        double _psiSpin;
        Vectors _scale;

    };

} // ComputerGraphics

#endif // Transformation_h

//------------------------------------------------------------------------------
