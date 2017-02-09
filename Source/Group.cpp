//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Group.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#pragma hdrstop
#include "Group.h"
#include "Light.h"
#include "Shape.h"
#include "Primitive.h"
#include "Object.h"
#include "Reader.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
vector<Light *> Group::_lights;
vector<Shape *> Group::_shapes;
vector<Primitive *> Group::_primitives;

//------------------------------------------------------------------------------
// erase group
void Group::erase() {
    for (vector<Object *>::iterator object = _objects.begin(); object != _objects.end(); ++object) {
        delete *object;
    }
    _objects.clear();
    _composites.clear();
    _lights.clear();
    _shapes.clear();
    _primitives.clear();
}

//------------------------------------------------------------------------------
// static read group
bool Group::read(istream &in, string &token, Group &group) {
    if (token == "Group") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing group opening brace");
        }
        Group *nestedGroup = new Group();
        group.push_back(nestedGroup);
        while (in >> token, token != CLOSING_BRACE) {
            if (Object::read(in, token, *nestedGroup)) {}
            else {
                throw string("Error : Invalid group attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// update group
void Group::update(Group &group, bool composite) {
    for (vector<Object *>::const_iterator object = _objects.begin(); object != _objects.end();
        ++object) {
        (*object)->update(group, composite);
    }
}

//------------------------------------------------------------------------------
// transform group
void Group::transform(Transform &transform) {
    Transform nestedTransform(transform);
    for (vector<Object *>::const_iterator object = _objects.begin(); object != _objects.end();
        ++object) {
        (*object)->transform(nestedTransform);
    }
}

//------------------------------------------------------------------------------
// preview group
void Group::preview() const {
    for (vector<Object *>::const_iterator object = _objects.begin(); object != _objects.end();
        ++object) {
        (*object)->preview();
    }
}

//------------------------------------------------------------------------------
