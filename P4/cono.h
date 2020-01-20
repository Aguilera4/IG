//**************************************************************************
// Practica 2
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#ifndef CONO_H
#define CONO_H


#include "malla.h"

class Cono : public ObjRevolucion
{

    public:
      //El constructor es el encargado de crear el perfil del cono
      //después dicho perfil es enviado al método crearMalla() para crear
      //el objeto revolucionado
    	Cono(const int num_vert_perfil, const int num_instancias_perf, float radio, float altura);
} ;

#endif