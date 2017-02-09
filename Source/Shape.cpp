//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Shape.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Shape.h"
#include "Group.h"
#include "Primitive.h"
#include "Composite.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static function to read shape
bool Shape::read(istream &in, string &token, Group &group) {
    if (Primitive::read(in, token, group)) {
        return true;
    }
    else if (Composite::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// update group with this shape
void Shape::update(Group &group, bool composite) {
    if (composite) {
        group.composites().push_back(this);
    }
    else {
        group.shapes().push_back(this);
    }
}

//------------------------------------------------------------------------------
