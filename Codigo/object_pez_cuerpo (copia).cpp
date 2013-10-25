/*  
 *  CLASS PEZ
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

#include "object_pez_cuerpo.h"



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
PezCuerpo::PezCuerpo() { }


// Destructor
PezCuerpo::~PezCuerpo() { }


// Crea un objeto
void PezCuerpo::create()
{
	// Creamos la esfera
	this->spiralSphere.create(1.0, 32, 32);
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PezCuerpo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Damos forma del cuerpo a la esfera y la renderizamos
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::scale(model_matrix, glm::vec3(1.0, 0.1, 0.4));
	this->spiralSphere.changeObjectColor(166, 214, 38);
	this->spiralSphere.render(mCuerpo, view_matrix, projection_matrix);
}
