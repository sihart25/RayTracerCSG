//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Reader.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#pragma hdrstop
#include "Reader.h"
#include "Group.h"
#include "Screen.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read
void Reader::read(const string &filename, Group &group, Screen &screen) {
    try {
        ifstream in(filename.c_str());
        if (!in.good()) {
            throw string("Error : Invalid file name = " + filename);
        }
        string token;
        screen.clear();
        while (in >> token, comment(in, token)) {}
        if (!screen.read(in, token)) {
            throw string("Error : Invalid file attribute = " + token);
        }
        group.clear();
        while (in >> token, comment(in, token)) {}
        if (!Group::read(in, token, group)) {
            throw string("Error : Invalid file attribute = " + token);
        }
    }
    catch (string s) {
        cout << s << endl;
    }
    catch (...) {
        cout << "Error : Unknown exception caught in reader" << endl;
    }
}

//------------------------------------------------------------------------------
// read comment
bool Reader::comment(istream &in, string &token) {
    if (token == OPENING_COMMENT) {
        while (in >> token, token != CLOSING_COMMENT) {
        }
        return true;
    }
    else if (token == LINE_COMMENT) {
        getline(in, token);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
