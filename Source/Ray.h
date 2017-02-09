//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Ray.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Ray_h
#define Ray_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Ray {

    public:

        Ray(const Vectors &position = Vectors(0.0, 0.0, 0.0, 1.0),
            const Vectors &direction = Vectors(0.0, 0.0, -1.0, 0.0)) {
            _position.setPosition(position);
            _direction.setDirection(direction);
        }
        const Vectors &position() const { return _position; }
        const Vectors &direction() const { return _direction; }
        Vectors &position() { return _position; }
        Vectors &direction() { return _direction; }
        double distance(const Vectors &vector) const;
        double distance(const Ray &ray) const;
        Vectors intersection(const Ray &ray) const;
        Ray &normalize();
        Ray unit() const;
        Ray &negate();
        Ray operator-() const;
        friend ostream &operator<<(ostream &out, const Ray &ray);

    private:

        void write(ostream &out) const;

        Vectors _position;
        Vectors _direction;

    };

} // ComputerGraphics

#endif // Ray_h

//------------------------------------------------------------------------------
