// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"


// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(int modo);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(int modo);

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int modo, int modo_de_dibujo) ;

   //función que dibuja el objeto en modo ajedrez
   void draw_ajedrez(int modo);

   //función que gestiona las caras pares e impares y sus repectivos colores
   void IndicarColorAjedrez();

   //función creadora de VBOs
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);



   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo

   std::vector<Tupla3i> ladosPar;//vector de los lados pares del objetos
   std::vector<Tupla3i> ladosImpar;//vector de los lados impares del objeto
   std::vector<Tupla3f> colorLadosPar;//vector con el color de cada lado par del objeto
   std::vector<Tupla3f> colorLadosImpar;//vector con el color de cada lado impar del objeto

   int id_vbo_ver;
   int id_vbo_tri;

 
   // completar: tabla de colores, tabla de normales de vértices
} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)



// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
   public:
      ObjRevolucion( const std::string & nombre_ply_perfil );
} ;

#endif
