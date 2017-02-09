//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Mesh.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Mesh_h
#define Mesh_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Primitive.h"
#include "Group.h"
#include "Transform.h"
#include "Ray.h"
#include "Intersects.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Mesh : public Primitive {

    public:

        Mesh() : _smooth(false) {}
        ~Mesh() { erase(); }
        static bool read(istream &in, string &token, Group &group);
        virtual void update(Group &group, bool composite) {}
        virtual void transform(Transform &transform) {}
        virtual void preview() const {}
        virtual void intersect(const Ray &ray, Intersects &intersects) const {}

    private:

        Mesh(const Mesh &mesh);
        Mesh &operator=(const Mesh &mesh);
        void erase();
        bool readVertex(istream &in, string &token);
        bool readNormal(istream &in, string &token);
        bool readFace(istream &in, string &token);
        void triangle(Group &group);
        virtual void write(ostream &out) const { cout << "Mesh" << endl; Primitive::write(out); }

        //------------------------------------------------------------------------------
        // nested class definition

        class Face {

        public:

            Face() : _a(0), _b(0), _c(0) {}
            int a() const { return _a; }
            int b() const { return _b; }
            int c() const { return _c; }
            void normal(const Vectors &n) { _normal = n; }
            const Vectors &normal() const { return _normal; }
            friend istream &operator>>(istream &in, Face &f) {
                f.read(in);
                return in;
            }

        private:

            void read(istream &in) {
                in >> _a >> _b >> _c;
            }
            int _a;
            int _b;
            int _c;
            Vectors _normal;

        };

        vector<Vectors *> _vertex;
        vector<Vectors *> _normal;
        vector<Face *> _face;
        bool _smooth;

    };

} // ComputerGraphics

#endif // Mesh_h

//------------------------------------------------------------------------------
