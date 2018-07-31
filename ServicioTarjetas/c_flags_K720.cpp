#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>


#include "ServicioTarjetas/c_flags_K720.h"

using namespace std;



c_flags_K720::c_flags_K720()
{
	cout << "Constructor";
	lectura_com = false;
	escritura_com=false;
	status_com =false;
}

c_flags_K720::~c_flags_K720()
{
	cout << "Destructor";
}


///////////////////////////////////////////////////
//Devoluci�n de los estados de los flags para comprobaciones externas
///////////////////////////////////////////////////

//Lee el estado del flag de lectura del puerto com
bool* c_flags_K720::leer_com()
{
	//cout << lectura_com;
	return &lectura_com; 	
}


//Devuelve el estado del flag de conexi�n del puerto com
bool* c_flags_K720::estado_com()
{
	//cout << status_com;
	return &status_com; 	
}

//Devuelve el estado del flag de conexi�n del puerto com
bool* c_flags_K720::escribir_com()
{
	//cout << escritura_com;
	return &escritura_com; 	
}
//Devuelve el estado del sensor 1: Posición primera desde el apilador
bool* c_flags_K720::sensor1_com()
{
    return &sensor1;
}

//Devuelve el estado del sensor 2: Posición intermedia del carril de tarjetas
bool* c_flags_K720::sensor2_com()
{
    return &sensor2;
}

//Devuelve el estado del sensor 2: Posición más cercana a la boca de salida
bool* c_flags_K720::sensor3_com()
{
    return &sensor3;
}

///////////////////////////////////////////////////
//Modificaci�n de estados de los estados de los flags para ejecuciones externas
///////////////////////////////////////////////////

//Cambia el estado del flag de lectura del puerto com
void c_flags_K720::flag_lectura_com(bool flag)
{
	lectura_com = flag;
	//cout << lectura_com;
}
//Cambia el estado del flag de status del puerto com		
void c_flags_K720::flag_status_com(bool flag)
{
	status_com = flag;
	//cout << status_com;
}
		
//Cambia el estado del flag de escritura del puerto com		
void c_flags_K720::flag_escritura_com(bool flag)
{
	escritura_com = flag;
	//cout << escritura_com;
}

//Cambia el estado del flag de sincronismo del sensor 1
void c_flags_K720::flag_sensor1_com(bool flag)
{
    sensor1 = flag;
}

//Cambia el estado del flag de sincronismo del sensor 2
void c_flags_K720::flag_sensor2_com(bool flag)
{
    sensor2 = flag;
}

//Cambia el estado del flag de sincronismo del sensor 3
void c_flags_K720::flag_sensor3_com(bool flag)
{
    sensor3 = flag;
}
		

