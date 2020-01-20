//**************************************************************************
// Practica 4
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#ifndef LUZ_H
#define LUZ_H

#include "malla.h"



class Luz : public ObjMallaIndexada {
	public:
		Luz(GLenum p_luz_ind,Tupla4f p_luz_ambiente, Tupla4f p_luz_difusa, Tupla4f p_luz_especular,Tupla4f p_luz_pos);
		void activar();
		void desactivar(GLenum p_luz_ind);
		void cambia_pos_luz();

		GLenum luz_ind;

		float ang = 0.0;

		Tupla4f luz_posicion;
		Tupla4f luz_ambiente;
		Tupla4f luz_difusa;
		Tupla4f luz_especular;
};

#endif