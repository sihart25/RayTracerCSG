//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Triangle.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Triangle_h
#define Triangle_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Primitive.h"
#include "Transform.h"
#include "Material.h"
#include "Vectors.h"
#include "Group.h"
#include "Ray.h"
#include "Intersects.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Triangle : public Primitive {

    public:

        Triangle() : _vertexA(-1.0, -1.0, 0.0, 1.0), _vertexB(1.0, -1.0, 0.0, 1.0),
            _vertexC(0.0, 1.0, 0.0, 1.0), _smooth(false) {}
        Triangle(const Transform &transform, const Material &material, const Vectors &centre,
            const Vectors &vA, const Vectors &vB, const Vectors &vC, bool smooth,
            const Vectors &nA, const Vectors &nB, const Vectors &nC) :
            Primitive(transform, material, centre), _vertexA(vA), _vertexB(vB), _vertexC(vC),
            _smooth(smooth), _normalA(nA), _normalB(nB), _normalC(nC) {}
        static bool read(istream &in, string &token, Group &group);
        virtual void transform(Transform &transform);
        virtual void preview() const;
        virtual void intersect(const Ray &ray, Intersects &intersects) const;

    private:

        virtual Vectors normal(const Vectors &intersect) const;
        virtual void write(ostream &out) const { cout << "Triangle" << endl; Primitive::write(out); }

        Vectors _vertexA;
        Vectors _vertexB;
        Vectors _vertexC;
        bool _smooth;
        Vectors _normalA;
        Vectors _normalB;
        Vectors _normalC;

    };

} // ComputerGraphics

#endif // Triangle_h

//------------------------------------------------------------------------------
