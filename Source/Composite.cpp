//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Composite.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#pragma hdrstop
#include "Composite.h"
#include "Group.h"
#include "Union.h"
#include "Difference.h"
#include "Intersection.h"
#include "Ray.h"
#include "Intersects.h"
#include "Shape.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static read composite
bool Composite::read(istream &in, string &token, Group &group) {
    if (Union::read(in, token, group)) {
        return true;
    }
    else if (Difference::read(in, token, group)) {
        return true;
    }
    else if (Intersection::read(in, token, group)) {
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// intersect with composite
void Composite::intersect(const Ray &ray, Intersects &intersects) const {
    Intersects intersectsA;
    Intersects intersectsB;
    for (vector<Shape *>::const_iterator shape = _group.composites().begin();
        shape != _group.composites().end(); ++shape) {
        if (shape == _group.composites().begin()) {
            (*shape)->intersect(ray, intersects);
        }
        else {
            intersectsA = intersects;
            intersectsB().clear();
            (*shape)->intersect(ray, intersectsB);
            intersects().clear();
            vector<Intersects::Intersect>::const_iterator intersectA = intersectsA().begin();
            vector<Intersects::Intersect>::const_iterator intersectB = intersectsB().begin();
            bool insideA = false;
            bool insideB = false;
            bool insideOld = false;
            for (int i = 0; i < (int)intersectsA().size() + (int)intersectsB().size(); ++i) {
                bool insideNew;
                if (intersectA != intersectsA().end() && intersectB != intersectsB().end()) {
                    if (*intersectA < *intersectB) {
                        insideA = !insideA;
                        insideNew = inside(insideA, insideB);
                        if (insideNew != insideOld) {
                            intersects().push_back(*intersectA);
                        }
                        intersectA++;
                    }
                    else {
                        insideB = !insideB;
                        insideNew = inside(insideA, insideB);
                        if (insideNew != insideOld) {
                            intersects().push_back(*intersectB);
                        }
                        intersectB++;
                    }
                }
                else if (intersectA != intersectsA().end()) {
                    insideA = !insideA;
                    insideNew = inside(insideA, insideB);
                    if (insideNew != insideOld) {
                        intersects().push_back(*intersectA);
                    }
                    intersectA++;
                }
                else {
                    insideB = !insideB;
                    insideNew = inside(insideA, insideB);
                    if (insideNew != insideOld) {
                        intersects().push_back(*intersectB);
                    }
                    intersectB++;
                }
                insideOld = insideNew;
            }
        }
    }
}

//------------------------------------------------------------------------------
