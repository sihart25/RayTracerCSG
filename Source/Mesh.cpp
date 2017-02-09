//------------------------------------------------------------------------------
//
// Module 08932 : Object-Oriented Software Engineering
// Module 08933 : Graphics Algorithms and Techniques
// Ray Tracer Assessment
// Mesh.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <vector>
#include <gl/glut.h>
#pragma hdrstop
#include "Mesh.h"
#include "Group.h"
#include "Reader.h"
#include "Vectors.h"
#include "Triangle.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// erase mesh
void Mesh::erase() {
    for (vector<Vectors *>::iterator vertex = _vertex.begin(); vertex != _vertex.end(); ++vertex) {
        delete *vertex;
    }
    _vertex.clear();
    for (vector<Vectors *>::iterator normal = _normal.begin(); normal != _normal.end(); ++normal) {
        delete *normal;
    }
    _normal.clear();
    for (vector<Face *>::iterator face = _face.begin(); face != _face.end(); ++face) {
        delete *face;
    }
    _face.clear();
}

//------------------------------------------------------------------------------
// read mesh with static fuunction
bool Mesh::read(istream &in, string &token, Group &group) {
    if (token == "Mesh") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing mesh opening brace");
        }
        Mesh *mesh = new Mesh();
        group.push_back(mesh);
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (mesh->_material.read(in, token)) {}
            else if (token == "Centre") {
                mesh->_centre.readPosition(in);
            }
            else if (mesh->readVertex(in, token)) {}
            else if (mesh->readFace(in, token)) {}
            else if (token == "Smooth") {
                in >> boolalpha >> mesh->_smooth >> noboolalpha;
            }
            else {
                throw string("Error : Invalid mesh attribute = " + token);
            }
        }
        mesh->triangle(group);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read mesh vertices
bool Mesh::readVertex(istream &in, string &token) {
    if (token == "Vertex") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing mesh vertex opening brace");
        }
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (token == "Vertex") {
                Vectors *vertex = new Vectors();
                _vertex.push_back(vertex);
                vertex->readPosition(in);
            }
            else {
                throw string("Error : Invalid mesh vertex attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// read mesh faces
bool Mesh::readFace(istream &in, string &token) {
    if (token == "Face") {
        if (in >> token, token != OPENING_BRACE) {
            throw string("Error : Missing mesh face opening brace");
        }
        while (in >> token, token != CLOSING_BRACE) {
            if (Reader::comment(in, token)) {}
            else if (token == "Face") {
                Face *face = new Face();
                _face.push_back(face);
                in >> *face;
            }
            else {
                throw string("Error : Invalid mesh face attribute = " + token);
            }
        }
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
// mesh normals
void Mesh::triangle(Group &group) {
    vector<Face *>::const_iterator face;
    // face normals
    for (face = _face.begin(); face != _face.end(); ++face) {
        (*face)->normal((*_vertex[(*face)->b()] - *_vertex[(*face)->a()]).
            cross(*_vertex[(*face)->c()] - *_vertex[(*face)->a()]));
    }
    // vertex normals
    for (vector<Vectors *>::const_iterator vertex = _vertex.begin(); vertex != _vertex.end(); ++vertex) {
        Vectors *normal = new Vectors(0.0, 0.0, 0.0, 0.0);
        _normal.push_back(normal);
        int faces = 0;
        for (face = _face.begin(); face != _face.end(); ++face) {
            if ((*vertex == _vertex[(*face)->a()]) || (*vertex == _vertex[(*face)->b()]) ||
                (*vertex == _vertex[(*face)->c()])) {
                *normal += (*face)->normal();
                ++faces;
            }
        }
        *normal /= faces ? (double)faces : 1.0;
    }
    // mesh triangles
    for (face = _face.begin(); face != _face.end(); ++face) {
        Triangle *triangle = new Triangle(_transform, _material, _centre,
            *(_vertex[(*face)->a()]), *(_vertex[(*face)->b()]), *(_vertex[(*face)->c()]), _smooth,
            *(_normal[(*face)->a()]), *(_normal[(*face)->b()]), *(_normal[(*face)->c()]));
        group.push_back(triangle);
    }
}

//------------------------------------------------------------------------------
