/*  
 *  CLASS PEZ_ALETA_DORSAL
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>

#include "lib_matematica.h"
#include "object_planta_hoja_tipo02.h"



// Constantes de CONFIGURACION
namespace {
	
	// Ruta del archivo del vertex shader
	const std::string FILE_VERT_SHADER = "shaders/HojaPlantaVShader.vert";
	
	// Ruta del archivo del fragment shader
	const std::string FILE_FRAG_SHADER = "shaders/HojaPlantaFShader.frag";
}




/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


// Constructor
PlantaHojaTipo02::PlantaHojaTipo02()
{
	// Valores por defecto
	this->tiempo = 0.0f;

	// Inicializamos buffers
	this->object_index_buffer = NULL;
	this->object_normal_buffer = NULL;
	this->object_texture_buffer = NULL;
	this->object_vertex_buffer = NULL;

	this->ESTIRAMIENTO = 15;
	this->ESPACIADO_ESTIRAMIENTO = 0.2;
}


// Destructor
PlantaHojaTipo02::~PlantaHojaTipo02() { }


// Crea un objeto
void PlantaHojaTipo02::create()
{
	// Cargamos la textura
	this->loadAndInitTexture("textures/leaf-texture-01.jpg");

	// Cargamos los shaders del objeto
	this->loadShaderPrograms(FILE_VERT_SHADER.c_str(),
							 FILE_FRAG_SHADER.c_str());



	// Puntos de control de la CURVA DE GROSOR

	float grosor_pc0x = 0.0;
	float grosor_pc0y = 0.0;

	float grosor_pc1x = 8.5;
	float grosor_pc1y = 0.0;

	float grosor_pc2x = 9.0;
	float grosor_pc2y = 0.2;

	float grosor_pc3x = 10.0;
	float grosor_pc3y = 0.0;

	float grosor_pcx[] = {grosor_pc0x, grosor_pc1x, grosor_pc2x, grosor_pc3x};
	float grosor_pcy[] = {grosor_pc0y, grosor_pc1y, grosor_pc2y, grosor_pc3y};


	// Puntos de control de la CURVA DE DEFORMACIÓN

	float deformacion_pc0x = 0.0;
	float deformacion_pc0y = 0.0;
	float deformacion_pc0z = 0.0;

	float deformacion_pc1x = 2.0;
	float deformacion_pc1y = 0.4;
	float deformacion_pc1z = 0.0;

	float deformacion_pc2x = 8.0;
	float deformacion_pc2y = -0.15;
	float deformacion_pc2z = 0.0;

	float deformacion_pc3x = 10.0;
	float deformacion_pc3y = 0.0;
	float deformacion_pc3z = 0.0;

	float deformacion_pcx[] = {deformacion_pc0x, deformacion_pc1x,
		deformacion_pc2x, deformacion_pc3x};
	float deformacion_pcy[] = {deformacion_pc0y, deformacion_pc1y,
		deformacion_pc2y, deformacion_pc3y};
	float deformacion_pcz[] = {deformacion_pc0z, deformacion_pc1z,
		deformacion_pc2z, deformacion_pc3z};



	// CREACIÓN DEL OBJETO

	// Configuración del paso entre un punto y otro.
	float PASO = 0.25;

	// Valores para cálculos (no modificar)
	this->CANT_PUNTOS = int(ceil(1.0 / PASO)) + 1;
	int DIMENSIONES = 3;
	int DIMENSIONES_TEXTURA = 2;
	int OBJ_ALTURA = 5;


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


	// Unimos los puntos

	int malla[this->ESTIRAMIENTO][this->CANT_PUNTOS];

	int e = 0;
	for(int m = 0; m < this->ESTIRAMIENTO; m++)
		for(int n = 0; n < this->CANT_PUNTOS; n++)
			malla[m][n] = e++;


	int i = 0;
	int y = 0;
	int w = 0;

	for(int k = 0; k < this->ESTIRAMIENTO; k++)
	{
		// Calculamos el ancho de fragmento de la hoja
		float paso_actual = (k * 1.0) / (this->ESTIRAMIENTO-1);

		float distancia = Matematica::curvaBezier(paso_actual,	grosor_pcy);

		// Calculamos la deformación (doblez) de la hoja
		float deformacion = Matematica::curvaBezier(paso_actual, deformacion_pcy);

		// Calculamos el vector tangente dado por el doblez de la hoja
		float t_barrido[3];
		Matematica::vectorTangenteCurvaBezier(paso_actual, deformacion_pcy, deformacion_pcz, deformacion_pcx, t_barrido);


		// Puntos de control
		float pc0x = 0.0 * distancia + deformacion;
		float pc0y = -1.0 * distancia;
		float pc0z = k;

		float pc1x = -0.6 * distancia + deformacion;
		float pc1y = -1.0 * distancia / 2.0;
		float pc1z = k;

		float pc2x = -0.6 * distancia + deformacion;
		float pc2y = 1.0 * distancia / 2.0;
		float pc2z = k;

		float pc3x = 0.0 * distancia + deformacion;
		float pc3y = 1.0 * distancia;
		float pc3z = k;

		float pcx[] = {pc0x, pc1x, pc2x, pc3x};
		float pcy[] = {pc0y, pc1y, pc2y, pc3y};
		float pcz[] = {pc0z, pc1z, pc2z, pc3z};


		for(int j = 0; j < this->CANT_PUNTOS; j++) 
		{
			float ppx = Matematica::curvaBezier(j * PASO, pcx);
			float ppy = Matematica::curvaBezier(j * PASO, pcy);
			float ppz = k * this->ESPACIADO_ESTIRAMIENTO * 1.0f;

			this->object_vertex_buffer[i++] = ppx;
			this->object_vertex_buffer[i++] = ppy;
			this->object_vertex_buffer[i++] = ppz;


			this->object_texture_buffer[y++] = (j * PASO);
			this->object_texture_buffer[y++] = ((k * 1.0) 
				/ (this->ESTIRAMIENTO-1));

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


	// Tejemos los puntos insertandolos en el index buffer para crear
	// la superficie del objeto

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
void PlantaHojaTipo02::render(glm::mat4 model_matrix, glm::mat4 &view_matrix, 
	glm::mat4 &projection_matrix)
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glUseProgram(this->programHandle);

	this->changeObjectColor(0, 200, 0);

	// Bind tiempo para variación de movimiento
	// ########################################
	GLfloat algae_time = glGetUniformLocation(this->programHandle,
		"TIMEEE");
	this->tiempo += 0.01f;

	// if(algae_time >= 0)
	glUniform1f(algae_time, this->tiempo); 


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

	glm::vec3 light_intensity = glm::vec3(0.7f, 0.7f, 0.7f);
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
	

	// Fog
	float FogMinDist = 4.0;
	float FogMaxDist = 10.0;
	glm::vec3 FogColor = glm::vec3(0.0f / 255.0, 
								   36.0f / 255.0,
								   60.0f / 255.0);


	// Light Intensity
	GLuint location_light_intensity = glGetUniformLocation(this->programHandle, 
		"LightIntensity");

	if(location_light_intensity >= 0) 
		glUniform3fv( location_light_intensity, 1, &light_intensity[0]); 

	// Light Position
	GLuint location_light_position = glGetUniformLocation(this->programHandle, 
		"LightPosition");

	if(location_light_position >= 0) 
		glUniform4fv( location_light_position, 1, &light_position[0]); 

	// // La
	// GLuint location_la = glGetUniformLocation(
	// 	this->programHandle, "La");

	// if(location_la >= 0) 
	// 	glUniform3fv( location_la, 1, &La[0]); 
	
	// // Ld
	// GLuint location_ld = glGetUniformLocation(
	// 	this->programHandle, "Ld");

	// if(location_ld >= 0) 
	// 	glUniform3fv( location_ld, 1, &Ld[0]); 

	// // Ls
	// GLuint location_ls = glGetUniformLocation(
	// 	this->programHandle, "Ls");

	// if(location_ls >= 0) 
	// 	glUniform3fv( location_ls, 1, &Ls[0]); 


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


	
	// FoxMaxDist
	GLfloat location_fogMaxDist = glGetUniformLocation(this->programHandle,
		"FogMaxDist");

	if(location_fogMaxDist >= 0)
		glUniform1f(location_fogMaxDist, FogMaxDist);


	// FoxMinDist
	GLfloat location_fogMinDist = glGetUniformLocation(this->programHandle,
		"FogMinDist");

	if(location_fogMinDist >= 0)
		glUniform1f(location_fogMinDist, FogMinDist); 


	// FogColor
	GLuint location_FogColor = glGetUniformLocation(
		this->programHandle, "FogColor");

	if(location_FogColor >= 0) 
		glUniform3fv(location_FogColor, 1, &FogColor[0]); 



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
		fprintf(stderr, "Uniform variable TexPlantaHojaTipo02 not found!\n");


	// Activamos textura
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);


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


// Permite setear la amplitud de la hoja. Debe setearse antes de crear
// el objeto.
void PlantaHojaTipo02::setAmplitud(float amplitud)
{

}


// Permite setear la velocidad de movimiento de la hoja. Debe setearse 
// antes de crear el objeto.
void PlantaHojaTipo02::setVelocidad(float velocidad)
{

}
