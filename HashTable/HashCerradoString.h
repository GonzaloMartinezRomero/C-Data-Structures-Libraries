/* 
 * File:   HashCerradoString.h
 * Author: Drebin
 *
 * Created on 26 de noviembre de 2015, 19:18
 */

#ifndef HASHCERRADOSTRING_H
#define	HASHCERRADOSTRING_H
#include <vector>
#include <iostream>
#include <string>
#include "ErrorTablaHash.h"

using namespace std;

enum estadoCasilla{
    //Casilla nunca ocupada
    Libre,
    //Casilla ocupada
    Ocupado,
    //Casilla con dato anteriormente borrado
    Disponible
};


//-------------------------CLASE CASILLA---------------------
template <class T>
class Casilla{
    public:    
        T dato;
        estadoCasilla estado;
        string clave;
        
     
    
         Casilla(){
            estado=Libre;
            clave=" ";
        }
       
        bool insertarDatoCasilla(const T &_dato,const string &_clave);
        void borrarDato();
        estadoCasilla estadoActualCasilla();
        T& devolverDatoCasilla();
        string& devolverClave();

};
template <class T>
bool Casilla<T>::insertarDatoCasilla(const T &_dato,const string &_clave)
{
    if(estado!=Ocupado)
    {
        dato=_dato;
        estado=Ocupado;
        clave=_clave;
        return true;
    }
    else
    {
        return false;
    }
}

/*La funcion de borrar,no consiste en eliminar el dato en sí. Pone el estado de la casilla en 
 disponible para que pueda ser sobreescrita*/
template <class T>
void Casilla<T>::borrarDato(){
  estado=Disponible;
}

template <class T>
estadoCasilla Casilla<T>::estadoActualCasilla(){
    return estado;
}

template <class T>
T& Casilla<T>::devolverDatoCasilla(){
    return dato;
}

template <class T>
string& Casilla<T>::devolverClave(){
    return clave;
}


//------------------------CLASE TABLA HASH-------------------

template <class T>
class HashCerradoString{
private:
    vector<Casilla<T> > vectorCasillas;
    unsigned long int numeroDatos;
    long int numeroPrimo;
        
     
    /*
     * Devuelve el numero primo mas cercano al tamano de la estructura 
     * Algoritmo utilizado: Criba de Eratostenes
     */
    long int generarPrimo();
    /*Funcion de dispersion simple*/
    unsigned long int funcionDispersion(const string &clave);
    /* 
    *  Utiliza la dispersion doble:
    *  h1(x)=x%tam
    *  h2(x)=1+(x%q), q=primo mayor de 1000
    *  h(x)=(h1(x)+i*h2(x))%tam 
    */
    unsigned long int resolucionColisiones(const string &clave,int numColisiones);
    /*Algoritmo djb2*/
    unsigned long int djb2(const string &str);
       
    /*
     * Aumenta el tam de la tabla en un 50%
     */
    void aumentarTamano();
    
    
public:
    HashCerradoString(int _tam){
        
        this->vectorCasillas.resize(_tam);
        this->numeroPrimo=generarPrimo();
        this->numeroDatos=0;            
    }
    /**
     * Constructor por defecto que inicia el tamaño de la tabla a 100
     */
    HashCerradoString(){
        this->vectorCasillas.resize(100);  
        this->numeroPrimo=generarPrimo();
        this->numeroDatos=0;

    }
    /*
     * Constructor por copia
     */
    HashCerradoString(const HashCerradoString &orig){
        this->numeroDatos=orig.numeroDatos;
        this->numeroPrimo=orig.numeroPrimo;
        this->vectorCasillas=orig.vectorCasillas;
    }
    /*
     * Destructor
     */
    ~HashCerradoString(){}
    
    
    
    /*
     * Devuelve true si el dato se ha introducido en la tabla hash
     * Devuelve false si:
     *      Ha habido mas de 10 colisiones en la inserccion
     *      El dato y clave insertados ya están en la tabla
     * 
     */
    bool insertarDato(const T &dato,const string& clave);

    /*
     * Devuelve el dato asociado a la clave 
     * En caso de no encontrarlo lanza excepcion tipo ErrorTablaHash()
     */
    T& buscarDato(const string & clave);
    /*
     * Devuelve el factor de carga de la tabla hash
     */
    double factorCarga();
    /*
     * Devuelve los datos de la tabla
     */
    vector<pair<T,string> > devolverDatosTabla(); 
    /*
     * Devuelve el numero de datos insertados en la tabla
     */
    unsigned long int size();
};

