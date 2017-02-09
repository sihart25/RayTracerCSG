//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Union.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Union_h
#define Union_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Composite.h"
#include "Group.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Union : public Composite {

    public:

        static bool read(istream &in, string &token, Group &group);

    protected:

        virtual bool inside(bool insideA, bool insideB) const { return insideA || insideB; }
        virtual void write(ostream &out) const { cout << "Union" << endl; }

    };

} // ComputerGraphics

#endif // Union_h

//------------------------------------------------------------------------------
