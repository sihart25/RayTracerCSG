//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Cylinder.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Cylinder_h
#define Cylinder_h

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

    class Cylinder : public Primitive {

    public:

        Cylinder() : _radius(1.0), _height(1.0), _top(true), _bottom(true) {}
        static bool read(istream &in, string &token, Group &group);
        virtual void transform(Transform &transform);
        virtual void preview() const;
        virtual void intersect(const Ray &ray, Intersects &intersects) const;

    private:

        virtual Vectors normal(const Vectors &intersect) const;
        virtual void write(ostream &out) const { cout << "Cylinder" << endl; Primitive::write(out); }

        double _radius;
        double _height;
        bool _top;
        bool _bottom;

    };

} // ComputerGraphics

#endif // Cylinder_h

//------------------------------------------------------------------------------
