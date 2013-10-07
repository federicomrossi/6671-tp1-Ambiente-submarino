/*  
 *  CLASS PEZ_ALETA_DORSAL
 */  


#ifndef OBJECT_PLANTA_HOJA_TIPO_O1_H
#define OBJECT_PEZ_ALETA_DORSAL_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_cube.h"



/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PlantaHojaTipo01 : public ObjectDibujable
{
private:

	// Objetos
	Cube cube;		// Cubo
	
public:

	// Constructor
	PlantaHojaTipo01();

	// Destructor
	~PlantaHojaTipo01();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
