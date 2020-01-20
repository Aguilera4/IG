//**************************************************************************
// Practica 2
//
// SERGIO AGUILERA RAMÍREZ  Grupo: A3
//
//**************************************************************************
#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "cubo.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 0.1;
    Back_plane        = 2000.0;
    Observer_distance = 20.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    cubo = new Cubo();//inicializo el cubo
    tetra = new tetrahedron();//inicializo el tetrahedro
    big_dodge = new ObjPLY("plys/big_dodge.ply");
    ant = new ObjPLY("plys/ant.ply");
    beethoven = new ObjPLY("plys/beethoven.ply");
    objrevolucion = new ObjRevolucion("plys/peon.ply");
    esfe = new Esfera(20,20,0.5);
    cono = new Cono(20,20,0.5,0.5);
    cilindro = new Cilindro(20,20,0.5,0.75);
    modelo_jerar = new ObjJerarquico();
    num_objetos = 10; // se usa al pulsar la tecla 'O' (rotar objeto actual)
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
	redimensionar(UI_window_width,UI_window_height);
}

// ************************************s**************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   glColor3f(0,0,1);
   glPolygonMode(GL_FRONT_AND_BACK, modo2);



   switch( objeto_actual )
   {

   		//dibuja el cubo segun los modos elegidos
    	case 0:
        	if ( cubo != nullptr && !ajedrez ) cubo->draw(modo,modo_de_dibujo);
        	else if ( cubo != nullptr) cubo->draw_ajedrez(modo);
        	break;

      	//dibuja el tetrahedro segun los modos elegidos
      	case 1:
        	if ( tetra != nullptr && !ajedrez ) tetra->draw(modo,modo_de_dibujo);
        	else if (tetra != nullptr) tetra->draw_ajedrez(modo);
        	break;

        // big_dodge
    	case 2:
        	if ( big_dodge != nullptr && !ajedrez ) big_dodge->draw(modo,modo_de_dibujo);
        	else if (big_dodge != nullptr) big_dodge->draw_ajedrez(modo);
        	break;

        // ant	
      	case 3:
        	if ( ant != nullptr && !ajedrez ) ant->draw(modo,modo_de_dibujo);
        	else if (ant != nullptr) ant->draw_ajedrez(modo);
        	break;

        // beethoven
      	case 4:
        	if (  beethoven!= nullptr && !ajedrez ) beethoven->draw(modo,modo_de_dibujo);
        	else if (beethoven != nullptr) beethoven->draw_ajedrez(modo);
        	break;

        // objRevolucion	
      	case 5:
        	if ( objrevolucion != nullptr && !ajedrez ) objrevolucion->draw(modo,modo_de_dibujo);
        	else if (objrevolucion != nullptr) objrevolucion->draw_ajedrez(modo);
        	break;

        // esfera
      	case 6:
        	if (esfe != nullptr && !ajedrez ) esfe->draw(modo,modo_de_dibujo);
        	else if (esfe != nullptr) esfe->draw_ajedrez(modo);
        	break;

        // cono
      	case 7:
        	if ( cono != nullptr && !ajedrez ) cono->draw(modo,modo_de_dibujo);
        	else if (cono != nullptr) cono->draw_ajedrez(modo);
        	break;

        // cilindro
      	case 8:
        	if ( cilindro != nullptr && !ajedrez ) cilindro->draw(modo,modo_de_dibujo);
        	else if (cilindro != nullptr) cilindro->draw_ajedrez(modo);
        	break;

        //modelo_jerarquico
      	case 9:
      		modo_de_dibujo = 1;
        	if ( modelo_jerar != nullptr) modelo_jerar->draw(modo,modo_de_dibujo, ajedrez);
        	break;

      	default:
        	cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         	break ;
   	}
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
  glEnable(GL_CULL_FACE);
	change_observer();
  ejes.draw();
	dibujar_objeto_actual();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   ajedrez = false;

   switch( toupper(tecla) )
   {
      	case 'I': //dibuja en modo puntos
        	modo = GL_POINTS;
        	modo2 = GL_POINT;
        	break;

      	case 'L': //dibuja en modo lineas
        	modo = GL_TRIANGLES;
        	modo2 = GL_LINE;
        	break;

      	case 'T': //dibuja en modo triangulos(relleno)
        	modo = GL_TRIANGLES;
        	modo2 = GL_FILL;
        	break;

      	case 'C': //dibuja el modo ajedrez en modo inmediato por defecto
        	modo = GL_TRIANGLES;
        	modo2 = GL_FILL;
        	ajedrez = true;
        	break;

      	case 'V': //cambia de modo de dibujo entre inmediato y diferido
        	modo_de_dibujo = (modo_de_dibujo+1) % 2 ;
        	if (modo_de_dibujo==0) cout << "Modo de dibujo inmediato"<< endl;
        	else cout << "Modo de dibujo diferido"<< endl;
        	break;

        case 'Q' : // salir
        	return true ;
        	break ;

        case 'O' :// activar siguiente objeto
        	objeto_actual = (objeto_actual+1) % num_objetos ;
        	cout << "objeto actual == " << objeto_actual << endl ;
        	break ;

        case 'A': //inicia las animaciones
        	conmutarAnimaciones();
        	break;

        case 'P': // siguiente grado de libertad
        	modelo_jerar->siguienteParametro();
        	break;

        case 'Z': // incrementa movimiento
        	modelo_jerar->incrementaParamAct();
        	break;

        case 'z': // decrementa movimiento
        	modelo_jerar->decrementaParamAct();
        	break;

        case '>': // acelera
        	modelo_jerar->acelerar();
        	break;

        case '<': // decelera
        	modelo_jerar->decelerar();
        	break;
   }

   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wy = 0.84*Front_plane ;
   const float wx=ratio_xy*wy;
   glFrustum( -wx, +wx,-wy,+wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth;
   Height = newHeight;
   change_projection( float(Height)/float(Width) );
   glViewport( 0, 0,Width,Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
   glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}


void Escena::mgeDesocupado(){
	modelo_jerar->actualizarEstado();
	glutPostRedisplay();
}

void Escena::conmutarAnimaciones(){

	 if ( objeto_actual == 9 ){
	 	animaciones_activadas = !animaciones_activadas;
	 }

	 if ( animaciones_activadas == true ){
	 	modelo_jerar->inicioAnimaciones();
	 	glutIdleFunc(funcion_desocupado);
	 }
	 else{
	 	glutIdleFunc(nullptr);
	 }

}
