//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Group.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Group_h
#define Group_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Transform.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // forward declarations

    class Light;
    class Shape;
    class Primitive;

    //------------------------------------------------------------------------------
    // class definition

    class Group : public Object {

    public:

        Group() {}
        ~Group() { erase(); }
        void clear() { erase(); }
        static bool read(istream &in, string &token, Group &group);
        virtual void update(Group &group, bool composite);
        virtual void transform(Transform &transform);
        virtual void preview() const;
        void push_back(Object *object) { _objects.push_back(object); }
        const vector<Object *> &objects() const { return _objects; }
        const vector<Shape *> &composites() const { return _composites; }
        vector<Shape *> &composites() { return _composites; }
        static vector<Light *> &lights() { return _lights; }
        static vector<Shape *> &shapes() { return _shapes; }
        static vector<Primitive *> &primitives() { return _primitives; }

    private:

        Group(const Group &group);
        Group &operator=(const Group &group);
        void erase();
        virtual void write(ostream &out) const { cout << "Group"; }

        vector<Object *> _objects;
        vector<Shape *> _composites;
        static vector<Light *> _lights;
        static vector<Shape *> _shapes;
        static vector<Primitive *> _primitives;

    };

} // ComputerGraphics

#endif // Group_h

//------------------------------------------------------------------------------
