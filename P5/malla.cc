//**************************************************************************
// Practica 4
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

   glDisable(GL_TEXTURE_2D);
	//tamañao de los puntos
  	if ( modo == GL_POINTS)
    glPointSize(10.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	

  if (glIsEnabled(GL_LIGHTING)){

    // calculamos las normales
    if(normales_vertices.empty()){
      calcular_normales_vertices();
    }

  	glEnable(GL_NORMALIZE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnableClientState(GL_NORMAL_ARRAY);

		glNormalPointer(GL_FLOAT, 0, normales_vertices.data());
  }

	glVertexPointer(3,GL_FLOAT,0, vertices.data());
  	
  glDrawElements(GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data());

	if (glIsEnabled(GL_LIGHTING)){
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_NORMALIZE);
	}

  	glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido(int modo)
{
   glDisable(GL_TEXTURE_2D);

  //if ( id_vbo_ver == 0)
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER,3*vertices.size()*sizeof(float),vertices.data());

  //if ( id_vbo_tri == 0)
    id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*triangulos.size()*sizeof(float), triangulos.data());

  //tamañao de los puntos
    if ( modo == GL_POINTS)
    glPointSize(10.0);

  glEnableClientState(GL_VERTEX_ARRAY);
  

  if (glIsEnabled(GL_LIGHTING)){

    // calculamos las normales
    if(normales_vertices.empty()){
      calcular_normales_vertices();
    }

    glEnable(GL_NORMALIZE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnableClientState(GL_NORMAL_ARRAY);

    glNormalPointer(GL_FLOAT, 0, normales_vertices.data());
  }

    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
    glDrawElements(modo, 3*triangulos.size(), GL_UNSIGNED_INT,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

  if (glIsEnabled(GL_LIGHTING)){
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_NORMALIZE);
  }

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
  	if (modo_de_dibujo == 0){
  		draw_ModoInmediato(modo);  
  	}else if (modo_de_dibujo == 1){
		draw_ModoDiferido(modo);
  	}else {
  		draw_ajedrez(modo);
  	}
}



void ObjMallaIndexada::draw_ajedrez(int modo){

	glDisable(GL_LIGHTING);

  	//dividimos los lados pares e impares en dos arrays
  	for ( int j=0; j < triangulos.size(); j+=1){
    	if(j%2 == 0){
    		ladosPar.push_back(triangulos[j]);
    	}
    	else{
      		ladosImpar.push_back(triangulos[j]);
    	}
  	}

  	Tupla3f color1 = {0.756,0.756,0.756};
  	Tupla3f color2 = {0.255, 0.255, 1.255};

  	//metemos tantos colores como vertices hay en el array, Par(rojo) impar(verde)
  	for ( int i=0; i<vertices.size(); i++){
    	colorLadosPar.push_back(color1);
    	colorLadosImpar.push_back(color2);
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
  if (normales_vertices.empty()){
    calcular_normales_vertices();
  }
}


void ObjMallaIndexada::calcular_normales_vertices(){

	if (normales_triangulos.empty()){
    	calcular_normales_triangulos();
 	}

 	for ( int i =0; i<vertices.size(); i++){
 		normales_vertices.push_back({0.0,0.0,0.0});
 	}

  	for (int j=0; j<triangulos.size(); j++){
    	normales_vertices[triangulos[j][0]] = normales_vertices[triangulos[j][0]] + normales_triangulos[j];
   		normales_vertices[triangulos[j][1]] = normales_vertices[triangulos[j][1]] + normales_triangulos[j];
   		normales_vertices[triangulos[j][2]] = normales_vertices[triangulos[j][2]] + normales_triangulos[j];
  	}
}


void ObjMallaIndexada::calcular_normales_triangulos(){

	Tupla3f vertice_aux1, vertice_aux2, n;

  	for ( int i=0; i<triangulos.size(); i++){
    	vertice_aux1 = vertices[triangulos[i][1]]-vertices[triangulos[i][0]];
    	vertice_aux2 = vertices[triangulos[i][2]]-vertices[triangulos[i][0]];
    	n = vertice_aux1.cross(vertice_aux2);
   		
   		float modulo = sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);

    	normales_triangulos.push_back({n[0]/modulo, n[1]/modulo, n[2]/modulo});
   	}      
}

