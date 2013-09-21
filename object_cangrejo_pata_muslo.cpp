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

#include "object_cangrejo_pata_muslo.h"



// Constantes
namespace {
	// const int MAX_CONEXIONES = 10;
}





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
CangrejoPataMuslo::CangrejoPataMuslo()
{
	this->muslo_index_buffer = NULL;
	this->muslo_vertex_buffer = NULL;
	this->muslo_normal_buffer = NULL;
}


// Destructor
CangrejoPataMuslo::~CangrejoPataMuslo() { }


// Crea un objeto
void CangrejoPataMuslo::create() { }


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPataMuslo::render(glm::mat4 model_matrix, GLuint &programHandle)
{
	// Renderizamos esfera que representa la muñeca
	glm::mat4 mMuslo = glm::mat4 ( 1.0f );
	mMuslo = glm::scale(m, glm::vec3(0.3f, 0.3f, 0.3));
	
	this->spiralSphere.render(mMuslo, this->programHandle, this->view_matrix);
}
