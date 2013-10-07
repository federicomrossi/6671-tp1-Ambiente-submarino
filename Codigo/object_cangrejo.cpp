/*  
 *  CLASS CANGREJO
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

#include "object_cangrejo.h"



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
Cangrejo::Cangrejo() { }


// Destructor
Cangrejo::~Cangrejo() { }


// Crea un objeto
void Cangrejo::create()
{
	// Creamos el eje coordenado
	this->ejeCoordenado.create(3);

	// Creamos el cuerpo
	this->cangrejoCuerpo.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void Cangrejo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	this->ejeCoordenado.render(model_matrix, view_matrix, projection_matrix);

	// Dibujamos el cuerpo
	glm::mat4 mCuerpo = glm::mat4(1.0f);
	mCuerpo = glm::translate(model_matrix, glm::vec3(0.0, -2.0, 1.0));
	this->cangrejoCuerpo.render(mCuerpo, view_matrix, projection_matrix);
}
