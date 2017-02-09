//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Intersection.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Intersection.h"
#include "Group.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read intersection
bool Intersection::read(istream &in, string &token, Group &group) {
    if (token == "Intersection") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing composite opening brace");
        }
        Intersection *nestedIntersection = new Intersection();
        group.push_back(nestedIntersection);
        while (in >> token, token != CLOSING_BRACE) {
            if (Object::read(in, token, nestedIntersection->_group)) {}
            else {
                throw string("Error : Invalid composite attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
