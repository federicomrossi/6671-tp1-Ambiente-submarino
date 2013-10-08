/*  
 *  CLASS PEZ_ALETA_TRASERA
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

#include "object_pez_aleta_trasera.h"



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
PezAletaTrasera::PezAletaTrasera() { }


// Destructor
PezAletaTrasera::~PezAletaTrasera() { }


// Crea un objeto
void PezAletaTrasera::create()
{
	// Creamos el cubo
	this->cube.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PezAletaTrasera::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Damos forma y la renderizamos
	this->cube.changeObjectColor(33, 59, 148);
	glm::mat4 m = glm::mat4(1.0f);
	m = glm::scale(model_matrix, glm::vec3(1.0, 0.01, 0.8));
	this->cube.render(m, view_matrix, projection_matrix);
}