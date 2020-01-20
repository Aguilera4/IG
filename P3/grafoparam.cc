// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cilindro = new Cilindro( 4, 16, 1, 0.5 );
   cubo     = new Cubo();
   cono 	= new Cono(10,10,0.5,0.5);
   big_dodge = new ObjPLY("plys/big_dodge.ply");
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

   constexpr float vp = 2.5 ;

   switch( iparam )
   {
 
      	case 0:
         	// altura 2: oscila entre 1.1 y 1.9, a 0.8 oscilaciones por segundo
         	altura_2 = 1.5 + 15.0*sin( 0.8*(2.0*M_PI*valor_na) );
         	break ;
      	case 1:
        	 // ángulo en grados de rotacion 2 (cubo azul)
         	// oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
         	// (inicialmente es -7.5 grados)
         	ag_rotacion_2 = -7.5 + 37.5*sin( 1.5*(2.0*M_PI*valor_na) );
         	break ;

       	case 2:
         // ángulo en grados de rotacion 2 (cubo azul)
         // oscila entre -45 y 30 grados, a 1.5 oscilaciones por segundo
         // (inicialmente es -7.5 grados)
         ag_rotacion_3 =37.5*sin( 3*(0.53*M_PI*valor_na) );
         altura_3 = 1.5 + 15.0*sin( 0.8*(2.0*M_PI*valor_na) );
         break ;
      
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const int p_modo_vis, const bool p_usar_diferido, bool ajedrez )
{
   // asegurarnos que está inicializado ok

   assert( cubo     != nullptr );
   assert( cilindro != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = p_modo_vis ;
   usar_diferido = p_usar_diferido ;
   modo_ajedrez = ajedrez;
   // dibujar objetos

    constexpr float
      sep       = 1.5,  // separación entre centros de las columnas
      radio_cil = 0.5 , // radio del cilindro más fino
      radio_cil2 = radio_cil+0.1 ; // radio del cilindro más grueso

    glColor3f(0.0,0.0,0.0);  

    glPushMatrix();
    	glTranslatef(-altura_3,-40.0,0.0);

   
    	// Rueda 1  
    	glPushMatrix();
      		glTranslatef(23.0,0.0,0.0);
      		glRotatef(ag_rotacion_3,0.0,0.0,1.0);
      		rueda(radio_cil);
    	glPopMatrix();

    	//Rueda 2
		glPushMatrix();
      		glTranslatef(-23.0,0.0,0.0);
      		glRotatef(ag_rotacion_3,0.0,0.0,1.0);
      		rueda(radio_cil);
    	glPopMatrix();
    
    	//Rueda 3
    	glPushMatrix();
      		glTranslatef(0.0,0.0,23.0);
      		glRotatef(ag_rotacion_3,0.0,0.0,1.0);
      		rueda(radio_cil);
    	glPopMatrix();

    	//Rueda 4
		glPushMatrix();
      		glTranslatef(0.0,0.0,-23.0);
      		glRotatef(ag_rotacion_3,0.0,0.0,1.0);
      		rueda(radio_cil);
		glPopMatrix();


		//cruceta
		glPushMatrix();
	    	glColor3f(128.0,0.0,0.0);
			cruceta();
		glPopMatrix();  


		//cilindro central
		glPushMatrix();
			glColor3f(0.756,0.756,0.756);
			glScalef(2.0,75.0,2.0);
			glTranslatef(0.0,0.57,0.0);
			if ( modo_ajedrez == true){
				cilindro->draw_ajedrez(modo_vis);
			}
			else{
				cilindro->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();


		//brazo superior
		glPushMatrix();
			glColor3f(0.0,0.0,0.0);
			glTranslatef(0.0,altura_2,0.0);
			brazo(ag_rotacion_2);
		glPopMatrix();


		glPushMatrix();
			glColor3f(0.0,0.0,1.0);
			glTranslatef(0.0,80.0,0.0);
			glRotatef(ag_rotacion_2,0.0,1.0,0.0);
			if ( modo_ajedrez == true){
				big_dodge->draw_ajedrez(modo_vis);
			}
			else{
				big_dodge->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

	glPopMatrix();
}

// --------------------------------------------------------------------

void GrafoParam::rueda(const float radio_cil)
{
    glPushMatrix();
   		glScalef(5,5,5);
		glRotatef(90.0,1.0,0.0,0.0);
    		if ( modo_ajedrez == true){
				cilindro->draw_ajedrez(modo_vis);
			}
			else{
				cilindro->draw(modo_vis, usar_diferido);
			}
   glPopMatrix();
}

void GrafoParam::cruceta(){

	glPushMatrix();

		glTranslatef(0.0,6.0,0.0);

		glPushMatrix();
			glScalef(5.0,3.0,50.0);
			glRotatef(90.0,0.0,1.0,0.0);
			if ( modo_ajedrez == true){
				cubo->draw_ajedrez(modo_vis);
			}
			else{
				cubo->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

		glPushMatrix();
			glScalef(50.0,3.0,5.0);
			if ( modo_ajedrez == true){
				cubo->draw_ajedrez(modo_vis);
			}
			else{
				cubo->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

	glPopMatrix();
}


void GrafoParam::foco(){
	glPushMatrix();
		
		glRotatef(-90.0,0.0,0.0,1.0);
		glTranslatef(-60.0,0.0,0.0);

		glPushMatrix(); // cono
			glScalef(10.0,10.0,10.0);
			glTranslatef(0.0,-0.5,0.0);
			if ( modo_ajedrez == true){
				cono->draw_ajedrez(modo_vis);
			}
			else{
				cono->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

		glPushMatrix(); // cilindro
			glTranslatef(0.0,-2.0,0.0);
			glScalef(-4.0,-4.0,-4.0);
			if ( modo_ajedrez == true){
				cilindro->draw_ajedrez(modo_vis);
			}
			else{
				cilindro->draw(modo_vis, usar_diferido);
			}
		
		glPopMatrix();

	glPopMatrix();
}


void GrafoParam::brazo(float movimiento_articulacion_1){

	glPushMatrix();
		

		glPushMatrix();
			glTranslatef(0.0,60.0,0.0);
			glRotatef(-90.0,0.0,0.0,1.0);
			glScalef(2.0,30.0,2.0);
			glColor3f(0.756,0.756,0.756);
			if ( modo_ajedrez == true){
				cilindro->draw_ajedrez(modo_vis);
			}
			else{
				cilindro->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0,60.0,0.0);
			glColor3f(0.0,1.0,0.0);
			glScalef(10.0,10.0,10.0);
			glTranslatef(2.0,0.10,0.0);
			if ( modo_ajedrez == true){
				cubo->draw_ajedrez(modo_vis);
			}
			else{
				cubo->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0,60.0,0.0);
			glColor3f(0.0,0.0,0.0);
			glScalef(6.0,4.0,6.0);
			glRotatef(-90,0.0,0.0,1.0);
			if ( modo_ajedrez == true){
				cilindro->draw_ajedrez(modo_vis);
			}
			else{
			cilindro->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.0,0.0,0.0);
			glScalef(2.0,4.0,2.0);
			glTranslatef(-8.0,15.0,0.0);
			if ( modo_ajedrez == true){
				cilindro->draw_ajedrez(modo_vis);
			}
			else{
			cilindro->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

		brazo2( movimiento_articulacion_1);
		
	glPopMatrix();
}

void GrafoParam::brazo2(float movimiento_articulacion_1){

	//brazo del foco
	glPushMatrix();

		//cilindro chico
		glPushMatrix();
			glScalef(1.0,8.0,1.0);
			glTranslatef(-16.0,8.0,0.0);
			glColor3f(0.756,0.756,0.756);
			if ( modo_ajedrez == true){
				cilindro->draw_ajedrez(modo_vis);
			}
			else{
			cilindro->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

		
		//cilindro grande
		glPushMatrix();
			glColor3f(0.756,0.756,0.756);
			glTranslatef(-16.0,8.0,0.0);
			
			glRotatef(movimiento_articulacion_1,0.0,1.0,0.0);
			glTranslatef(-12.5,58.0,0.0);
			glRotatef(-90.0,0.0,0.0,1.0);
			glScalef(1.0,25.0,1.0);
			if ( modo_ajedrez == true){
				cilindro->draw_ajedrez(modo_vis);
			}
			else{
				cilindro->draw(modo_vis, usar_diferido);
			}
		glPopMatrix();

		//foco
		glPushMatrix();

			glColor3f(0.0,0.0,0.0);
			
			glTranslatef(-16.0,8.0,0.0);
			glRotatef(movimiento_articulacion_1,0.0,1.0,0.0);
			glTranslatef(-24.0,-3.0,0.0);
			foco();
		glPopMatrix();

	glPopMatrix();

}


