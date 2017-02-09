//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Control.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Control_h
#define Control_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Scene.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Control {

    public:

        Control() : _render(false), _wireframe(false),
            _shadow(false), _reflection(false), _refraction(false), _recursion(10), _samples(1),
            _position(true), _rotation(true), _motionX(0), _motionY(0) {}
        ~Control() { cout << "Control object destructed" << endl; }
        void initialize(int argc, char **argv);
        void menu() const;
        void display();
        void reshape(int width, int height);
        void keyboard(unsigned char key, int x, int y);
        void special(int key, int x, int y);
        void mouse(int button, int state, int x, int y);
        void motion(int x, int y);
        void idle();

    private:

        void read();
        void render(bool update);

        Scene _scene;
        string _fin;
        string _fout;
        bool _render;
        bool _wireframe;
        bool _shadow;
        bool _reflection;
        bool _refraction;
        int _recursion;
        int _samples;
        bool _position;
        bool _rotation;
        int _motionX;
        int _motionY;

    };

} // ComputerGraphics

#endif // Control_h

//------------------------------------------------------------------------------
