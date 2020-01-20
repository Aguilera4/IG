//**************************************************************************
// Practica 2
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

#define _USE_MATH_DEFINES
#include <cmath>


// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato(int modo)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
  // ...


	//tamañao de los puntos
  if ( modo == GL_POINTS)
    glPointSize(10.0);

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3,GL_FLOAT,0, vertices.data());
  glDrawElements(modo, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data());
  
  glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido(int modo)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

  if ( id_vbo_ver == 0)
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER,3*vertices.size()*sizeof(float),vertices.data());

  if ( id_vbo_tri == 0)
    id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*triangulos.size()*sizeof(float), triangulos.data());


  glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
  glVertexPointer(3,GL_FLOAT,0,0);
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glEnableClientState(GL_VERTEX_ARRAY);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
  glDrawElements(modo, 3*triangulos.size(), GL_UNSIGNED_INT,0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

  glDisableClientState(GL_VERTEX_ARRAY);
}

GLuint ObjMallaIndexada::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
  GLuint id_vbo;
  glGenBuffers(1, &id_vbo);
  glBindBuffer(tipo_vbo,id_vbo);

  glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

  glBindBuffer(tipo_vbo, 0);
  return id_vbo;
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int modo, int modo_de_dibujo)
{

  if(modo_de_dibujo==0)draw_ModoInmediato(modo);
  else draw_ModoDiferido(modo);

}


void ObjMallaIndexada::draw_ajedrez(int modo){

    //dividimos los lados pares e impares en dos arrays
  for ( int j=0; j < triangulos.size(); j+=1){
    if(j%2 == 0){
      ladosPar.push_back(triangulos[j]);
    }
    else{
      ladosImpar.push_back(triangulos[j]);
    }
  }

  Tupla3f verde = {0.0, 1.0, 0.0};
  Tupla3f azul = {0.0, 0.0, 1.0};

    //metemos tantos colores como vertices hay en el array, Par(rojo) impar(verde)
  for ( int i=0; i<vertices.size(); i++){
    colorLadosPar.push_back(verde);
    colorLadosImpar.push_back(azul);
  }


    glEnableClientState(GL_VERTEX_ARRAY);
   	//idicamos que vamos a hacer uso del array de colores
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3,GL_FLOAT,0,vertices.data());

    glColorPointer(3, GL_FLOAT, 0, colorLadosPar.data());
    glDrawElements(modo, ladosPar.size()*3, GL_UNSIGNED_INT, ladosPar.data());

    glColorPointer(3, GL_FLOAT, 0, colorLadosImpar.data());
    glDrawElements(modo, ladosImpar.size()*3, GL_UNSIGNED_INT, ladosImpar.data());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

void ObjMallaIndexada::calcular_normales()
{
   // completar .....(práctica 3)
}


// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );
}


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************



// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)


ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil){

   ply::read_vertices(nombre_ply_perfil, vertices);
   std::vector<Tupla3f> v = vertices;
   this->crearMalla(v,30);
}

void ObjRevolucion::rotacion(Tupla3f x, Tupla3f & xprima,float ang, int num_instancias_perf){

  float angulo = (2.0*ang*M_PI)/num_instancias_perf;

  float seno = sin(angulo);
  float coseno = cos(angulo);

  xprima = {x[0]*coseno+x[2]*seno, x[1],-x[0]*seno+x[2]*coseno};

}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf){

  float ang = 0.0;
  int tam_original = perfil_original.size();
  int tam_vertices = vertices.size();

  Tupla3f ver_aux;
  Tupla3i cara_aux;

  vertices.clear();
  triangulos.clear();


  // obtiene los vertices rotados
  for ( float i=0; i<=num_instancias_perf-1; i++){
    ang=i;
    for(int j=0; j<=tam_original-1; j++){
      ver_aux=perfil_original[j];
      rotacion(ver_aux,ver_aux,ang,num_instancias_perf);
      vertices.push_back(ver_aux);
    }
  }


  //obtiene los triangulos de revolución
    for(int k=0; k<=num_instancias_perf-1; k++){
      for(int v=0; v<=tam_original-2; v++){
        cara_aux[0]=v+((k+1)%num_instancias_perf)*tam_original;
        cara_aux[1]=v+1+((k+1)%num_instancias_perf)*tam_original;
        cara_aux[2]=v+1+k*tam_original;

        triangulos.push_back(cara_aux);

        cara_aux[0]=v+1+k*tam_original;
        cara_aux[1]=v+k*tam_original;
        cara_aux[2]=v+((k+1)%num_instancias_perf)*tam_original;

        triangulos.push_back(cara_aux);

      }
    }

  Tupla3f aux_v;
  Tupla3i aux_c;


  //tapa inferior
  aux_v[0]=0.0;
  aux_v[1]= perfil_original[tam_original-1][1];
  aux_v[2]=0.0;
  vertices.push_back(aux_v);

  aux_c[0]=tam_original*num_instancias_perf;

  for ( int i=0; i<num_instancias_perf; i++){
    aux_c[1]=(i+1)*tam_original-1;
    aux_c[2]=((i+1)%num_instancias_perf)*tam_original+tam_original-1;
    triangulos.push_back(aux_c);
  }



  //tapa superior
  aux_v[0]=0.0;
  aux_v[1]= perfil_original[0][1];
  aux_v[2]=0.0;
  vertices.push_back(aux_v);


  aux_c[0]=tam_original*num_instancias_perf+1;

  for ( int i=0; i<num_instancias_perf; i++){
    aux_c[1]=((i+1)%num_instancias_perf)*tam_original;
    aux_c[2]=i*tam_original;
    triangulos.push_back(aux_c);
  }
}









