/*  
 *  CLASS PLANTA_ACUATICA
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

#include "object_planta_acuatica.h"



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
PlantaAcuatica::PlantaAcuatica() { }


// Destructor
PlantaAcuatica::~PlantaAcuatica() { }


// Crea un objeto
void PlantaAcuatica::create()
{
	// Creamos el eje coordenado
	// this->ejeCoordenado.create(3);

	// Creamos una hoja de tipo 01
	this->hojaTipo01.setAmplitud(7.0);
	this->hojaTipo01.setVelocidad(0.1);
	this->hojaTipo01.create();

	// Creamos una hoja de tipo 02
	this->hojaTipo02.create();

	// Creamos una hoja de tipo 03
	this->hojaTipo03.create();
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PlantaAcuatica::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Dibujamos el eje coordenado
	// this->ejeCoordenado.render(model_matrix, view_matrix, 
	// 	projection_matrix);

	// Dibujamos la hoja de tipo 01
	glm::mat4 mHojaT1_01 = glm::mat4(1.0f);
	// mHojaT1_01 = glm::scale(model_matrix, glm::vec3(1.0, 1.0, 1.0));
	mHojaT1_01 = glm::rotate(model_matrix, -21.0f, glm::vec3(0.0, 1.0, 0.0));
	// mHojaT1_01 = glm::rotate(mHojaT1_01, -10.0f, glm::vec3(1.0, 0.0, 0.0));
	// this->hojaTipo01.changeObjectColor(0, 255, 0);
	this->hojaTipo01.render(mHojaT1_01, view_matrix, projection_matrix);

	glm::mat4 mHojaT1_02 = glm::mat4(1.0f);
	mHojaT1_02 = glm::scale(model_matrix, glm::vec3(0.7, 0.7, 0.7));
	mHojaT1_02 = glm::rotate(mHojaT1_02, -10.0f, glm::vec3(0.0, 1.0, 0.0));
	mHojaT1_02 = glm::rotate(mHojaT1_02, -10.0f, glm::vec3(0.0, 0.0, 1.0));
	this->hojaTipo01.render(mHojaT1_02, view_matrix, projection_matrix);

	// Dibujamos la hoja de tipo 02
	glm::mat4 mHojaT2_01 = glm::mat4(1.0f);
	// this->hojaTipo02.changeObjectColor(0, 255, 0);
	mHojaT2_01 = glm::rotate(model_matrix, 20.0f, glm::vec3(0.0, 1.0, 0.0));
	mHojaT2_01 = glm::rotate(mHojaT2_01, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	this->hojaTipo02.render(mHojaT2_01, view_matrix, projection_matrix);

	// Dibujamos la hoja de tipo 02
	glm::mat4 mHojaT2_02 = glm::mat4(1.0f);
	mHojaT2_02 = glm::translate(model_matrix, glm::vec3(-0.1, 0.0, 0.0));
	mHojaT2_02 = glm::scale(mHojaT2_02, glm::vec3(1.0, 1.0, 0.8));
	// mHojaT2_02 = glm::rotate(mHojaT2_02, 20.0f, glm::vec3(0.0, 1.0, 0.0));
	this->hojaTipo02.render(mHojaT2_02, view_matrix, projection_matrix);

	// Dibujamos la hoja de tipo 03
	glm::mat4 mHojaT3 = glm::mat4(1.0f);
	mHojaT3 = glm::translate(model_matrix, glm::vec3(0.04, 0.0, 0.0));
	mHojaT3 = glm::rotate(mHojaT3, 35.0f, glm::vec3(0.0, 1.0, 0.0));
	mHojaT3 = glm::rotate(mHojaT3, 180.0f, glm::vec3(0.0, 0.0, 1.0));
	// this->hojaTipo03.changeObjectColor(0, 255, 0);
	this->hojaTipo03.render(mHojaT3, view_matrix, projection_matrix);
}
