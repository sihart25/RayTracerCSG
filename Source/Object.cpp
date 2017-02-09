//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Object.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Object.h"
#include "Group.h"
#include "Transformation.h"
#include "Light.h"
#include "Shape.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read object
bool Object::read(istream &in, string &token, Group &group) {
    if (Reader::comment(in, token)) {
        return true;
    }
    else if (Group::read(in, token, group)) {
        return true;
    }
    else if (Transformation::read(in, token, group)) {
        return true;
    }
    else if (Light::read(in, token, group)) {
        return true;
    }
    else if (Shape::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
