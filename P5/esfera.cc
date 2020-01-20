#include "esfera.h"


Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf,float radio){
  vertices.clear();
  triangulos.clear();

	std::vector<Tupla3f> p;
	float ang, x, y;

	for ( int i=0; i<=num_instancias_perf; i++){
		
		ang = i*(180/(num_instancias_perf/2));
		ang+=270;

		x = radio * cos(ang * M_PI/180);
		y = radio * sin(ang * M_PI/180);

		p.push_back({x,y,0.0});
	}

	crearMalla(p,num_instancias_perf);

}