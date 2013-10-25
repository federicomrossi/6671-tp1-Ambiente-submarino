/*  
 *  CLASS PLANTA_ACUATICA
 */  


#ifndef OBJECT_PLANTA_ACUATICA_H
#define OBJECT_PLANTA_ACUATICA_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_eje_coordenado.h"
#include "object_planta_hoja_tipo01.h"
#include "object_planta_hoja_tipo02.h"
#include "object_planta_hoja_tipo03.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PlantaAcuatica : public ObjectDibujable
{
private:

	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	PlantaHojaTipo01 hojaTipo01;		// Hoja de tipo 01
	PlantaHojaTipo02 hojaTipo02;		// Hoja de tipo 02
	PlantaHojaTipo03 hojaTipo03;		// Hoja de tipo 03

public:

	// Constructor
	PlantaAcuatica();

	// Destructor
	~PlantaAcuatica();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
