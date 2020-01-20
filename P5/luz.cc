//**************************************************************************
// Practica 4
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#include "luz.h"



	Luz::Luz(GLenum p_luz_ind, Tupla4f p_luz_ambiente, Tupla4f p_luz_difusa, Tupla4f p_luz_especular , Tupla4f p_luz_pos){
		luz_ind = p_luz_ind;
		luz_difusa = p_luz_difusa;
		luz_especular = p_luz_especular;
		luz_ambiente = p_luz_ambiente;
		luz_posicion = p_luz_pos;
	}

	void Luz::activar(){
		glEnable(GL_LIGHTING);
		glEnable(luz_ind);

		glLightfv(luz_ind, GL_AMBIENT, (GLfloat *) &luz_ambiente);
		glLightfv(luz_ind, GL_DIFFUSE, (GLfloat *) &luz_difusa);
		glLightfv(luz_ind, GL_SPECULAR, (GLfloat *) &luz_especular);
		glLightfv(luz_ind, GL_POSITION, (GLfloat *) &luz_posicion);
	}

	void Luz::desactivar(){
		glDisable(GL_LIGHTING);
		glDisable(luz_ind);
	}


	void Luz::cambia_pos_luz(){
		ang += 10.0;
		if(ang == 360.0){
			ang =0.0;
		}
		
		if (ang >= 0.0){
			glPushMatrix();
			glRotatef(ang,0,1,0);
			glLightfv(luz_ind, GL_POSITION, (GLfloat *) &luz_posicion);
			glPopMatrix();
		}
	}