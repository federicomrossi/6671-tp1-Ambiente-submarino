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
	this->hojaTipo01.create();
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
	glm::mat4 mHojaT1 = glm::mat4(1.0f);
	// mHojaT1 = glm::scale(model_matrix, glm::vec3(1.0, 1.0, 1.0));
	// // mHojaT1 = glm::rotate(mHojaT1, -140.0f, glm::vec3(0.0, 0.0, 1.0));
	// // mHojaT1 = glm::rotate(mHojaT1, -10.0f, glm::vec3(1.0, 0.0, 0.0));
	this->hojaTipo01.changeObjectColor(0, 255, 0);
	this->hojaTipo01.render(model_matrix, view_matrix, projection_matrix);

	// mHojaT1 = glm::scale(model_matrix, glm::vec3(1.0, 1.0, 0.7));
	// mHojaT1 = glm::rotate(mHojaT1, 130.0f, glm::vec3(0.0, 0.0, 1.0));
	// // mHojaT1 = glm::rotate(mHojaT1, -20.0f, glm::vec3(1.0, 0.0, 0.0));
	// this->hojaTipo01.render(mHojaT1, view_matrix, projection_matrix);

	// mHojaT1 = glm::scale(model_matrix, glm::vec3(1.2, 1.0, 1.4));
	// mHojaT1 = glm::rotate(mHojaT1, -30.0f, glm::vec3(1.0, 0.0, 0.0));
	// mHojaT1 = glm::rotate(mHojaT1, 90.0f, glm::vec3(0.0, 0.0, 1.0));
	// this->hojaTipo01.render(mHojaT1, view_matrix, projection_matrix);
}