template<class T>
long int HashCerradoString<T>::generarPrimo(){
     /*
     *----Algoritmo: Criba de Eratostenes
     * Guardamos todos los numeros comprendidos entre el 2 y n
     * Comenzando por el 2, se tachan todos sus multiplos
     * Cuando se encuentra el siguiente numero no tachado, se considera primo
     * Despues se tachan todos sus multiplos
     * Termina cuando el cuadrado del mayor numero primo guardado es mayor que n     
     */
    long int n=vectorCasillas.size();
    //Todos los false se consideran primos
    vector<bool> numerosNaturales(n+1,false);
    int mayorPrimo=1;    
    for(long int i=2;i<n;i++){
        if(!numerosNaturales[i]){            
            mayorPrimo=i;
            for(long int j=i;j*i<=n;j++){   
                numerosNaturales[j*i]=true;
            }
        }
       
    }    
    return mayorPrimo;
}

template<class T>
unsigned long int HashCerradoString<T>::size(){
    return numeroDatos;
}

template <class T>
vector<pair<T,string> > HashCerradoString<T>::devolverDatosTabla(){
    
    vector<pair<T,string> > vectorPares;
    pair<T,string> parAux;
    for(int i=0;i<vectorCasillas.size();i++){
        if(vectorCasillas[i].estado==Ocupado){
            parAux=make_pair(vectorCasillas[i].dato,vectorCasillas[i].clave);
            vectorPares.push_back(parAux);
        }
    }
    return vectorPares;
    
}


template<class T>
void HashCerradoString<T>::aumentarTamano(){
    //Hay que volver a redispersionar todos los elementos debido a que cuando cambia
    //el tam, la posicion que genera la clave cambia
    
    this->numeroDatos=0;    
    vector<Casilla<T> > vectorAux=vectorCasillas;
    
    vectorCasillas.clear();
    vectorCasillas.resize(vectorAux.size()+vectorAux.size()*0.5);
    this->numeroPrimo=generarPrimo();
    
    
    for(int i=0;i<vectorAux.size();i++){        
        if(vectorAux[i].estado==Ocupado)
            this->insertarDato(vectorAux[i].dato,vectorAux[i].clave);            
        
    }   
    
}


template<class T>
unsigned long int HashCerradoString<T>::resolucionColisiones(const string& clave, int numColisiones){
    
    unsigned long int h1=funcionDispersion(clave);
    unsigned long int h2=1+(djb2(clave)%numeroPrimo);    
    return (h1 + numColisiones*h2)%vectorCasillas.size();    
    
}


template<class T>
unsigned long int HashCerradoString<T>::djb2(const string& str){
    unsigned long hash = 5381;
    for (auto c : str) {
        hash = (hash << 5) + hash + c; /* hash * 33 + c */
    }    
    return hash;
}

template <class T>
unsigned long int HashCerradoString<T>::funcionDispersion(const string &clave){
    
    return djb2(clave)%vectorCasillas.size();

}

template <class T>
bool HashCerradoString<T>::insertarDato(const T& dato,const string &clave){
   
    //Antes de introducir otro dato, si el factor de carga es superior a 0.7 la tabla crece 50%
    if(this->factorCarga()>=0.7)
    {  
        this->aumentarTamano();     
    }
    
    unsigned long int posicion=funcionDispersion(clave);
  
    int contador=0;
    int numeroColisiones=0;    
    int numMaxColisiones=10;
    
    //Si no se consigue insertar en 10 intentos, se aborta la operacion
    while((!vectorCasillas[posicion].insertarDatoCasilla(dato,clave))&&(contador<numMaxColisiones))
    {
        //Hay que ver si se está metiendo el mismo dato repetido
        if(vectorCasillas[posicion].devolverDatoCasilla()==dato && vectorCasillas[posicion].devolverClave()==clave){          
           return false;
        }
        else
        {           
            numeroColisiones++;
            contador++;
            posicion=resolucionColisiones(clave,numeroColisiones);           
        }
       
    }
     
    if(contador==numMaxColisiones)
    {   
        return false;
    }
    else
    {
        this->numeroDatos++;
        return true;
    }
   
}

template <class T>
T& HashCerradoString<T>::buscarDato(const string &clave){
    
    unsigned long int posicion=funcionDispersion(clave);  
    int numeroIntentos=0;    
    int contador=0;
    int numMaxIntentos=10;
    
    //Lo busco en la tabla hash considerando posibles colisiones
    while((vectorCasillas[posicion].estado!=Libre)&&(vectorCasillas[posicion].devolverClave()!=clave)&&(contador<numMaxIntentos))
    {
        numeroIntentos++;
        contador++;
        posicion=resolucionColisiones(clave,numeroIntentos);
        
    }
     
    //Una vez encontrado, si la clave coincide, devuelvo el dato
    if((vectorCasillas[posicion].estadoActualCasilla()==Ocupado)&&(contador<numMaxIntentos))
    {   
        return vectorCasillas[posicion].devolverDatoCasilla();
    }
    else
    {
        throw ErrorTablaHash("El dato no ha sido encontrado");
    }
}

template<class T>
double HashCerradoString<T>::factorCarga(){      
    return (double)numeroDatos/vectorCasillas.size();        
}




#endif	/* HASHCERRADOSTRING_H */

