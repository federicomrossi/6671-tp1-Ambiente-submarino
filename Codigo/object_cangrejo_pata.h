/*  
 *  CLASS CANGREJOPATA
 */  


#ifndef OBJECT_CANGREJO_PATA_H
#define OBJECT_CANGREJO_PATA_H


#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <vector>
#include "object_dibujable.h"

#include "object_eje_coordenado.h"
#include "object_cangrejo_pata_muslo.h"
#include "object_cangrejo_pata_pierna.h"
#include "object_cangrejo_pata_pie.h"





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class CangrejoPata : public ObjectDibujable
{
private:

	// Objetos
	EjeCoordenado ejeCoordenado;		// Eje coordenado del objeto
	CangrejoPataMuslo muslo;			// Muslo de la pata
	CangrejoPataPierna pierna;			// Pierna de la pata
	CangrejoPataPie pie;				// Pie de la pata

	// Atributos de movimiento
	int direccion;						// Sentido de movimiento.

	float gradoRotacion;				// Grado de rotación de la pata
	float gradoMuslo;					// Posición del muslo
	float maxGradoMuslo;				// Maximo grado del muslo
	float minGradoMuslo;				// Mínimo grado del muslo
	float sentidoMuslo;					// Flag para cambio de movimiento

	float gradoPierna;					// Posición del pierna
	float maxGradoPierna;				// Maximo grado del pierna
	float minGradoPierna;				// Mínimo grado del pierna

	float gradoPie;						// Posición del pie
	float maxGradoPie;					// Maximo grado del pie
	float minGradoPie;					// Mínimo grado del pie

public:

	// Constructor
	CangrejoPata();

	// Destructor
	~CangrejoPata();

	// Crea un objeto
	virtual void create(int direccion);

	// Renderiza el objeto (lo dibuja).
	// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
	// debe renderizarce el objeto.
	virtual void render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
		glm::mat4 &projection_matrix);

	// Permite establecer un delay en el movimiento
	void setDelay(float delay);
};

#endif
