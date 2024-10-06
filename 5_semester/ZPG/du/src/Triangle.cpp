#include "Triangle.h"

// Definice vertexů pro trojúhelník
static float triangleVertices[] = {
    // Positions         
     0.0f,  0.5f, 0.0f,  
    -0.5f, -0.5f, 0.0f,  
     0.5f, -0.5f, 0.0f   
};

Triangle::Triangle() 
    : Model(triangleVertices, sizeof(triangleVertices)) 
{
    // Případné další inicializace specifické pro trojúhelník
}