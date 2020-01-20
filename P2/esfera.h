//**************************************************************************
// Practica 2
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************

#ifndef ESFERA_H
#define ESFERA_H


#include "malla.h"

class Esfera : public ObjRevolucion
{

    public:
      //El constructor es el encargado de crear el perfil del esfera
      //después dicho perfil es enviado al método crearMalla() para crear
      //el objeto revolucionado
    	Esfera(const int num_vert_perfil, const int num_instancias_perf, float radio);
} ;

#endif