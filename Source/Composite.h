//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Composite.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Composite_h
#define Composite_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
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

    class Composite : public Shape {

    public:

        virtual ~Composite() {}
        static bool read(istream &in, string &token, Group &group);
        virtual void update(Group &group, bool composite) {
            Shape::update(group, composite);
            _group.composites().clear();
            _group.update(_group, true);
        }
        virtual void transform(Transform &transform) { _group.transform(transform); }
        virtual void preview() const { _group.preview(); }
        virtual void intersect(const Ray &ray, Intersects &intersects) const;

    protected:

        virtual bool inside(bool insideA, bool insideB) const { return false; }
        virtual void write(ostream &out) const { cout << "Composite" << endl; }

        Group _group;

    };

} // ComputerGraphics

#endif // Composite_h

//------------------------------------------------------------------------------
