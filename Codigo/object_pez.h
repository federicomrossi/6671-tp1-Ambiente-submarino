/*  
 *  CLASS PEZ
 */  


#ifndef OBJECT_PEZ_H
#define OBJECT_PEZ_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

// Objetos
#include "object_eje_coordenado.h"
#include "object_pez_cuerpo.h"
#include "object_pez_ojo_izq.h"
#include "object_pez_ojo_der.h"
#include "object_pez_aleta_trasera.h"
#include "object_pez_aleta_dorsal.h"
#include "object_pez_aleta_lateral.h"




/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class Pez : public ObjectDibujable
{
private:

	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	PezCuerpo pezCuerpo;				// Cuerpo del pez
	PezOjoIzq pezOjoIzq;				// Ojo izquierdo
	PezOjoDer pezOjoDer;				// Ojo derecho
	PezAletaTrasera pezAletaTrasera;	// Aleta trasera
	PezAletaDorsal pezAletaDorsal;		// Aleta dorsal
	PezAletaLateral pezAletaLateralDer;	// Aleta lateral derecha
	PezAletaLateral pezAletaLateralIzq;	// Aleta lateral izquierda

public:

	// Constructor
	Pez();

	// Destructor
	~Pez();

	// Crea un objeto
	virtual void create();

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);
};

#endif
