//**************************************************************************
// Practica 2
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#ifndef CILINDRO_H
#define CILINDRO_H

#include "malla.h"



class Cilindro : public ObjRevolucion
{

    public:
      //El constructor es el encargado de crear el perfil del cilindro
      //después dicho perfil es enviado al método crearMalla() para crear
      //el objeto revolucionado
    	Cilindro(const int num_vert_perfil, const int num_instancias_perf, float radio, float altura);
} ;

#endif