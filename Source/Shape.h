//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Shape.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Shape_h
#define Shape_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Object.h"
#include "Group.h"
#include "Transform.h"
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

    class Shape : public Object {

    public:

        virtual ~Shape() {}
        static bool read(istream &in, string &token, Group &group);
        virtual void update(Group &group, bool composite) = 0;
        virtual void transform(Transform &transform) = 0;
        virtual void preview() const = 0;
        virtual void intersect(const Ray &ray, Intersects &intersects) const = 0;

    protected:

        virtual void write(ostream &out) const { cout << "Shape" << endl; }

    };

} // ComputerGraphics

#endif // Shape_h

//------------------------------------------------------------------------------
