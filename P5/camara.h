//**************************************************************************
// Practica 5
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#ifndef CAMARA_H
#define CAMARA_H

#include "malla.h"



class Camara : public ObjMallaIndexada{

	private:
		Tupla3f eye;
		Tupla3f at;
		Tupla3f up; 

		Tupla3f reset_eye;
		Tupla3f reset_at;
		Tupla3f reset_up; 


		int type;
		float left, right, near, far, bottom, top;


	public:
		GLfloat angle_x;
		GLfloat angle_y;
		GLfloat distancia;
		Camara(int c_type, float c_left, float c_right, float c_near, float c_far, float c_bottom, float c_top, Tupla3f c_eye, Tupla3f c_at, Tupla3f c_up);
		Camara();
		
		void girar(GLfloat x, GLfloat y, GLfloat z);
		void zoom(float factor);
		void mover(GLfloat x, GLfloat y);

		void reiniciarCamara();
		void setCamara(int c_type, float c_left, float c_right, float c_near, float c_far, float c_bottom, float c_top, Tupla3f c_eye, Tupla3f c_at, Tupla3f c_up);
		void setObserver();
		void setProyeccion(int c_type);
		void aplicarProyeccion();

};

#endif