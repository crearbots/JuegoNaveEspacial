#include <stdio.h> //libreria para imprimir caracteres especiales del codigo ASCII
#include <windows.h> //libreria para utilizar varias funciones de videojuegos
#include <conio.h> //libreria para detectar las teclas que se oprimen
#include <stdlib.h> //libreria para utilizar la funcion rand()
#include <list> //libreria para utilizar listas

//Definimos las siguientes palabras para hacer referencia a las flechas del teclado basadas en el codigo ASCII
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

using namespace std;

void gotoxy (int x , int y) //Funcion que nos perite tener control sobre el cursor segun las cordenadas que ingresemos
{
	HANDLE hCon; //Declaramos el handle
	hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Recuperamos el identificador de la consola y definimos que tipo de control queremos tener sobre ella
	COORD dwPos; //Estructura de datos para coordenadas
	dwPos.X = x; //Definiendo coordenadas en X
	dwPos.Y = y; //Definiendo coordenadas en Y
	SetConsoleCursorPosition(hCon,dwPos); //Funcion para darle una posicion especifica al cursor
}

void OcultarCursor() //Funcion creada con el fin de ocultar el cursor
{
	HANDLE hCon; //Declaramos el handle
	hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Recuperamos el identificador de la consola y definimos que tipo de control queremos tener sobre ella
	CONSOLE_CURSOR_INFO cci; //Estructura para controlar la apariencia del cursor
	cci.dwSize = 1; //Atributo para definir el tamaño del cursor
	cci.bVisible = FALSE; //Atributo para mostrar u ocultar el cursor 
	SetConsoleCursorInfo(hCon,&cci); //Funcion para controlar las caracteristicas de apariencia del cursor
}

void pintar_limite() //Funcion pora graficar los limites del juego utilizando caracteres del codigo ASCII
{
	for(int i=2; i<77; i++) //Imprimimos las filas del limite
	{
		gotoxy(i,3); printf("%c",205); 
		gotoxy(i,33); printf("%c",205);
	}
	
	for(int i=3; i<33; i++) //Imprimimos las columnas del limite
	{
		gotoxy(2,i); printf("%c",186);
		gotoxy(77,i); printf("%c",186);
	}
	
	//Imprimimos las esquinas del limite
	gotoxy(2,3); printf("%c",201);  
	gotoxy(2,33); printf("%c",200);
	gotoxy(77,3); printf("%c",187);
	gotoxy(77,33); printf("%c",188);
}

void instrucciones()
{
	//Pintar instrucciones
	printf("\t\tBIENVENIDO AL JUEGO DE NAVES\n");
	printf("Utilice las flechas para moverse\tUtilice la tecla 'p' para disparar\n");
	printf("\t\t<^>\t\t\t\tp\n");
	printf("\nPresione cualquier tecla para continuar :) "); getch();
	
	//Borrar instrucciones
	gotoxy(0,0);
	printf("                                                                      \n");
	printf("                                                                           \n");
	printf("                                                                      \n");
	printf("                                                                      \n");
	printf("                                                                      \n");
}

class NAVE //En este momento creamos la clase NAVE para despues determinar el objeto
{
	int x,y; //Atributos de la clase los cuales nos definen la coordenadas de la nave
	int corazones; //Atributo que nos define la salud de la nave
	int vida; //Atributo que nos define la vida de la nave

	public: //Los elementos puesto de aqui en adelante puede ser modificados o llamados desde cualquier otra funcion
		NAVE(int _x,int _y,int _corazones,int _vida) : x(_x),y(_y),corazones(_corazones),vida(_vida) {} //Constructor de la clase el cual se encarga de resivir los argumentos que en este caso son las coordenadas, el numero de corazones (salud) y la vida de la nave
		
		int X() { return x; } //Como las coordenada X es privada utilizamos esta funcion para retornar su valor y asi poderlo utilizar en el metodo choque de la clase AST
		int Y() { return y; } //Como las coordenada Y es privada utilizamos esta funcion para retornar su valor y asi poderlo utilizar en el metodo choque de la clase AST
		int VID() { return vida; } //Retornamos la vida de la nave para mas adelante establecer en que momento se acaba el juego
		void COR() { corazones --; } //Definimos esta funcion para poder modificar el numero de corazones desde el metodo choque de la clase AST
		
