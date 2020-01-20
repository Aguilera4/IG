//**************************************************************************
// Practica 1
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#include "cuadro.h"


//// CONSTRUCTOR DE LA CLASE CUADRO ///////////////

	Cuadro::Cuadro(){
 // inicializar la tabla de vértices
   vertices =  {  {4.0, 4.0,4.0}, // 0
                  {-4.0, -4.0, 4.0}, // 1
                  {4.0, -4.0, 4.0}, // 2
                  {-4.0,  4.0, 4.0}, // 3
               };


   triangulos = {{0, 1, 2},{3, 1, 0},{2, 1, 0},{1, 3, 0}};    

   
  textura_coord.push_back({1,0});
  textura_coord.push_back({0,1});
  textura_coord.push_back({1,1});

  textura_coord.push_back({0,0});
  textura_coord.push_back({0,1});
  textura_coord.push_back({1,0});

  textura_coord.push_back({1,0});
  textura_coord.push_back({0,1});
  textura_coord.push_back({1,1});

  textura_coord.push_back({0,0});
  textura_coord.push_back({0,1});
  textura_coord.push_back({1,0});
   
}


void Cuadro::dibujar_cuadro(GLuint ident_textura){
	 glPointSize(10.0);

  if(normales_vertices.empty()){
    calcular_normales_vertices();
  }
         
  glColor3f(1.0,1.0,1.0); 

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glEnable(GL_NORMALIZE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertices.data());
  glNormalPointer(GL_FLOAT, 0, normales_vertices.data());
  glTexCoordPointer(2, GL_FLOAT, 0, textura_coord.data());

  glDrawElements( GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data()) ;

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
  }
