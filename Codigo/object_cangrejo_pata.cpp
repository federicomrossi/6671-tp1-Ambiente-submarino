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
	// Creamos el eje coordenado
	this->ejeCoordenado.create(1);

	// Creamos la esfera
	this->spiralSphere.create(0.5, 32, 32);	
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPata::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, projection_matrix);

	glm::mat4 m = glm::mat4(1.0f);
	this->spiralSphere.changeObjectColor(126, 241, 95);

	// Damos forma al objeto y la renderizamos
	glm::mat4 mMuslo = glm::mat4(1.0f);
	m = glm::translate(model_matrix, glm::vec3(0.0, -0.35, 0.0));
	mMuslo = glm::scale(m, glm::vec3(0.4, 0.7, 0.4));
	this->spiralSphere.render(mMuslo, view_matrix, projection_matrix);

	// Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, -0.25, 0.0));
	m = glm::rotate(m, 45.0f, glm::vec3(1.0, 0.0, 0.0));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	glm::mat4 mEntrepierna = glm::mat4(1.0f);
	mEntrepierna = glm::translate(m, glm::vec3(0.0, -0.425, 0.0));
	mEntrepierna = glm::scale(mEntrepierna, glm::vec3(0.3, 0.85, 0.3));
	this->spiralSphere.render(mEntrepierna, view_matrix, projection_matrix);

	// Reposicionamos
	m = glm::translate(m, glm::vec3(0.0, -0.75, 0.0));
	m = glm::rotate(m, 60.0f, glm::vec3(1.0, 0.0, 0.0));

	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(m, view_matrix, projection_matrix);

	glm::mat4 mPie = glm::mat4(1.0f);
	mPie = glm::translate(m, glm::vec3(0.0, -0.25, 0.0));
	mPie = glm::scale(mPie, glm::vec3(0.2, 0.5, 0.2));
	this->spiralSphere.render(mPie, view_matrix, projection_matrix);
}
