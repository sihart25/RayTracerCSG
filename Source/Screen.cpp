//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Screen.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#pragma hdrstop
#include "Screen.h"
#include "Camera.h"
#include "Colour.h"
#include "Reader.h"
#include "Writer.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// erase screen
void Screen::erase() {
    delete[] _screen;
    _screen = 0;
    _cameras.clear();
    for (vector<Camera *>::iterator camera = _cameras.begin(); camera != _cameras.end(); ++camera) {
        delete *camera;
    }
    _cameras.clear();
}

//------------------------------------------------------------------------------
// clear screen
void Screen::clear() {
    erase();
    _width = WIDTH;
    _height = HEIGHT;
    _background = Colour(0.0, 0.0, 0.0, 1.0);
    _screen = new Colour[(long)_height * (long)_width];
}

//------------------------------------------------------------------------------
// read screen
bool Screen::read(istream &in, string &token) {
    if (token == "Screen") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing screen opening brace");
        }
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (token == "Width") {
                in >> _width;
            }
            else if (token == "Height") {
                in >> _height;
            }
            else if (token == "Background") {
                in >> _background;
            }
            else if (Camera::read(in, token, _cameras)) {}
            else {
                throw string("Error : Invalid screen attribute = " + token);
            }
        }
        resize(_width, _height);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// write screen
void Screen::write(const string &filename) {
    Writer::write(filename, width(), height());
}

//------------------------------------------------------------------------------
// resize screen
void Screen::resize(int width, int height) {
    _width = width;
    _height = height;
    delete[] _screen;
    _screen = new Colour[(long)_height * (long)_width];
}

//------------------------------------------------------------------------------
