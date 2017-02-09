//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Scene.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Scene_h
#define Scene_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Colour.h"
#include "Vectors.h"
#include "Ray.h"
#include "Screen.h"
#include "Group.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Scene {

    public:

        void read(const string &filename);
        void update();
        void preview() const;
        void render(int recursion, bool reflection, bool shadow, bool refraction, int samples = 1)
            const;
        void display() const;
        void write(const string &filename) { _screen.write(filename); }
        double width() const { return _screen.width(); }
        double height() const { return _screen.height(); }
        void resize(int width, int height) { _screen.resize(width, height); }
        const Colour &background() const { return _screen.background(); }
        void next() { _screen.next(); }
        void move(const Vectors &rotation, double distance, const Vectors &centre) {
            _screen.move(rotation, distance, centre);
        }

    private:

        Colour cast(const Ray &ray, const Colour &colour, int recursion, bool reflection, bool shadow,
            bool refraction) const;

        Screen _screen;
        Group _group;

    };

} // ComputerGraphics

#endif // Scene_h

//------------------------------------------------------------------------------
