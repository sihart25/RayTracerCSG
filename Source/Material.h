//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Material.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Material_h
#define Material_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Colour.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Material {

    public:

        Material() : _ambient(0.0, 0.0, 0.0, 1.0), _diffuse(0.0, 0.0, 0.0, 1.0),
            _specular(0.0, 0.0, 0.0, 1.0), _shininess(50.0),
            _emission(0.0, 0.0, 0.0, 1.0), _reflection(0.0, 0.0, 0.0, 1.0),
            _refraction(0.0, 0.0, 0.0, 1.0) {}
        bool read(istream &in, string &token);
        void preview() const;
        const Colour &ambient() const {return _ambient;}
        const Colour &diffuse() const {return _diffuse;}
        const Colour &specular() const {return _specular;}
        double shininess() const {return _shininess;}
        const Colour &emission() const {return _emission;}
        const Colour &reflection() const {return _reflection;}
        const Colour &refraction() const {return _refraction;}

    private:

        Colour _ambient;
        Colour _diffuse;
        Colour _specular;
        double _shininess;
        Colour _emission;
        Colour _reflection;
        Colour _refraction;

    };

} // ComputerGraphics

#endif // Material_h

//------------------------------------------------------------------------------
