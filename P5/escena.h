//**************************************************************************
// Practica 4
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************

#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "cubo.h"
#include "tetrahedron.h"
#include "cilindro.h"
#include "esfera.h"
#include "cono.h"
#include "luz.h"
#include "cuadro.h"
#include "camara.h"


class Escena
{

   private:

   	Ejes ejes;

   	// variables que definen la posicion de la camara en coordenadas polares
   
   	// variables que controlan la ventana y la transformacion de perspectiva
   	GLfloat Width, Height, Front_plane, Back_plane;

   

   	void clear_window();
	void dibujar_objeto_actual();

   	// Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();


   	int objeto_actual = 0 , // objeto actual (el que se visualiza)
       num_objetos   = 0 ; // número de objetos (actualizado al crear los objetos en el constructor)

   	// Objetos de la escena
   	Cubo * cubo = nullptr; // es importante inicializarlo a 'nullptr'
   	tetrahedron * tetra = nullptr;
   	ObjPLY * big_dodge = nullptr;
   	ObjPLY * ant = nullptr;
   	ObjPLY * beethoven = nullptr;
   	ObjRevolucion * objrevolucion = nullptr;
   	Esfera * esfe = nullptr;
   	Cono * cono = nullptr;
   	Cilindro* cilindro = nullptr;
   	ObjJerarquico * modelo_jerar = nullptr;
   	Cuadro *cuadro;


   	int modo;
   	int modo2;
   	bool ajedrez = false;
   	bool ply_bool = false;
   	int modo_de_dibujo = 0;
   	bool animaciones_activadas= false;


   	// contoladores de activación y desactivación de la luces
   	bool activar_luz_1 = false;
   	bool activar_luz_2 = false;	

   	// obajeto de la clase ObjMallaIndexada
   	ObjMallaIndexada *objMalla = nullptr;

   	// iamgen para cargar
   	std::string archivoJPG = "imagen/dali.jpg";

   	// identificador de la textura
  	GLuint ident = 1;

   	// controla el material actual
   	int material_actual = 0;

   	// primera luz blanca (GL_LIGHT0)
   	Luz *luz;

   	// segunda luz morada (GL_LIGHT1)
   	Luz *luz_2;

   	// controla si el suavizado es plano o de gouraud
   	bool suavizado_plano = false;

   	// controla la activación y desactivación de la textura
   	bool textura = false;

   	// objeto antes de activar la textura
   	int objeto_antiguo = 0;

   	// controla el cambio de posicion
   	bool cambia_pos = false;


   	// PRACTICA 5

   	int BUFFER_SIZE = 1000;
   	bool seleccionado0 , seleccionado1 , seleccionado2 , seleccionado3;
  
   public:

   	GLfloat Observer_distance;
   	GLfloat Observer_angle_x;
   	GLfloat Observer_angle_y;

   	std::vector<Camara> camaras;
   	int camaraActual;
      bool primeraPersona;

   	Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

	void mgeDesocupado();
   	void conmutarAnimaciones();

   	void dibujaSeleccion();
   	void procesaPick(int x, int y);

};
#endif
