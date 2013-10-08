/*  
 *  CLASS CANGREJO_OJO
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

#include "object_cangrejo_ojo.h"



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
CangrejoOjo::CangrejoOjo() { }


// Destructor
CangrejoOjo::~CangrejoOjo() { }


// Crea un objeto
void CangrejoOjo::create()
{
	// Creamos el eje coordenado
	this->ejeCoordenado.create(2);

	// Creamos el cubo
	this->cube.create();

	// Creamos la esfera
	this->spiralSphere.create(1.0, 32, 32);
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoOjo::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, projection_matrix);

	glm::mat4 m = glm::mat4(1.0f);

	// Damos forma al sosten del ojo
	glm::mat4 mSosten = glm::mat4(1.0f);
	m = glm::rotate(model_matrix, 25.0f,glm::vec3(0.0, 1.0, 0.0));
	m = glm::translate(m, glm::vec3(0.0, 0.0, 0.25));
	mSosten = glm::scale(m, glm::vec3(0.1, 0.1, 0.5));
	this->cube.changeObjectColor(157, 243, 232);
	this->cube.render(mSosten, view_matrix, projection_matrix);

	// Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, 0.0, 0.25));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	// Damos forma de Ojo a la esfera y la renderizamos
	glm::mat4 mOjo = glm::mat4(1.0f);
	mOjo = glm::scale(m, glm::vec3(0.20, 0.20, 0.20));
	this->spiralSphere.changeObjectColor(157, 243, 232);
	this->spiralSphere.render(mOjo, view_matrix, projection_matrix);
}