		void pintar(); //Metodo
		void borrar(); //Metodo
		void mover(); //Metodo
		void pintar_corazones(); //Metodo
		void morir(); //Metodo
};

void NAVE::pintar() //Lo que hace esta funcion es pintar la nave en base a caracteres del codigo ASCII
{
	gotoxy(x,y);   printf("  %c",245);
	gotoxy(x,y+1); printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2); printf("%c%c %c%c",201,190,190,187);
}

void NAVE::borrar() //Esta funcion simplemente se encarga de borrar la nave 
{
	gotoxy(x,y);     printf("      ");
	gotoxy(x,y+1);   printf("      ");
	gotoxy(x,y+2);   printf("      ");
}

void NAVE::mover() //Funcion que nos permite mover la nave
{
	if(kbhit()) //Este bloque de codigo se activa cuando oprimimos una tecla
	{
		borrar(); //Con el llamado de la funcion quitamos la nave
		char letra = getch(); //Guardamos la letra presionada en la variable LETRA
		if(letra == IZQUIERDA & x > 3) x--; //Al oprimir la flecha izquierda el valor de x disminuye
		if(letra == DERECHA & (x+5) < 76) x++; //Al oprimir la flecha derecha el valor de x aumenta
		if(letra == ARRIBA & y > 4) y--; //Al oprimir la flecha arriba el valor de y disminuyeaa
		if(letra == ABAJO & (y+3) < 33) y++; //Al oprimir la flecha abajo el valor de y aumenta
		pintar(); //Una vez movido el cursor pintamos de nuevo la nave
		pintar_corazones(); //Cada vez que se mueva la nave la salud se actualizara en pantalla		
	}	
}

void NAVE::pintar_corazones() //Con esta funcion controlamos la vitalidad de la nave imprimiendo en pantalla su salud y vida
{
	gotoxy(64,2); printf("Salud");
	gotoxy(70,2); printf("   "); //Imprimimos el espacio para los corazones
	
	for(int i=0; i<corazones; i++)
	{
		gotoxy(70+i,2); printf("%c",208); //Imprimimos los corazones
	}
	
	gotoxy(50,2); printf("VIDAS %d",vida); //Imprimimos la vida
}

void NAVE::morir() //Con esta funcion simulamos la explosion de la nave y disminuimos la vida de la misma 
{
	if(corazones==0) //Este bloque de codigo se activa cuando la nave se queda sin salud
	{
		//Inicio de la explosion
		borrar();
		gotoxy(x,y);   printf("  **  ");
		gotoxy(x,y+1); printf(" **** ");
		gotoxy(x,y+2); printf("  **  ");
		Sleep(200);
		
		borrar();
		gotoxy(x,y);   printf("* ** *");
		gotoxy(x,y+1); printf(" **** ");
		gotoxy(x,y+2); printf("* ** *");
		Sleep(200);
		
		borrar();
		gotoxy(x,y);   printf("* ** *");
		gotoxy(x,y+1); printf("* ** *");
		gotoxy(x,y+2); printf("* ** *");
		Sleep(200);
		
		borrar();
		gotoxy(x,y);   printf("* ** *");
		gotoxy(x,y+1); printf("*    *");
		gotoxy(x,y+2); printf("* ** *");
		Sleep(200);
		//Fin de la explosion
		
		borrar(); //Borramos la explosion
		corazones=3; //Reseteamos la salud de la nave para que vuelva a la normalidad
		vida--; //La nave pierde una vida
		pintar_corazones(); //Volvemos a imprimir la salud de la nave
		pintar(); //pintamos nuestra nave 
	}
}

class AST //Creamos una clase AST para despues crear varios asteroides
{
	int x,y; //Atributos los cuales nos definen las coordenadas de los asteroides
	
	public: //Los elementos puesto de aqui en adelante puede ser modificados o llamados desde cualquier otra funcion
		AST(int _x,int _y) : x(_x),y(_y) {} //Constructor de la clase el cual se encarga de resivir los argumentos que en este caso son las coordenadas
		
