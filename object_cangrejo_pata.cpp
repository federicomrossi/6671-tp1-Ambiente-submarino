/*  
 *  CLASS CANGREJOPATA
 */


#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>

#include "object_cangrejo_pata.h"





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
CangrejoPata::CangrejoPata()
{
	this->pata_index_buffer = NULL;
	this->pata_vertex_buffer = NULL;
	this->pata_normal_buffer = NULL;
}


// Destructor
CangrejoPata::~CangrejoPata() { }


// Crea un objeto
void CangrejoPata::create()
{
	
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPata::render(glm::mat4 model_matrix, GLuint &programHandle)
{

}
