//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Sphere.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Sphere_h
#define Sphere_h

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

    class Sphere : public Primitive {

    public:

        Sphere() : _radius(1.0) {}
        static bool read(istream &in, string &token, Group &group);
        virtual void transform(Transform &transform);
        virtual void preview() const;
        virtual void intersect(const Ray &ray, Intersects &intersects) const;

    private:

        virtual Vectors normal(const Vectors &intersect) const;
        virtual void write(ostream &out) const { cout << "Sphere" << endl; Primitive::write(out); }

        double _radius;

    };

} // ComputerGraphics

#endif // Sphere_h

//------------------------------------------------------------------------------
