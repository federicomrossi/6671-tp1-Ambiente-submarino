/*  
 *  CLASS CANGREJO
 */  


#ifndef OBJECT_CANGREJO_H
#define OBJECT_CANGREJO_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_eje_coordenado.h"
#include "object_cangrejo_cuerpo.h"
#include "object_cangrejo_pata.h"
#include "object_cangrejo_ojo.h"
#include "object_cangrejo_pinza.h"





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Cangrejo : public ObjectDibujable
{
private:

	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	CangrejoCuerpo cangrejoCuerpo;
	CangrejoPata cangrejoPataDer01;
	CangrejoPata cangrejoPataDer02;
	CangrejoPata cangrejoPataDer03;
	CangrejoPata cangrejoPataIzq01;
	CangrejoPata cangrejoPataIzq02;
	CangrejoPata cangrejoPataIzq03;
	CangrejoOjo cangrejoOjo;
	CangrejoPinza cangrejoPinza;

	// Movimiento
	float cuerpoPosZ;					// Posición del cuerpo en eje Z
	float parametro;
	int sentidoParametro;

public:

	// Constructor
	Cangrejo();

	// Destructor
	~Cangrejo();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
