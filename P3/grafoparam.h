// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....
#include "cilindro.h"
#include "cubo.h"
#include "cono.h"


constexpr int num_parametros =3 ; // número de parámetros o grados de libertad
                                   // de este modelo

class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( const int p_modo_vis, const bool p_usar_diferido, bool ajedrez );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void rueda( const float radio_cil);
   void cruceta();
   void foco();
   void brazo(float movimiento_articulacion_1);
   void brazo2(float movimiento_articulacion_1);



   // objetos tipo malla indexada (nodos terminales)

   Cilindro * cilindro = nullptr ;
   Cubo *     cubo     = nullptr ;
   Cono * cono = nullptr;
   ObjPLY * big_dodge = nullptr;

   // parámetros de la llamada actual (o última) a 'draw'
   int modo_vis ;      // modo de visualización
   bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)
   bool modo_ajedrez;


   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

   float altura_1,       // altura de la primera columna
         ag_rotacion_1,  // ángulo en grados de rotación (1)
         altura_2,
         altura_3,       // altura de la segunda columna
         ag_rotacion_2,  // ángulo en grados de rotación (2)
         ag_rotacion_3  ; 

} ;

#endif
