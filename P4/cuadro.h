//**************************************************************************
// Practica 4
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#ifndef CUADRO_H
#define CUADRO_H

#include "malla.h"
#include "aux.h"



class Cuadro : public ObjMallaIndexada {
   public:
   Cuadro();
   void dibujar_cuadro(GLuint ident_textura);
} ;

#endif