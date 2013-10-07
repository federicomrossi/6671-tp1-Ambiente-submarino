/*  
 *  CLASS CANGREJO_CUERPO
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

#include "object_cangrejo_cuerpo.h"



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
CangrejoCuerpo::CangrejoCuerpo() { }


// Destructor
CangrejoCuerpo::~CangrejoCuerpo() { }


// Crea un objeto
void CangrejoCuerpo::create()
{
	// Creamos la esfera
	this->spiralSphere.create(1.0, 32, 32);
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoCuerpo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Damos forma del cuerpo a la esfera y la renderizamos
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::scale(model_matrix, glm::vec3(1.0, 1.1, 0.5));
	mCuerpo = glm::rotate(mCuerpo, 15.0f, glm::vec3(0.0, 1.0, 0.0));
	this->spiralSphere.changeObjectColor(20, 143, 4);
	this->spiralSphere.render(mCuerpo, view_matrix, projection_matrix);
}
