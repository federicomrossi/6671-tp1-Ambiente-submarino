/*  
 *  CLASS CANGREJO_PATA_PIE
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
 #include "lib_matematica.h"

#include "object_cangrejo_pata_pie.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/DiffuseShadingVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/DiffuseShadingFShader.frag";
}





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
CangrejoPataPie::CangrejoPataPie()
{
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_vertex_buffer = NULL;
}


// Destructor
CangrejoPataPie::~CangrejoPataPie() { }


// Crea un objeto
void CangrejoPataPie::create()
{
	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// Puntos de control de la CURVA DE LA FORMA DEL ESQUELETO

	float forma_pc0x = 0.0;
	float forma_pc0y = 0.0;

	float forma_pc1x = 1.0;
	float forma_pc1y = 0.4;

	float forma_pc2x = 9.0;
	float forma_pc2y = 0.4;

	float forma_pc3x = 10.0;
	float forma_pc3y = 0.15;

	float forma_pcx[] = {forma_pc0x, forma_pc1x, forma_pc2x, forma_pc3x};
	float forma_pcy[] = {forma_pc0y, forma_pc1y, forma_pc2y, forma_pc3y};


	


	// Puntos de control de la CURVA DE ANCHO DEL ESQUELETO

	float curvatura_pc0x = 0.0;
	float curvatura_pc0y = 0.0;

	float curvatura_pc1x = 2.0;
	float curvatura_pc1y = -0.5;

	float curvatura_pc2x = 8.0;
	float curvatura_pc2y = -0.2;

	float curvatura_pc3x = 10.0;
	float curvatura_pc3y = 0.0;

	float curvatura_pcx[] = {curvatura_pc0x, curvatura_pc1x, curvatura_pc2x, curvatura_pc3x};
	float curvatura_pcy[] = {curvatura_pc0y, curvatura_pc1y, curvatura_pc2y, curvatura_pc3y};




	// Configuración del paso entre un punto y otro.
	float PASO = 0.1;
	// Cantidad de curvas que compondran la curva general
	int CANT_CURVAS = 4;

	// Valores para cálculos (no modificar)
	this->CANT_PUNTOS = CANT_CURVAS * (int(ceil(1.0 / PASO)) + 1);
	int DIMENSIONES = 3;
	this->ESTIRAMIENTO = 40;




	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS * this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2* this->CANT_PUNTOS * (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* (this->ESTIRAMIENTO-1);
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	// Unimos los puntos

	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;



	int i = 0;

	// Iteramos sobre cada nivel del objeto
	for(int q = 0; q < this->ESTIRAMIENTO; q++)
	{
		// Calculamos la curva de bezier que da forma al esqueleto superior
		float forma = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1),	forma_pcy);

		// Calculamos la curva de bezier que da la curvatura del pie
		float curvatura = Matematica::curvaBezier((q * 1.0) / 
			(this->ESTIRAMIENTO-1), curvatura_pcy);


		// Puntos de control
		float pc0x = 1.0 * forma;
		float pc0y = -1.0 * forma + curvatura;
		float pc0z = 0.0;

		float pc1x = -1.0 * forma;
		float pc1y = -1.0 * forma + curvatura;
		float pc1z = 0.0;

		float pc2x = -1.0 * forma;
		float pc2y = 1.0 * forma + curvatura;
		float pc2z = 0.0;

		float pc3x = 1.0 * forma;
		float pc3y = 1.0 * forma + curvatura;
		float pc3z = 0.0;

		// Armamos arreglos para los trozos que conforman la curva
		float pcx012[] = {pc0x, pc1x, pc2x};
		float pcx123[] = {pc1x, pc2x, pc3x};
		float pcx230[] = {pc2x, pc3x, pc0x};
		float pcx301[] = {pc3x, pc0x, pc1x};

		float pcy012[] = {pc0y, pc1y, pc2y};
		float pcy123[] = {pc1y, pc2y, pc3y};
		float pcy230[] = {pc2y, pc3y, pc0y};
		float pcy301[] = {pc3y, pc0y, pc1y};





		// Segmento 0-1-2 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx012);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy012);
			float ppz = q * 0.05f;

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}

		// Segmento 1-2-3 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx123);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy123);
			float ppz = q * 0.05f;

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}

		// Segmento 2-3-0 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx230);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy230);
			float ppz = q * 0.05f;

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}

		// Segmento 3-0-1 de la curva
		for(int j = 0; j < this->CANT_PUNTOS / CANT_CURVAS; j++) 
		{
			// Calculamos los puntos
			float ppx = Matematica::curvaBSpline(j * PASO, pcx301);
			float ppy = Matematica::curvaBSpline(j * PASO, pcy301);
			float ppz = q * 0.05f;

			// Cargamos puntos en el vertex buffer
			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;
		}
	}

	int sentido = 1;
	int k = 0;

	for(int i=0; i < (this->ESTIRAMIENTO-1); i++)
	{
		if(sentido == 1)
		{
			for(int j=0; j <= (this->CANT_PUNTOS-1); j++) {
				this->object_index_buffer[k++] = malla[i][j];
				this->object_index_buffer[k++] = malla[i+1][j];
			}

			sentido = -1;
		}
		else if(sentido == -1)
		{
			for(int j=(this->CANT_PUNTOS-1); j >= 0; j--) {
				this->object_index_buffer[k++] = malla[i][j];
				this->object_index_buffer[k++] = malla[i+1][j];
			}

			sentido = 1;
		}
	}

	// NORMALES

	k = 0;

	for(int i=0; i < (this->ESTIRAMIENTO-1); i++) {
		for(int j=0; j <= (this->CANT_PUNTOS-1); j++)
		{
			float u[3], v[3];
			
			// Tomamos vectores adyacentes u y v
			u[0] = this->object_vertex_buffer[malla[i+1][j] * 3] - 
				this->object_vertex_buffer[malla[i][j] * 3];
			u[1] = this->object_vertex_buffer[malla[i+1][j] * 3 + 1] - 
				this->object_vertex_buffer[malla[i][j] * 3 + 1];
			u[2] = this->object_vertex_buffer[malla[i+1][j] * 3 + 2] - 
				this->object_vertex_buffer[malla[i][j] * 3 + 2];
			
			v[0] = this->object_vertex_buffer[malla[i][j+1] * 3] -
				this->object_vertex_buffer[malla[i][j] * 3];
			v[1] = this->object_vertex_buffer[malla[i][j+1] * 3 + 1] -
				this->object_vertex_buffer[malla[i][j] * 3 + 1];
			v[2] = this->object_vertex_buffer[malla[i][j+1] * 3 + 2] -
				this->object_vertex_buffer[malla[i][j] * 3 + 2];


			// Calculamos la normal a u y v
			float *n = Matematica::productoVectorial(u, v);

			this->object_normal_buffer[k++] = n[0];
			this->object_normal_buffer[k++] = n[1];
			this->object_normal_buffer[k++] = n[2];
		}
	}
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void CangrejoPataPie::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	// Ponemos el objeto en el centro del eje coordenado
	glm::mat4 mPierna = glm::mat4(1.0f);
	mPierna = glm::translate(model_matrix, glm::vec3(0.0, 0.0, 0.0));


	

	///////////////////////////////////////////
	// Bind View Matrix
	GLuint location_view_matrix = glGetUniformLocation(this->programHandle,
		"ViewMatrix"); 

	if(location_view_matrix >= 0) 
		glUniformMatrix4fv(location_view_matrix, 1, GL_FALSE, 
			&view_matrix[0][0]); 

	// Bind Projection Matrix
	GLuint location_projection_matrix = glGetUniformLocation(
		this->programHandle, "ProjectionMatrix"); 
	
	if(location_projection_matrix >= 0) 
		glUniformMatrix4fv( location_projection_matrix, 1, GL_FALSE,
			&projection_matrix[0][0]); 
	//
	///////////////////////////////////////////


	//////////////////////////////////////
	// Bind Light Settings
	glm::vec4 light_position = glm::vec4(8.0f, 8.0f, 2.0f, 1.0f);
	glm::vec3 light_intensity = glm::vec3(1.0f, 1.0f, 1.0f);
	   
	GLuint location_light_position = glGetUniformLocation(this->programHandle, 
		"LightPosition");

	if(location_light_position >= 0) 
		glUniform4fv( location_light_position, 1, &light_position[0]); 

	GLuint location_light_intensity = glGetUniformLocation(
		this->programHandle, "Ld");

	if(location_light_intensity >= 0) 
		glUniform3fv( location_light_intensity, 1, &light_intensity[0]); 
	//
	///////////////////////////////////////////


	// Normal Matrix
	glm::mat3 normal_matrix = glm::mat3 ( 1.0f );

	// Bind Normal MAtrix
	GLuint location_normal_matrix = glGetUniformLocation(this->programHandle, 
		"NormalMatrix"); 
	if( location_normal_matrix >= 0 ) 
		glUniformMatrix3fv( location_normal_matrix, 1, GL_FALSE, 
			&normal_matrix[0][0]); 

	// Bind Model Matrix
	GLuint location_model_matrix = glGetUniformLocation(this->programHandle, 
		"ModelMatrix"); 
	if(location_model_matrix >= 0)
		glUniformMatrix4fv( location_model_matrix, 1, GL_FALSE, 
			&mPierna[0][0]); 

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, object_normal_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