void ObjMallaIndexada::cambiar_material(int id_material){

	Material material;

	switch(id_material){

		// material magenta
    case 0:
    		material.ambiente = {0.0,0.0,0.0,0.0};
    		material.difusa = {0.5,0.5,0.0,0.0};
	    	material.especular =  {0.6,0.6,0.6,1.0};
	    	material.brillo = 0.25;
	    	break;

    // material verde
	case 1:
			  material.ambiente = {0.0,0.5,0.2,1.0};
	    	material.difusa = {0.0,0.5,0.2,0.0};
	    	material.especular =  {0.0,0.6,0.2,1.0};
	    	material.brillo = 0.1;
	    	break;	

   
    // material rojo
    case 2:		
    		material.ambiente = {0.05,0.0,0.0,0.0};
    		material.difusa = {0.5,0.4,0.4,1.0};
	    	material.especular =  {0.7,0.04,0.04,1.0};
	    	material.brillo = 0.4;
	    	break;

	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *) &material.ambiente);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *) &material.difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &material.especular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,  material.brillo);
}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de triangulos y vértices
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
   this->crearMalla(v,20);
}

void ObjRevolucion::rotacion(Tupla3f x, Tupla3f & xprima,float ang, int num_instancias_perf){
  float angulo = (2.0*ang*M_PI)/num_instancias_perf;
  float seno = sin(angulo);
  float coseno = cos(angulo);
  xprima = {x[0]*coseno+x[2]*seno, x[1],-x[0]*seno+x[2]*coseno};

}

void ObjRevolucion::crearMalla( std::vector<Tupla3f> perfil_original, const int num_instancias_perf){

  float ang = 0.0;
  int tam_original = perfil_original.size();

  Tupla3f ver_inf;
  Tupla3f ver_sup;



  if ( perfil_original[0][0] == 0 && perfil_original[0][2]==0){
    ver_inf = perfil_original[0];
    perfil_original.erase(perfil_original.begin());
    inf_quitado = true;
  }

  if ( perfil_original[tam_original-1][0] == 0 && perfil_original[tam_original-1][2]==0){
    ver_sup = perfil_original[tam_original-1];
    perfil_original.erase(perfil_original.end()-1);
    sup_quitado=true;
  }


  tam_original = perfil_original.size();

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


    //tapa superior	
	if (sup_quitado == false){ // si no hemos quitado el punto medio de la tapa anteriormente
  																		// añadimos el vertice central
  		aux_v[0]=0.0;
  		aux_v[1]= perfil_original[tam_original-1][1];
  		aux_v[2]=0.0;
  		vertices.push_back(aux_v);
	}
	else{	// si lo hemos quitado anteriormente solo lo volvemos a añadir
		vertices.push_back(ver_sup);
	}

 	aux_c[0]=tam_original*num_instancias_perf;

  	for ( int i=0; i<num_instancias_perf; i++){
    	aux_c[1]=(i+1)*tam_original-1;
    	aux_c[2]=((i+1)%num_instancias_perf)*tam_original+tam_original-1;
    	triangulos.push_back(aux_c);
  	}

  //tapa inferior
	if (inf_quitado == false){ //si hemos quitado el punto medio de la tapa anteriormente
		aux_v[0]=0.0;													// añadimos el vertice central
		aux_v[1]= perfil_original[0][1];
		aux_v[2]=0.0;
		vertices.push_back(aux_v);
	}
	else{ // si lo hemos quitado anteriormente lo volvemos a añadir
		vertices.push_back(ver_inf);
	}

  	aux_c[0]=tam_original*num_instancias_perf+1;

	for ( int i=0; i<num_instancias_perf; i++){
    	aux_c[1]=((i+1)%num_instancias_perf)*tam_original;
    	aux_c[2]=i*tam_original;
    	triangulos.push_back(aux_c);
	}
}

void ObjMallaIndexada::carga_textura(GLuint ident_textura,std::string imagen){

  this->imagen.load(imagen.c_str());

  for (long y = 0; y < this->imagen.height(); y ++){
    for (long x = 0; x < this->imagen.width(); x ++){
      unsigned char *r = this->imagen.data(x, y, 0, 0);
      unsigned char *g = this->imagen.data(x, y, 0, 1);
      unsigned char *b = this->imagen.data(x, y, 0, 2);
      datos.push_back(*r);
      datos.push_back(*g);
      datos.push_back(*b);
    }
  }

  glGenTextures(1, &ident_textura);
  glBindTexture(GL_TEXTURE_2D, ident_textura);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->imagen.width(), this->imagen.height(),
      0, GL_RGB, GL_UNSIGNED_BYTE, &datos[0]);
}



void ObjMallaIndexada::activar_textura(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
}

void ObjMallaIndexada::desactivar_textura(){
  glDisable(GL_TEXTURE_2D);
}