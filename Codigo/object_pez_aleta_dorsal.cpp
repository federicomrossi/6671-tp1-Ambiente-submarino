/*  
 *  CLASS PEZ_ALETA_DORSAL
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
#include "object_pez_aleta_dorsal.h"



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
PezAletaDorsal::PezAletaDorsal() 
{
	// Inicializamos buffers
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_vertex_buffer = NULL;

	this->ESTIRAMIENTO = 30;
}


// Destructor
PezAletaDorsal::~PezAletaDorsal() { }


// Crea un objeto
void PezAletaDorsal::create()
{
	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());



	// Puntos de control de la CURVA SUPERIOR
	float distancia_sup_pc0x = 0.0;
	float distancia_sup_pc0y = -0.15;

	float distancia_sup_pc1x = 2.0;
	float distancia_sup_pc1y = 0.5;

	float distancia_sup_pc2x = 7.0;
	float distancia_sup_pc2y = 0.2;

	float distancia_sup_pc3x = 10.0;
	float distancia_sup_pc3y = -0.18;

	float distancia_sup_pcx[] = {distancia_sup_pc0x, distancia_sup_pc1x, distancia_sup_pc2x, distancia_sup_pc3x};
	float distancia_sup_pcy[] = {distancia_sup_pc0y, distancia_sup_pc1y, distancia_sup_pc2y, distancia_sup_pc3y};


	// Puntos de control de la CURVA INFERIOR
	float distancia_inf_pc0x = 0.0;
	float distancia_inf_pc0y = -0.15;

	float distancia_inf_pc1x = 2.0;
	float distancia_inf_pc1y = 0.1;

	float distancia_inf_pc2x = 7.0;
	float distancia_inf_pc2y = 0.005;

	float distancia_inf_pc3x = 10.0;
	float distancia_inf_pc3y = -0.18;

	float distancia_inf_pcx[] = {distancia_sup_pc0x, distancia_inf_pc1x, distancia_inf_pc2x, distancia_inf_pc3x};
	float distancia_inf_pcy[] = {distancia_sup_pc0y, distancia_inf_pc1y, distancia_inf_pc2y, distancia_inf_pc3y};



	// CREACIÓN DEL OBJETO

	// Configuración del paso entre un punto y otro.
	float PASO = 0.1;

	// Valores para cálculos (no modificar)
	this->CANT_PUNTOS = int(ceil(1.0 / PASO)) + 1;
	int DIMENSIONES = 3;


	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS * this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2 * this->CANT_PUNTOS 
		* (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];


	// Unimos los puntos
	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;


	int i = 0;

	for(int k = 0; k < this->ESTIRAMIENTO; k++)
	{
		float distancia_sup = Matematica::curvaBezier((k * 1.0) / 
			(this->ESTIRAMIENTO-1),	distancia_sup_pcy);

		float distancia_inf = Matematica::curvaBezier((k * 1.0) / 
			(this->ESTIRAMIENTO-1),	distancia_inf_pcy);


		// Puntos de control
		float pc0x = 0.0;
		float pc0y = k;
		float pc0z = 1.0 * distancia_inf - 0.5;

		float pc1x = 0.0;
		float pc1y = k;
		float pc1z = 1.0 * distancia_inf - 0.5;

		float pc2x = 0.0;
		float pc2y = k;
		float pc2z = 0.0 * distancia_sup;

		float pc3x = 0.0;
		float pc3y = k;
		float pc3z = 1.0 * distancia_sup;

		float pcx[] = {pc0x, pc1x, pc2x, pc3x};
		float pcy[] = {pc0y, pc1y, pc2y, pc3y};
		float pcz[] = {pc0z, pc1z, pc2z, pc3z};


		for(int j = 0; j < this->CANT_PUNTOS; j++) 
		{
			float ppx = Matematica::curvaBezier(j * PASO, pcx);
			float ppy = Matematica::curvaBezier(j * PASO, pcy) * 0.05f;
			float ppz = Matematica::curvaBezier(j * PASO, pcz);

			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy ;
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

	for(int i=0; i <= (this->ESTIRAMIENTO-1); i++) {
		for(int j=0; j <= (this->CANT_PUNTOS-1); j++)
		{
			float u[3], v[3];

			int realI, realJ;

			if((j == (this->CANT_PUNTOS-1)) && (i < (this->ESTIRAMIENTO-1)))
			{
				realI = i+1;
				realJ = j-1;
			}
			else if((j < (this->CANT_PUNTOS-1)) && (i == (this->ESTIRAMIENTO-1)))
			{
				realI = i-1;
				realJ = j+1;
			}
			else if((j == (this->CANT_PUNTOS-1)) && (i == (this->ESTIRAMIENTO-1)))
			{
				realI = i-1;
				realJ = j-1;
			}
			else
			{
				realI = i+1;
				realJ = j+1;
			}
			
			// Tomamos vectores adyacentes u y v
			u[0] = this->object_vertex_buffer[malla[realI][j] * 3] - 
				this->object_vertex_buffer[malla[i][j] * 3];
			u[1] = this->object_vertex_buffer[malla[realI][j] * 3 + 1] - 
				this->object_vertex_buffer[malla[i][j] * 3 + 1];
			u[2] = this->object_vertex_buffer[malla[realI][j] * 3 + 2] - 
				this->object_vertex_buffer[malla[i][j] * 3 + 2];
			
			v[0] = this->object_vertex_buffer[malla[i][realJ] * 3] -
				this->object_vertex_buffer[malla[i][j] * 3];
			v[1] = this->object_vertex_buffer[malla[i][realJ] * 3 + 1] -
				this->object_vertex_buffer[malla[i][j] * 3 + 1];
			v[2] = this->object_vertex_buffer[malla[i][realJ] * 3 + 2] -
				this->object_vertex_buffer[malla[i][j] * 3 + 2];

			float *n;

			if((j == (this->CANT_PUNTOS-1)) && (i < (this->ESTIRAMIENTO-1)))
				// Calculamos la normal a u y v
				n = Matematica::productoVectorial(v, u);
			else if((j < (this->CANT_PUNTOS-1)) && (i == (this->ESTIRAMIENTO-1)))
				// Calculamos la normal a u y v
				n = Matematica::productoVectorial(v, u);
			else if((j == (this->CANT_PUNTOS-1)) && (i == (this->ESTIRAMIENTO-1)))
				// Calculamos la normal a u y v
				n = Matematica::productoVectorial(u, v);
			else
				// Calculamos la normal a u y v
				n = Matematica::productoVectorial(u, v);

			n = Matematica::normalizar(n);

			this->object_normal_buffer[k++] = n[0];
			this->object_normal_buffer[k++] = n[1];
			this->object_normal_buffer[k++] = n[2];
		}
	}
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PezAletaDorsal::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glUseProgram(this->programHandle);
	
	// Centramos la aleta en el centro del eje de coordenadas
	glm::mat4 mAleta = glm::mat4(1.0f);
	mAleta = glm::translate(model_matrix, glm::vec3(0.0, -0.75, 0.0));


	// Bind View Matrix
	// ################t_motion +=0.01;t_motion +=0.01;
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



	// Bind Light Settings
	// ###################

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
			&mAleta[0][0]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, object_normal_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
