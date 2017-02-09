//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Screen.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Screen_h
#define Screen_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Colour.h"
#include "Constants.h"
#include "Camera.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Screen {

    public:

        Screen(int width = WIDTH, int height = HEIGHT,
            const Colour &background = Colour(0.0, 0.0, 0.0, 1.0)) :
            _width(width), _height(height), _background(background) {
            _screen = new Colour[(long)_height * (long)_width];
        }
        ~Screen() { erase(); }
        void clear();
        bool read(istream &in, string &token);
        void write(const string &filename);
        void resize(int width, int height);
        int width() const { return _width; }
        int height() const { return _height; }
        double aspectRatio() const { return (double)_width / (double)(_height ? _height : 1); }
        const Colour &background() const { return _background; }
        Colour *operator()() const { return _screen; }
        double fieldOfView() const { return Camera::fieldOfView(); }
        void next() { Camera::next(_cameras); }
        void move(const Vectors &rotation, double distance, const Vectors &centre) {
            Camera::move(rotation, distance, centre);
        }
        void transform(Transform &transform) const { Camera::transform(transform); }

    private:

        Screen(const Screen &screen);
        Screen &operator=(const Screen &screen);
        void erase();

        int _width;
        int _height;
        Colour _background;
        Colour *_screen;
        vector<Camera *> _cameras;

    };

} // ComputerGraphics

#endif // Screen_h

//------------------------------------------------------------------------------
