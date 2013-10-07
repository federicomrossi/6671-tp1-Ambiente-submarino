/*  
 *  CLASS PEZ_ALETA_LATERAL
 */  


#ifndef OBJECT_PEZ_ALETA_LATERAL_H
#define OBJECT_PEZ_ALETA_LATERAL_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_eje_coordenado.h"
#include "object_cube.h"



/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class PezAletaLateral : public ObjectDibujable
{
private:

	// Objetos
	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	Cube cube;		// Cubo
	
public:

	// Constructor
	PezAletaLateral();

	// Destructor
	~PezAletaLateral();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
