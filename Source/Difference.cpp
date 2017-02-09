//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Difference.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#pragma hdrstop
#include "Difference.h"
#include "Group.h"
#include "Reader.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read difference
bool Difference::read(istream &in, string &token, Group &group) {
    if (token == "Difference") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing composite opening brace");
        }
        Difference *nestedDifference = new Difference();
        group.push_back(nestedDifference);
        while (in >> token, token != CLOSING_BRACE) {
            if (Object::read(in, token, nestedDifference->_group)) {}
            else {
                throw string("Error : Invalid composite attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
