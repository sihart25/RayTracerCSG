//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Intersects.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Intersects_h
#define Intersects_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Primitive;

    //------------------------------------------------------------------------------
    // class definition

    class Intersects {

    public:

        //------------------------------------------------------------------------------
        // nested class definition

        class Intersect {

        public:

            Intersect(double intersect = INFINITY, const Primitive *primitive = 0) :
                _intersect(intersect), _primitive(primitive) {}
            double operator()() const { return _intersect; }
            const Primitive *primitive() const { return _primitive; }
            bool operator<(const Intersect &intersect) const {
                return _intersect < intersect._intersect;
            }

        private:

            double _intersect;
            const Primitive *_primitive;

        };

        vector<Intersect> &operator()() { return _intersects; }

    private:

        vector<Intersect> _intersects;

    };

} // ComputerGraphics

#endif // Intersects_h

//------------------------------------------------------------------------------
