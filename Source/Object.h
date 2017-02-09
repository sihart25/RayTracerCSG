//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Object.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Object_h
#define Object_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Transform.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Group;

    //------------------------------------------------------------------------------
    // class definition

    class Object {

    public:

        virtual ~Object() {}
        static bool read(istream &in, string &token, Group &group);
        virtual void update(Group &group, bool composite) = 0;
        virtual void transform(Transform &transform) = 0;
        virtual void preview() const = 0;
        friend ostream &operator<<(ostream &out, const Object &object) {
            object.write(out);
            return out;
        }

    protected:

        virtual void write(ostream &out) const { cout << "Object" << endl; }

    };

} // ComputerGraphics

#endif // Object_h

//------------------------------------------------------------------------------
