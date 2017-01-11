#include <iostream>
using namespace std;

#include "vgl.h"
#include "Loadshaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, numBuffer };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[numBuffers];

const GLuint NumVertices = 6;

