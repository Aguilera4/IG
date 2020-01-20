//**************************************************************************
// Practica 4
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"
#include "ply_reader.h"
#include "CImg.h"
using namespace cimg_library;
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
    void draw(int modo, int modo_de_dibujo);

    //función que dibuja el objeto en modo ajedrez
    void draw_ajedrez(int modo);

    //función creadora de VBOs
    GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

    //obtiene las coordenadas del ply 
    void obtenerPly();

    //calcula el vector de normales de triangulos (caras)
    void calcular_normales_triangulos();

    //calcula el vector de normales de vertices
    void calcular_normales_vertices();
   
    // calcula tabla de normales de vértices (práctica 3)
    void calcular_normales();

    //alterna entre los 3 materiales
    void cambiar_material(int id_material);

    //carga la imagen 
    void carga_textura(GLuint ident_textura,std::string imagen);

    //activa  textura
    void activar_textura();

    //desactiva textura
    void desactivar_textura();

  protected:

    std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
    std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo

    std::vector<Tupla3i> ladosPar;//vector de los lados pares del objetos
    std::vector<Tupla3i> ladosImpar;//vector de los lados impares del objeto
    std::vector<Tupla3f> colorLadosPar;//vector con el color de cada lado par del objeto
    std::vector<Tupla3f> colorLadosImpar;//vector con el color de cada lado impar del objeto

    int id_vbo_ver;
    int id_vbo_tri;

    // controladores de tapas
    bool sup_quitado = false;
    bool inf_quitado = false;


    std::vector<Tupla3f> normales_vertices; //vector normalizado de vertices
    std::vector<Tupla3f> normales_triangulos; //vector normalizado de triangulos


    // material
    struct Material{
       Tupla4f ambiente; 
	   Tupla4f difusa;
	   Tupla4f especular;
	   float brillo;
    };

    // vector de colores
    std::vector<Tupla3f> colores;

    // vector de coordenadas de textura
    std::vector<Tupla2f> textura_coord;

    // imagen
    CImg<unsigned char> imagen;
    
    // pixel de la imagen
    std::vector<unsigned char> datos;
    
    // identificacion de la textura
    GLuint ident_textura = 1;

} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************


// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{

    public:

      ObjPLY( const std::string & nombre_archivo );

};

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{

    public:
      ObjRevolucion(){};
    	ObjRevolucion( const std::string & nombre_ply_perfil );

      //Método encargado de crear la malla de revolucion de vertices y triangulos
    	void crearMalla( std::vector<Tupla3f>  perfil_original, const int num_instancias_perf);
      
      //Método encargado de rotar un determinado vértice
    	void rotacion(Tupla3f x, Tupla3f & xprima,float ang, int num_instancias_perf);
} ;

#endif