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



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/VERT_SHADER_FILENAME.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/FRAG_SHADER_FILENAME.frag";
	
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
void CangrejoPataMuslo::create() 
{
	// this->spiralSphere.create(1.0, 32, 32);			// Esfera
	this->cube.create();
}


// Renderiza el cubo (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPataMuslo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Renderizamos esfera que representa la muñeca
	glm::mat4 mMuslo = glm::mat4 ( 1.0f );
	mMuslo = glm::scale(mMuslo, glm::vec3(3.0f, 3.0f, 3.0f));
	mMuslo = glm::rotate (mMuslo, -30.0f, glm::vec3(0.0, 0.0, 1.0));
	mMuslo = glm::rotate (mMuslo, 10.0f, glm::vec3(0.0, 1.0, 0.0));

	// this->spiralSphere.render(model_, view_matrix, projection_matrix);
	this->cube.changeObjectColor(0.9, 0.9, 0.9);
	this->cube.render(mMuslo, view_matrix, projection_matrix);
}	
