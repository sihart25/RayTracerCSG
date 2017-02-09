//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Disc.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Disc_h
#define Disc_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Primitive.h"
#include "Transform.h"
#include "Material.h"
#include "Vectors.h"
#include "Group.h"
#include "Ray.h"
#include "Intersects.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Disc : public Primitive {

    public:

        Disc() : _radius(1.0) {}
        Disc(const Transform &transform, const Material &material, const Vectors &centre,
            double radius) : Primitive(transform, material, centre), _radius(radius) {}
        static bool read(istream &in, string &token, Group &group);
        virtual void transform(Transform &transform);
        virtual void preview() const;
        virtual void intersect(const Ray &ray, Intersects &intersects) const;

    private:

        virtual Vectors normal(const Vectors &intersect) const;
        virtual void write(ostream &out) const { cout << "Disc" << endl; Primitive::write(out); }

        double _radius;

    };

} // ComputerGraphics

#endif // Disc_h

//------------------------------------------------------------------------------
