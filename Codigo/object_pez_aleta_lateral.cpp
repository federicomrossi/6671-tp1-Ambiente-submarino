/*  
 *  CLASS PEZ_ALETA_LATERAL
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

#include "object_pez_aleta_lateral.h"



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
PezAletaLateral::PezAletaLateral() { }


// Destructor
PezAletaLateral::~PezAletaLateral() { }


// Crea un objeto
void PezAletaLateral::create()
{
	// Creamos el eje coordenado
	// this->ejeCoordenado.create(3);

	// Creamos el cubo
	this->cube.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PezAletaLateral::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, 
	// 	projection_matrix);
	
	// Damos forma y la renderizamos
	this->cube.changeObjectColor(33, 59, 148);
	glm::mat4 m = glm::mat4(1.0f);
	m = glm::translate(model_matrix, glm::vec3(-0.5, 0.0, 0.0));
	m = glm::scale(m, glm::vec3(1.0, 0.01, 0.6));
	this->cube.render(m, view_matrix, projection_matrix);
}