		int X() { return x; } //Como las coordenada X es privada utilizamos esta funcion para retornar su valor y asi poderlo utilizar en la funcion principal
		int Y() { return y; } //Como las coordenada Y es privada utilizamos esta funcion para retornar su valor y asi poderlo utilizar en la funcion principal
		void pintar(); //Metodo
		void mover(); //Metodo
		void choque(class NAVE &N); //Para este metodo es necesario resivir el objeto porque se necesita modificar valores de la nave, por eso se envia el argumento por referencia
};

void AST::pintar() //Con esta funcion pintamos el asteroide
{
	gotoxy(x,y); printf("%c",184);
}

void AST::mover() //Esta funcion permite visualizar como los asteroides descienden
{
	gotoxy(x,y); printf(" "); //Borramos en la coordenada indicada
	y++; //La coorderna Y aumenta para que el asteroide desceinda
	
	if(y>32) //Si el asteroide llega al limite inferior de la pantalla este bloque de codigo se ejecuta
	{
		x = (rand() % 72) + 4; //Generamos un numero aleatorio y lo guardamos en la cordenada X
		y = 4; //Restablecemos la coordenada Y en 4 para que el asteroide vuelva a aparecer en la parte superior del juego
	}
	
	pintar(); //Pintamos el asteroide en la nueva coordenada
}

void AST::choque(class NAVE &N) //En esta funcion definiremos lo que pasa cuando un asteroide choca con la nave
{
	if( x >= N.X() and x <= N.X()+4 and y >= N.Y() and y <= N.Y()+2 ) //Este bloque de codigo se activa cuando las coordenadas del asteroide son las mismas que de la nave
	{
		N.COR(); //La nave pierde un corazon
		N.borrar(); //Borramos todo 
		N.pintar(); //Volvemos a pintar la nave
		N.pintar_corazones(); //Actualizamos el numero de corazones en pantalla
		
		//Con el choque el asteriode vuelve a generarse desde la parte de arriba
		x = (rand() % 72) + 4; //Generamos un numero aleatorio y lo guardamos en la cordenada X
		y = 4; //Restablecemos la coordenada Y en 4 para que el asteroide vuelva a aparecer en la parte superior del juego
	}
}

class BALA //Creamos la clase BALA para definir los proyectiles de la nave 
{
	int x,y; //Atributos los cuales nos definen las coordenadas de los proyectiles
	
	public:
		BALA(int _x, int _y): x(_x), y(_y) {} //Constructor de la clase el cual se encarga de resivir los argumentos que en este caso son las coordenadas
		
		int X() { return x; } //Como las coordenada X es privada utilizamos esta funcion para retornar su valor y asi poderlo utilizar en la funcion principal
		int Y() { return y; } //Como las coordenada Y es privada utilizamos esta funcion para retornar su valor y asi poderlo utilizar en la funcion principal
		void mover(); //Metodo
		bool fuera(); //Metodo
};

void BALA::mover() //En esta funcion creamos el movimiento de los proyectiles
{
	gotoxy(x,y); printf(" "); //Borramos en la coordenada indicada
	if(y>3) y--; //Indicamos que el proyectil debe ir hacia la parte superior del juego siempre y cuando su coordenada en Y no sea mayor que la del limite superior 
	gotoxy(x,y); printf("$"); //Impresion del proyectil
}

bool BALA::fuera() //Esta funcion nos permite verificar el momento en el cual el proyectil se encuentra cerca del limite superior
{
	if( y == 4 ) 
		return true;
	else
		return false;
}

