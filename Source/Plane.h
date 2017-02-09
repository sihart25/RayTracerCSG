//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Plane.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Plane_h
#define Plane_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Primitive.h"
#include "Group.h"
#include "Transform.h"
#include "Ray.h"
#include "Intersects.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Plane : public Primitive {

    public:

        Plane() : _width(1.0), _height(1.0), _infinite(true), _normal(0.0, 0.0, 1.0, 0.0),
            _up(0.0, 1.0, 0.0, 0.0) {}
        static bool read(istream &in, string &token, Group &group);
        virtual void transform(Transform &transform);
        virtual void preview() const;
        virtual void intersect(const Ray &ray, Intersects &intersects) const;

    private:

        virtual Vectors normal(const Vectors &intersect) const;
        virtual void write(ostream &out) const { cout << "Plane" << endl; Primitive::write(out); }

        double _width;
        double _height;
        bool _infinite;
        Vectors _normal;
        Vectors _up;

    };

} // ComputerGraphics

#endif // Plane_h

//------------------------------------------------------------------------------
