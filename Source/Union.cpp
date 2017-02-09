//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Union.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Union.h"
#include "Group.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read union
bool Union::read(istream &in, string &token, Group &group) {
    if (token == "Union") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing composite opening brace");
        }
        Union *nestedUnion = new Union();
        group.push_back(nestedUnion);
        while (in >> token, token != CLOSING_BRACE) {
            if (Object::read(in, token, nestedUnion->_group)) {}
            else {
                throw string("Error : Invalid composite attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