int main()
{
	instrucciones(); //Mostramos las instrucciones en pantalla
	OcultarCursor(); //Llamamos la funcion para que la linea del cursor desaparezca 
	pintar_limite(); //LLamamos la funcion para pintar el limite del juego
	
	NAVE platillo(36,30,3,3); //Creamos el objeto llamado "platillo" y definimos sus coordenadas de aparicion, la cantidad de salud y el numero de vidas 
	platillo.pintar(); //llamamos la funcion pintar del objeto platillo para que la nave aparezca en pantalla 
	platillo.pintar_corazones(); //llamamos la funcion pintar_corazones del objeto platillo para mostrar la salud de la nave apenas empiece el juego
	
	list<AST*> A; //Creamos una lista que tendra como elemento los asteroides
	list<AST*>::iterator itA; //Creamos un iterador para poder recorrer toda la lista mas adelante
	
	for(int i=0; i<5; i++) //Con este ciclo podemos crear el numero de asteriodes que nosotros queramos
		A.push_back( new AST ( (rand() % 72) + 4 , (rand() % 2) + 4 ) ); //Creamos un asteriode dentro de la lista con coordenadas aleatorias
		
	list<BALA*> B; //Creamos una lista que tendra como elemento las balas de la nave
	list<BALA*>::iterator it; //Creamos un iterador para poder recorrer toda la lista mas adelante  
			
	bool game_over = false; //Declaramos una variable boleana para mantener el ciclo en constante funcionamiento
	int puntos = 0; //Declramos el contador de los puntos
	while(!game_over) //El ciclo solo se detendra cuando game_over sea false
	{
		gotoxy(4,2); printf("Puntos %d", puntos); //Imprimimos los puntos en pantalla
		
		if(kbhit()) //Este bloque de codigo se activa cuando oprimimos una tecla
		{
			char letra = getch(); //Guardamos la letra presionada en la variable LETRA
			if(letra == 'p') B.push_back( new BALA ( platillo.X()+2 , platillo.Y()-1 ) ); //AL oprimir la tecla 'p' se crea una bala dentro de la lista
		}
		
		for( it = B.begin(); it != B.end(); it++ ) //Recorremos toda la lista con ayuda del iterador 
		{
			(*it) -> mover(); //Como el iterador es la misma bala llamamos a su metodo mover() para ver la animacion de la bala
			
			if( (*it)->fuera() ) //Este bloque de codigo se activa cuando la bala llega a la parte superior del limite 
			{
				gotoxy( (*it)->X(), (*it)->Y() ); printf(" "); //La bala se borra cuando llega a la parte superior 
				delete(*it); //Eliminamos el elemento de la lista, en otras palabras eliminamos el valor del iterador 
				it = B.erase(it); //Ahora indicamos que el iterador debe tomar el valor del segundo elemento que este en la lista
			}
		}
	
		for( itA = A.begin(); itA != A.end(); itA ++ ) //Recorremos toda la lista con ayuda del iterador 
		{
			(*itA) -> mover(); //Como el iterador es la misma clase AST llamamos a su metodo mover() para ver la animacion de cada asterioide caer
			(*itA) -> choque(platillo); //Como el iterador es la misma clase AST llamamos a su metodo choque() simular el choque de cada asteroide con la nave
		}
		
		for( itA = A.begin(); itA != A.end(); itA ++ ) //Recorremos cada asteroide
		{
			for( it = B.begin(); it != B.end(); it ++ ) //Recorremos cada bala
			{
				if( (*itA)->X() == (*it)->X() and ( (*itA)->Y()+1 == (*it)->Y() or (*itA)->Y() == (*it)->Y() ) ) //Este bloque de codigo se activa cuando hay choque
				{
					gotoxy( (*it)->X(), (*it)->Y() ); printf(" "); //La bala se borra cuando choca con el asteriode 
					delete(*it); //Eliminamos el elemento de la lista, en otras palabras eliminamos el valor del iterador 
					it = B.erase(it); //Ahora indicamos que el iterador debe tomar el valor del segundo elemento que este en la lista
					
					A.push_back( new AST ( (rand() % 72) + 4 , (rand() % 2) + 4 ) ); //Creamos un asteriode dentro de la lista con coordenadas aleatorias
					gotoxy( (*itA)->X(), (*itA)->Y() ); printf(" "); //El asteroide se borra cuando choca con la bala 
					delete(*itA); //Eliminamos el elemento de la lista, en otras palabras eliminamos el valor del iterador 
					itA = A.erase(itA); //Ahora indicamos que el iterador debe tomar el valor del segundo elemento que este en la lista
					
					puntos += 15; //Cada asteroide eliminado vale 15 puntos
				}
			}
		}
		
		platillo.mover(); //llamamos la funcion mover del objeto platillo para que la nave se mueva
		platillo.morir(); //llamamos la funcion morir del objeto platillo para ver la explosion de la nave cuando los corazones son 0
		if( platillo.VID() == 0 ) game_over = true; 
		Sleep(30); //Se detiene la ejecucion del programa para no saturar el procesador
	}
		
	return 0;
}
