//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Primitive.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Primitive_h
#define Primitive_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Shape.h"
#include "Transform.h"
#include "Material.h"
#include "Vectors.h"
#include "Group.h"
#include "Intersects.h"
#include "Ray.h"
#include "Colour.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Primitive : public Shape {

    public:

        Primitive() : _centre(0.0, 0.0, 0.0, 1.0) {}
        Primitive(const Transform &transform, const Material &material, const Vectors &centre) :
            _transform(transform), _material(material), _centre(centre) {}
        virtual ~Primitive() {}
        static bool read(istream &in, string &token, Group &group);
        virtual void update(Group &group, bool composite) {
            Shape::update(group, composite);
            group.primitives().push_back(this);
        }
        virtual void transform(Transform &transform) {}
        virtual void preview() const {}
        virtual void intersect(const Ray &ray, Intersects &intersects) const {}
        bool reflect(const Vectors &intersect, const Ray &ray, Ray &reflect, Colour &colour) const;
        bool refract(const Vectors &intersect, const Ray &ray, Ray &refract, Colour &colour) const;
        Colour light(const Vectors &intersect, const Group &group, const Colour &reflect,
            const Colour &refract, bool shadows) const;

    protected:

        virtual Vectors normal(const Vectors &intersect) const { return Vectors(0.0, 0.0, 1.0, 0.0); }
        virtual void write(ostream &out) const { cout << "Primitive" << endl << _transform << endl; }

        Transform _transform;
        Material _material;
        Vectors _centre;

    private:

        bool shadow(const Ray &ray, const Group &group, double distance) const;

    };

} // ComputerGraphics

#endif // Primitive_h

//------------------------------------------------------------------------------
