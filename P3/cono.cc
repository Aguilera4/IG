#include "cono.h"


Cono::Cono(const int num_vert_perfil, const int num_instancias_perf,float radio, float altura){
  std::vector<Tupla3f> p;
  Tupla3f aux;
  
  p.push_back({0.0,-altura,0.0});
  p.push_back({radio,-altura,0.0});
  p.push_back({0.0, altura,0.0});
  


  crearMalla(p,num_instancias_perf);

}