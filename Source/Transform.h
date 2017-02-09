//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Transform.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Transform_h
#define Transform_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include "Vectors.h"
#include "Matrix.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Transform {

    public:

        Transform &identity();
        Transform &scale(const Vectors &v);
        Transform &rotate(double theta, double phi, double psi);
        Transform &rotate(double angle, const Vectors &axis, bool unit = false);
        Transform &euler(double theta, double phi, double psi);
        Transform &translate(const Vectors &v);
        Transform &projection(double fieldOfView);
        Transform &preMultiply(const Transform &transform);
        Transform &postMultiply(const Transform &transform);
        const Matrix &forward() const { return _forward; }
        const Matrix &inverse() const { return _inverse; }
        friend ostream &operator<<(ostream &out, const Transform &transform) {
            transform.write(out);
            return out;
        }

    private:

        void write(ostream &out) const {
            out << "Transform" << endl << _forward << endl << _inverse;
        }

        Matrix _forward;
        Matrix _inverse;

        //------------------------------------------------------------------------------
        // nested class definition

        class Angle {

        public:

            Angle(double deg = 0.0) {
                _rad = deg * PI / 180.0;
                _c = cos(_rad);
                _s = sin(_rad);
            }
            double c() const { return _c; }
            double s() const { return _s; }

        private:

            double _rad;
            double _c;
            double _s;

        };

    };

} // ComputerGraphics

#endif // Transform_h

//------------------------------------------------------------------------------
