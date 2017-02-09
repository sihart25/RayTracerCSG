//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Control.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <gl/glut.h>
#pragma hdrstop
#include "Control.h"
#include "Scene.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// initialize
void Control::initialize(int argc, char **argv) {
    if (argc != 3) {
        _fin = string("RayTracerCSG.txt");
        _fout = string("RayTracerCSG.bmp");
    }
    else {
        _fin = argv[1];
        _fout = argv[2];
    }
    read();
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);
    GLfloat ambient[] = {0.0, 0.0, 0.0, 0.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

//------------------------------------------------------------------------------
// menu
void Control::menu() const {
    cout << "Press <escape>               to exit program" << endl;
    cout << "Press <f1>                   to preview scene with solid surfaces" << endl;
    cout << "Press <f2>                   to preview scene with wire-frame surfaces" << endl;
    cout << "Press <f3>                   to ray-cast scene" << endl;
    cout << "Press <f4>                   to ray-cast scene with shadows" << endl;
    cout << "Press <f5>                   to ray-cast scene with shadows and refraction" << endl;
    cout << "Press <f6>                   to ray-trace scene" << endl;
    cout << "Press <f7>                   to ray-trace scene with shadows" << endl;
    cout << "Press <f8>                   to ray-trace scene with shadows and refraction" << endl;
    cout << "Press <f9>                   to write bitmap file" << endl;
    cout << "Press <f10>                  to select camera rotation and distance" << endl;
    cout << "Press <f11>                  to select camera centre" << endl;
    cout << "Press <f12>                  to change to next camera" << endl;
    cout << "Press <1,2,3,4,5,6,7,8,9,0>  to select number of reflections and refractions" << endl;
    cout << "Press <l,m,h>                to select number of samples per pixel" << endl;
    cout << "Press <space>                to read scene file" << endl;
    cout << "Press <left,right>           to adjust camera yaw rotation or x centre" << endl;
    cout << "Press <down,up>              to adjust camera pitch rotation or y centre" << endl;
    cout << "Press <pagedown,pageup>      to adjust camera roll rotation or z centre" << endl;
    cout << "Press <end,home>             to adjust camera distance" << endl;
    cout << "Press left mouse button      to adjust camera yaw and pitch rotation" << endl;
    cout << "Press right mouse button     to adjust camera roll rotation" << endl;
}

//------------------------------------------------------------------------------
// read
void Control::read() {
    _scene.read(_fin);
    glutReshapeWindow(_scene.width(), _scene.height());
    glViewport(0, 0, _scene.width(), _scene.height());
}

//------------------------------------------------------------------------------
// display
void Control::display() {
    if (!_render) {
        glPolygonMode(GL_FRONT_AND_BACK, !_wireframe ? GL_FILL : GL_LINE);
        _scene.preview();
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        _scene.display();
    }
    glutSwapBuffers();
}

//------------------------------------------------------------------------------
// render
void Control::render(bool update) {
    if (update) {
        _scene.update();
    }
    if (!_render) {
        glutSetWindowTitle(!_wireframe ? "OpenGL - Solid Preview" : "OpenGL - Wire-Frame Preview");
    }
    else {
        glutSetWindowTitle(_reflection ? "Ray Tracer - Rendering..." : "Ray Caster - Rendering...");
        clock_t start;
        start = clock();
        _scene.render(_recursion, _reflection, _shadow, _refraction, _samples);
        clock_t finish;
        finish = clock();
        double seconds = (double)(finish - start) / CLOCKS_PER_SEC;
        ostringstream oss;
        oss << setiosflags(ios::fixed) << setprecision(2);
        oss << (_reflection ? "Ray Tracer" : "Ray Caster") << " - Rendered in " << seconds << "s";
        glutSetWindowTitle(oss.str().c_str());
    }
    glutPostRedisplay();
}

//------------------------------------------------------------------------------
// reshape
void Control::reshape(int width, int height) {
    _scene.resize(width, height);
    glViewport(0, 0, width, height);
    render(false);
}

//------------------------------------------------------------------------------
// keyboard
void Control::keyboard(unsigned char key, int /*x*/, int /*y*/) {
    bool update = false;
    switch (key) {
        case 'l': {
            _samples = 1;
            break;
        }
        case 'm': {
            _samples = 2;
            break;
        }
        case 'h': {
            _samples = 3;
            break;
        }
        case '1': {
            _recursion = 1;
            break;
        }
        case '2': {
            _recursion = 2;
            break;
        }
        case '3': {
            _recursion = 3;
            break;
        }
        case '4': {
            _recursion = 4;
            break;
        }
        case '5': {
            _recursion = 5;
            break;
        }
        case '6': {
            _recursion = 6;
            break;
        }
        case '7': {
            _recursion = 7;
            break;
        }
        case '8': {
            _recursion = 8;
            break;
        }
        case '9': {
            _recursion = 9;
            break;
        }
        case '0': {
            _recursion = 10;
            break;
        }
        case ' ': {
            read();
            update = true;
            break;
        }
        case 0x0D: {
            _scene.next();
            update = true;
            break;
        }
        case 0x1B: {
            glutDestroyWindow(glutGetWindow());
            delete this;
            exit(0);
        }
        default: {
            return;
        }
    }
    render(update);
}

//------------------------------------------------------------------------------
// special
void Control::special(int key, int /*x*/, int /*y*/) {
    bool update = false;
    const double ANGLE_INCREMENT = 5.0;
    const double POSITION_INCREMENT = 0.05;
    switch (key) {
        case GLUT_KEY_F1: {
            _render = false;
            _wireframe = false;
            break;
        }
        case GLUT_KEY_F2: {
            _render = false;
            _wireframe = true;
            break;
        }
        case GLUT_KEY_F3: {
            _render = true;
            _reflection = false;
            _shadow = false;
            _refraction = false;
            break;
        }
        case GLUT_KEY_F4: {
            _render = true;
            _reflection = false;
            _shadow = true;
            _refraction = false;
            break;
        }
        case GLUT_KEY_F5: {
            _render = true;
            _reflection = false;
            _shadow = true;
            _refraction = true;
            break;
        }
        case GLUT_KEY_F6: {
            _render = true;
            _reflection = true;
            _shadow = false;
            _refraction = false;
            break;
        }
        case GLUT_KEY_F7: {
            _render = true;
            _reflection = true;
            _shadow = true;
            _refraction = false;
            break;
        }
        case GLUT_KEY_F8: {
            _render = true;
            _reflection = true;
            _shadow = true;
            _refraction = true;
            break;
        }
        case GLUT_KEY_F9: {
            _scene.write(_fout);
            return;
        }
        case GLUT_KEY_F10: {
            _position = true;
            return;
        }
        case GLUT_KEY_F11: {
            _position = false;
            return;
        }
        case GLUT_KEY_F12: {
            _scene.next();
            update = true;
            break;
        }
        case GLUT_KEY_END: {
            _scene.move(Vectors(), -POSITION_INCREMENT, Vectors());
            update = true;
            break;
        }
        case GLUT_KEY_HOME: {
            _scene.move(Vectors(), POSITION_INCREMENT, Vectors());
            update = true;
            break;
        }
        default: {
            if (_position) {
                switch (key) {
                    case GLUT_KEY_LEFT: {
                        _scene.move(Vectors(-ANGLE_INCREMENT, 0.0, 0.0), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_RIGHT: {
                        _scene.move(Vectors(ANGLE_INCREMENT, 0.0, 0.0), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_DOWN: {
                        _scene.move(Vectors(0.0, ANGLE_INCREMENT, 0.0), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_UP: {
                        _scene.move(Vectors(0.0, -ANGLE_INCREMENT, 0.0), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_PAGE_DOWN: {
                        _scene.move(Vectors(0.0, 0.0, -ANGLE_INCREMENT), 0.0, Vectors());
                        break;
                    }
                    case GLUT_KEY_PAGE_UP: {
                        _scene.move(Vectors(0.0, 0.0, ANGLE_INCREMENT), 0.0, Vectors());
                        break;
                    }
                }
            }
            else {
                switch (key) {
                    case GLUT_KEY_LEFT: {
                        _scene.move(Vectors(), 0.0, Vectors(-POSITION_INCREMENT, 0.0, 0.0));
                        break;
                    }
                    case GLUT_KEY_RIGHT: {
                        _scene.move(Vectors(), 0.0, Vectors(POSITION_INCREMENT, 0.0, 0.0));
                        break;
                    }
                    case GLUT_KEY_DOWN: {
                        _scene.move(Vectors(), 0.0, Vectors(0.0, -POSITION_INCREMENT, 0.0));
                        break;
                    }
                    case GLUT_KEY_UP: {
                        _scene.move(Vectors(), 0.0, Vectors(0.0, POSITION_INCREMENT, 0.0));
                        break;
                    }
                    case GLUT_KEY_PAGE_DOWN: {
                        _scene.move(Vectors(), 0.0, Vectors(0.0, 0.0, -POSITION_INCREMENT));
                        break;
                    }
                    case GLUT_KEY_PAGE_UP: {
                        _scene.move(Vectors(), 0.0, Vectors(0.0, 0.0, POSITION_INCREMENT));
                        break;
                    }
                }
            }
            update = true;
        }
    }
    render(update);
}

//------------------------------------------------------------------------------
// mouse
void Control::mouse(int button, int state, int x, int y) {
    _motionX = x;
    _motionY = y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _rotation = true;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        _rotation = false;
    }
}

//------------------------------------------------------------------------------
// motion
void Control::motion(int x, int y) {
    const double ANGLE_INCREMENT = 1.0;
    if (_rotation) {
        _scene.move(Vectors((x - _motionX) * ANGLE_INCREMENT, -(_motionY - y) * ANGLE_INCREMENT, 0.0),
            0.0, Vectors());
    }
    else {
        _scene.move(Vectors(0.0, 0.0, ((x - _motionX) + (_motionY - y)) * ANGLE_INCREMENT),
            0.0, Vectors());
    }
    _motionX = x;
    _motionY = y;
    render(true);
}

//------------------------------------------------------------------------------
// idle
void Control::idle() {
    if (!_render) {
        render(true);
    }
}

//------------------------------------------------------------------------------
