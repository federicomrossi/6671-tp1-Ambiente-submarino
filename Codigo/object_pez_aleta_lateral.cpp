/*  
 *  CLASS PEZ_ALETA_LATERAL
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
#include "object_pez_aleta_lateral.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/PezAletaLateralVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/PezAletaLateralFShader.frag";
}




/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
PezAletaLateral::PezAletaLateral() 
{
	// Valores por defecto
	this->tiempo = 0.0f;

	// Inicializamos buffers
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_tangent_buffer = NULL;
	this->object_texture_buffer = NULL;
	this->object_vertex_buffer = NULL;

	this->ESTIRAMIENTO = 40;
}


// Destructor
PezAletaLateral::~PezAletaLateral() { }


// Crea un objeto
// PRE: 'orientacion' define si la aleta se curva hacia la derecha (-1) o 
// hacia la izquierda (1).
void PezAletaLateral::create(int orientacion)
{
	// Almacenamos la orientación especificada
	this->ORIENTACION_ALETA = orientacion;

	// Creamos el eje coordenado
	// this->ejeCoordenado.create(3);

		// Cargamos la textura
	this->loadAndInitTexture("textures/pez-aleta-texture-02.jpg");

	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());


	// Puntos de control de la CURVA SUPERIOR
	float distancia_sup_pc0x = 0.0;
	float distancia_sup_pc0y = 1.0;

	float distancia_sup_pc1x = 3.0;
	float distancia_sup_pc1y = 0.0;

	float distancia_sup_pc2x = 10.0;
	float distancia_sup_pc2y = 5.0;

	float distancia_sup_pc3x = 10.0;
	float distancia_sup_pc3y = 3.0;

	float distancia_sup_pcx[] = {distancia_sup_pc0x, distancia_sup_pc1x, distancia_sup_pc2x, distancia_sup_pc3x};
	float distancia_sup_pcy[] = {distancia_sup_pc0y, distancia_sup_pc1y, distancia_sup_pc2y, distancia_sup_pc3y};

	// Puntos de control de la CURVA INFERIOR
	float distancia_inf_pc0x =0.0;
	float distancia_inf_pc0y = 1.0;

	float distancia_inf_pc1x = 3.0;
	float distancia_inf_pc1y = 0.0;

	float distancia_inf_pc2x = 10.0;
	float distancia_inf_pc2y = 5.0;

	float distancia_inf_pc3x = 10.0;
	float distancia_inf_pc3y = 3.0;

	float distancia_inf_pcx[] = {distancia_inf_pc0x, distancia_inf_pc1x, distancia_inf_pc2x, distancia_inf_pc3x};
	float distancia_inf_pcy[] = {distancia_inf_pc0y, distancia_inf_pc1y, distancia_inf_pc2y, distancia_inf_pc3y};


	// Puntos de control de la CURVA DE ONDULACION
	float ondulacion_pc0x =0.0;
	float ondulacion_pc0y = 0.0;
	float ondulacion_pc0z =0.0;

	float ondulacion_pc1x = 2.0;
	float ondulacion_pc1y = 0.0;
	float ondulacion_pc1z = 0.0;

	float ondulacion_pc2x = 5.0;
	float ondulacion_pc2y = this->ORIENTACION_ALETA * 1.5;
	float ondulacion_pc2z = 0.0;

	float ondulacion_pc3x = 10.0;
	float ondulacion_pc3y = this->ORIENTACION_ALETA * 1.0;
	float ondulacion_pc3z = 0.0;

	float ondulacion_pcx[] = {ondulacion_pc0x, ondulacion_pc1x, ondulacion_pc2x, ondulacion_pc3x};
	float ondulacion_pcy[] = {ondulacion_pc0y, ondulacion_pc1y, ondulacion_pc2y, ondulacion_pc3y};
	float ondulacion_pcz[] = {ondulacion_pc0z, ondulacion_pc1z, ondulacion_pc2z, ondulacion_pc3z};



	// CREACIÓN DEL OBJETO

	// Configuración del paso entre un punto y otro.
	float PASO = 0.2;

	// Valores para cálculos (no modificar)
	this->CANT_PUNTOS = int(ceil(1.0 / PASO)) + 1;
	int DIMENSIONES = 3;
	int DIMENSIONES_TEXTURA = 2;


	if (this->object_vertex_buffer != NULL)
		delete this->object_vertex_buffer;

	this->object_vertex_buffer_size = DIMENSIONES * this->CANT_PUNTOS * this->ESTIRAMIENTO;
	this->object_vertex_buffer = new GLfloat[this->object_vertex_buffer_size];

	this->object_texture_buffer_size = DIMENSIONES_TEXTURA * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO; 
	this->object_texture_buffer = new GLfloat[this->object_vertex_buffer_size];


	if (this->object_index_buffer != NULL)
		delete this->object_index_buffer;

	this->object_index_buffer_size = 2 * this->CANT_PUNTOS 
		* (this->ESTIRAMIENTO-1);
	this->object_index_buffer = new GLuint[this->object_index_buffer_size];

	this->object_normal_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_normal_buffer = new GLfloat[this->object_normal_buffer_size];

	this->object_tangent_buffer_size = DIMENSIONES * this->CANT_PUNTOS 
		* this->ESTIRAMIENTO;
	this->object_tangent_buffer = new GLfloat[this->object_tangent_buffer_size];

	// Unimos los puntos
	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;


	int i = 0;
	int y = 0;
	int w = 0;
	int z = 0;

	for(int k = 0; k < this->ESTIRAMIENTO; k++)
	{
		// Calculamos el ancho de fragmento de la hoja
		float paso_actual = (k * 1.0) / (this->ESTIRAMIENTO-1);

		float distancia_sup = Matematica::curvaBezier((k * 1.0) / 
			(this->ESTIRAMIENTO-1),	distancia_sup_pcy);

		float distancia_inf = Matematica::curvaBezier((k * 1.0) / 
			(this->ESTIRAMIENTO-1),	distancia_inf_pcy);

		float ondulacion = Matematica::curvaBezier((k * 1.0) / 
			(this->ESTIRAMIENTO-1),	ondulacion_pcy);

		// Calculamos el vector tangente dado por el doblez de la hoja
		float t_barrido[3];
		Matematica::vectorTangenteCurvaBezier(paso_actual, ondulacion_pcx, ondulacion_pcy, ondulacion_pcz, t_barrido);


		// Puntos de control
		float pc0x = ondulacion * 0.4;
		float pc0y = k;
		float pc0z = -0.30 * distancia_inf;

		float pc1x = ondulacion * 0.4;
		float pc1y = k  + 6.0;
		float pc1z = -0.2 * distancia_inf;

		float pc2x = ondulacion * 0.4;
		float pc2y = k + 6.0;
		float pc2z = 0.2  * distancia_sup;

		float pc3x = ondulacion * 0.4;
		float pc3y = k;
		float pc3z = 0.30 * distancia_sup;

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

			this->object_texture_buffer[y++] = ((k * 1.0) 
				/ (this->ESTIRAMIENTO-1));
			this->object_texture_buffer[y++] = (j * PASO);

			// Calculamos el vector tangente dado por la curvatura de la hoja
			float t[3];
			Matematica::vectorTangenteCurvaBezier(j * PASO, pcx, pcy, pcz, t);

			// Calculamos la normal con los vectores tangentes obtenidos
			float *temp = Matematica::productoVectorial(t, t_barrido);
			float *n = Matematica::normalizar(temp);

			// Cargamos las coordenadas del vector normal en el buffer
			this->object_normal_buffer[w++] = n[0];
			this->object_normal_buffer[w++] = n[1];
			this->object_normal_buffer[w++] = n[2];
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
}


// Renderiza el objeto (lo dibuja).
// PRE: 'model_matrix' es la matriz que contiene los datos de cómo
// debe renderizarce el objeto.
void PezAletaLateral::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glUseProgram(this->programHandle);

	this->changeObjectColor(255, 255, 255);
	

	// Bind tiempo para variación de movimiento
	// ########################################
	GLfloat algae_time = glGetUniformLocation(this->programHandle,
		"Tiempo");
	this->tiempo += 0.01f;

	if(algae_time >= 0)
		glUniform1f(algae_time, this->tiempo); 


	GLfloat location_sentido = glGetUniformLocation(this->programHandle,
		"Sentido");

	if(location_sentido >= 0)
		glUniform1f(location_sentido, this->ORIENTACION_ALETA); 


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

	glm::vec3 light_intensity = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec4 light_position = glm::vec4(8.0f, 8.0f, 2.0f, 1.0f);
	glm::vec3 La = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ld = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ls = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Ka = glm::vec3(0 / 255.0f,
							 85 / 255.0f, 
							 0 / 255.0f);
	this->changeObjectColor(0, 255, 0);
	glm::vec3 Kd = glm::vec3(this->R / 255.0f,
							 this->G / 255.0f, 
							 this->B / 255.0f);
	glm::vec3 Ks = glm::vec3(1.0f, 1.0f, 1.0f);
	float Shininess = 1.0;

	// Light Intensity
	GLuint location_light_intensity = glGetUniformLocation(this->programHandle, 
		"LightIntensity");

	if(location_light_intensity >= 0) 
		glUniform4fv( location_light_intensity, 1, &light_intensity[0]); 

	// Light Position
	GLuint location_light_position = glGetUniformLocation(this->programHandle, 
		"LightPosition");

	if(location_light_position >= 0) 
		glUniform4fv( location_light_position, 1, &light_position[0]); 

	// La
	GLuint location_la = glGetUniformLocation(
		this->programHandle, "La");

	if(location_la >= 0) 
		glUniform3fv( location_la, 1, &La[0]); 
	
	// Ld
	GLuint location_ld = glGetUniformLocation(
		this->programHandle, "Ld");

	if(location_ld >= 0) 
		glUniform3fv( location_ld, 1, &Ld[0]); 

	// Ls
	GLuint location_ls = glGetUniformLocation(
		this->programHandle, "Ls");

	if(location_ls >= 0) 
		glUniform3fv( location_ls, 1, &Ls[0]); 


	// Ka
	GLuint location_ka = glGetUniformLocation(
		this->programHandle, "Ka");

	if(location_ka >= 0) 
		glUniform3fv( location_ka, 1, &Ka[0]); 
	
	// Kd
	GLuint location_kd = glGetUniformLocation(
		this->programHandle, "Kd");

	if(location_kd >= 0) 
		glUniform3fv( location_kd, 1, &Kd[0]); 

	// Ks
	GLuint location_ks = glGetUniformLocation(
		this->programHandle, "Ks");

	if(location_ks >= 0) 
		glUniform3fv( location_ks, 1, &Ks[0]); 


	// Shininess
	GLfloat location_shininess = glGetUniformLocation(this->programHandle,
		"Shininess");

	if(location_shininess >= 0)
		glUniform1f(location_shininess, Shininess);





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
			&model_matrix[0][0]);


	// Set the Tex1 sampler uniform to refer to texture unit 0
	int loc = glGetUniformLocation(this->programHandle, "Tex1");

	if( loc >= 0 )
		// We indicate that Uniform Variable sampler2D "text" uses  Texture Unit 0 
		glUniform1i(loc, 0);
	else
		fprintf(stderr, "Uniform variable Tex1 not found!\n");


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->object_vertex_buffer);
	glNormalPointer(GL_FLOAT, 0, object_normal_buffer);
	glTexCoordPointer(2, GL_FLOAT, 0, this->object_texture_buffer);

	glDrawElements(GL_TRIANGLE_STRIP, this->object_index_buffer_size, GL_UNSIGNED_INT, 
		this->object_index_buffer);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
