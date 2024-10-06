#include "Square.h"

// Definice vertexů pro čtverec
static float squareVertices[] = {
    // Positions         
    -0.5f,  0.5f, 0.0f,  
     0.5f,  0.5f, 0.0f,  
     0.5f, -0.5f, 0.0f,  
     0.5f, -0.5f, 0.0f,  
    -0.5f, -0.5f, 0.0f,  
    -0.5f,  0.5f, 0.0f   
};

Square::Square() 
    : Model(squareVertices, sizeof(squareVertices)) 
{
    // Případné další inicializace specifické pro čtverec
}