//**************************************************************************
// Practica 5
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#include "camara.h"



	Camara::Camara(int c_type, float c_left, float c_right, float c_near, float c_far, float c_bottom, float c_top, Tupla3f c_eye, Tupla3f c_at, Tupla3f c_up){
		type = c_type;
		left = c_left;
		right = c_right;
		near = c_near;
		far = c_far;
		bottom = c_bottom;
		top = c_top;
		eye = c_eye;
		at = c_at;
		up = c_up;

		angle_x = 0;
		angle_y = 0;
		distancia = 0;

		reset_eye = c_eye;
		reset_at = c_at;
	}

	void Camara::setCamara(int c_type, float c_left, float c_right, float c_near, float c_far, float c_bottom, float c_top, Tupla3f c_eye, Tupla3f c_at, Tupla3f c_up){
		type = c_type;
		left = c_left;
		right = c_right;
		near = c_near;
		far = c_far;
		bottom = c_bottom;
		top = c_top;
		eye = c_eye;
		at = c_at;
		up = c_up;
	}

	void Camara::setProyeccion(int c_type){
		type = c_type;
	}

	void Camara::aplicarProyeccion(){
		if (this->type == 0){
			glOrtho(left,right,bottom,top,near,far);
		}else{
			glFrustum(left,right,bottom,top,near,far);
		}
	}

	void Camara::girar(GLfloat x, GLfloat y, GLfloat z){
		angle_x += x*0.3;
		angle_y += y*0.3;
		distancia = z;
	}

	void Camara::zoom(float factor){
		eye[2] = factor;
	}

	void Camara::mover(GLfloat x, GLfloat y){
		at[0] += x*0.05;
		at[1] += y*0.05;
	}

	void Camara::setObserver(){
		distancia = eye[2];
		glTranslatef(0,0,-distancia*3);
      	glRotatef(angle_x,0,1,0);
      	glRotatef(angle_y,1,0,0);
		gluLookAt(eye[0],eye[1],eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
	}

	void Camara::reiniciarCamara(){
		eye = reset_eye;
		at = reset_at;
	}