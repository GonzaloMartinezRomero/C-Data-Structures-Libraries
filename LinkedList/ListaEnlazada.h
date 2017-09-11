/* 
 * File:   ListaEnlazada.h
 * Author: Drebin
 *
 * Created on 30 de septiembre de 2015, 16:09
 */

#ifndef LISTAENLAZADA_H
#define	LISTAENLAZADA_H
#include <iostream>
using namespace std;
//----------------------    CLASE NODO    ----------------------
template <class T>
class Nodo{
    public:
        T dato;
        Nodo<T> *sig;
        
        Nodo(T _dato,Nodo<T> *_sig)
        {
            this->dato=_dato;
            this->sig=_sig;
        }
};

 
template <typename T>
class ListaEnlazada{
private:
    
    Nodo<T> *cabecera,*cola;
    T dato;
    unsigned int tam;
    
    
public:
        
    
    ListaEnlazada();//Constructor por defecto
   
    ListaEnlazada(const ListaEnlazada &orig);//Constructor copia
    
    ~ListaEnlazada();//Destructor
    
    //Clase Iterador
    class Iterador{
    public:          
        Nodo<T> *nodo;        
        
        Iterador(){
            nodo=0;
        }
        
        Iterador(Nodo<T> *_nodo){        
            this->nodo=_nodo;         
        }
        
        //Si el iterador apunta al final, devuelve true
        bool fin(){        
            if(nodo==0)
                return true;       
            else
                return false;           
        }
        
        //Avanza a la siguiente posicion 
        void siguiente(){        
            nodo=nodo->sig;
        }
        
        //Devuelve el dato al que apunta
        T &getDato(){
            return nodo->dato;
        }
    };
    
    //Devuelve un iterador apuntando a la cabecera
    Iterador begin(){
        return Iterador(cabecera);
    }
    
    //Operador =
    ListaEnlazada<T>& operator=(const ListaEnlazada &l);
    
    //Inserta un dato por el principio de la lista
    void insertarInicio(const T &dato);
    
    //Inserta un dato por el final de la lista   
    void insertarFinal(const T &dato);
    
    //Inserta un dato donde apunta el iterador, dejando a la derecha el dato apuntado       
    void insertarDcha(const T &dato,const Iterador &it);
    
    //Inserta un dato donde apunta el iterador, dejando a la izquierda el dato apuntado
    void insertarIzqda(const T &dato,const Iterador &it);
    
    //Borra el primer dato de la lista
    void borrarInicio();
    
    //Borra el ultimo dato de la lista
    void borrarFinal();

    //Borra el dato al que apunta el iterador
    void borrar(const Iterador &it);

    //Devuelve el dato T situado en la posicion n
    //Si la posicion no es valida, lanza una excepcion tipo bad_alloc()
    T& leer(unsigned n);
    
    //Devuelve el ultimo dato de la lista
    T& leerUltimaPos(){        
        return cola->dato;        
    }
    
    //Devuelve el primer dato de la lista
    T& leerPrimeraPos(){        
        return cabecera->dato;        
    }
    
    //Devuelve el numero de elementos de la lista
    unsigned size(){
        return tam;
    }
    
    //Devuelve el primer elemento y lo elimina
    T pop_front();
    
    //Devuelve el ultimo elemento y lo elimina
    T pop_back();
    
    //Devuelve true si la lista esta vacia
    bool isEmpty();
   
};


template <class T>
ListaEnlazada<T>::ListaEnlazada(){
    cabecera=0;
    cola=0;
    tam=0;
}

template <class T>
ListaEnlazada<T>::ListaEnlazada(const ListaEnlazada& orig){
   
    cabecera=new Nodo<T>(orig.cabecera->dato,0);  
    tam=orig.tam;
      
    Nodo<T> *auxOrig;//Indice para el vector copia
    Nodo<T> *aux; //Indice para el vector propio
    Nodo<T> *nuevo; //Reserva las nuevas zonas de memoria
    
    if(orig.cabecera!=orig.cola){
       
        cola=new Nodo<T>(orig.cola->dato,0);
        auxOrig=orig.cabecera->sig;
        aux=cabecera;
        while(auxOrig!=orig.cola){
            nuevo=new Nodo<T>(auxOrig->dato,0);
            aux->sig=nuevo;
            auxOrig=auxOrig->sig;
            aux=aux->sig;
        }
        aux->sig=cola;        
    }
    else
    {
        cola=cabecera;
    }
    
}

template <class T>
ListaEnlazada<T>::~ListaEnlazada(){
    
    Nodo<T> *aux=0;
    if(cabecera!=cola){
        while(cabecera->sig!=cola){
            aux=cabecera;
            cabecera=cabecera->sig;
            delete aux;
        }
        delete cabecera;
    }  
    delete cola;
}

template <class T>
void ListaEnlazada<T>::insertarInicio(const T &dato){
    Nodo<T> *nuevo=0;
    tam+=1;           
    //En caso de que la lista este vacia
    if(cabecera==0)
    {   nuevo=new Nodo<T>(dato,0);
        cola=nuevo;               
    }
    else
    {
        nuevo=new Nodo<T>(dato,cabecera);
    }       
    cabecera=nuevo;     
}

template <class T>
void ListaEnlazada<T>::insertarFinal(const T &dato){
    Nodo<T> *nuevo=new Nodo<T>(dato,0);        
    tam+=1;
    
    if(cabecera==0)
    {
        cabecera=nuevo;
    }
    else
    {
        cola->sig=nuevo;                    
    }
    
    cola=nuevo;
}

template <class T>
void ListaEnlazada<T>::insertarDcha(const T &dato,const Iterador &it){    
   
    
    Nodo<T> *n=&(*it);
    
    
    
    Nodo<T> *nuevo=0;    
    if(cabecera==0){
        this->insertarFinal(dato);
    }
    else
    {
        if(it.nodo==cola){
            this->insertarFinal(dato);
        }
        else{
            this->tam+=1;
            nuevo=new Nodo<T>(dato,it.nodo->sig);
            it.nodo->sig=nuevo;
        }
    }
    
}

template <class T>
void ListaEnlazada<T>::insertarIzqda(const T &dato,const Iterador &it){
    
    Nodo<T> *aux=cabecera;
    Nodo<T> *nuevo=0;
    
    if(cabecera==0)
    {
        this->insertarInicio(dato);
    }
    else
    {
        if(it.nodo==cabecera)
        {
            this->insertarInicio(dato);
        }
        else
        {
            this->tam+=1;
            while(aux->sig!=it.nodo){
                aux=aux->sig;
            }
            nuevo=new Nodo<T>(dato,it.nodo);
            aux->sig=nuevo;
        }
    }
    
    
    
}


template <class T>
void ListaEnlazada<T>::borrarInicio(){
    Nodo<T> *aux=cabecera;
    
    //Primero se comprueba que hay algo en la lista
    if(cabecera!=0){
        
        tam-=1;
        cabecera=cabecera->sig;
        delete aux;

        //En caso de haber borrado el ultimo nodo,cola apunta a 0 porque no hay siguiente
        if(cabecera==0)        
            cola=0;            
    }
}

template <class T>
void ListaEnlazada<T>::borrarFinal(){
    Nodo<T> *aux=0;
    //Primero se comprueba que la lista tiene elementos
    if(cabecera!=0)
    {        
        tam-=1;
        aux=cabecera;
        //En caso de haber mas de 1 elemento
        if(cabecera!=cola)
        {           
            while(aux->sig!=cola)
            {
                aux=aux->sig;
            }        
            delete cola;
            aux->sig=0;
            cola=aux;
        }
        else//En caso de borrar el ultimo elemento
        {
            delete aux;
            cabecera=cola=0;//------------------------------->>>>>POR QUE SI PONGO delete cabecera; cola=0 DA ERROR??
        }
         
    }
     
}

template <class T>
void ListaEnlazada<T>::borrar(const Iterador &it){
    Nodo<T> *aux=0;
    
    //Primero se comprueba que la lista tiene elementos
    if(cabecera!=0){
        
        
        if(it.nodo==cabecera){//Caso de borrar la cabecera
            this->borrarInicio();
        }
        else
        {
            if(it.nodo==cola)//Caso de borrar la cola
            {
                this->borrarFinal();
            }
            else
            {
                tam-=1;
            
                if(cabecera==cola){//Caso de que solo quede 1 elemento
                    aux=cabecera;
                    delete aux;
                    cabecera=cola=0;
                }
                else
                {
                    aux=cabecera;
                    while(aux->sig!=it.nodo)
                    {
                        aux=aux->sig;
                    }
                    aux->sig=it.nodo->sig;
                    delete it.nodo;
                }
            }
        }
                
    }  
}

template<class T>
T &ListaEnlazada<T>::leer(unsigned n){
    
    Nodo<T> *nodo=cabecera;
    int cont=0;    
     
    if(n>=0 && n<tam){
        
        while(cont!=n){
            
            nodo=nodo->sig;
            cont++;            
        }
        return nodo->dato;
    }
    else
    {
        throw bad_alloc();
    }
     
}

template <class T>
ListaEnlazada<T>& ListaEnlazada<T>::operator=(const ListaEnlazada& l){
     
    if(this!=&l){
        //-----------------------Realizar el borrado--------------------
        Nodo<T> *aux=0;
        if(cabecera!=cola){
            while(cabecera->sig!=cola){
                aux=cabecera;
                cabecera=cabecera->sig;
                delete aux;
            }
            delete cabecera;
        }  
        delete cola;
        //-----------------------Realizar la copia-------------------------
        
        cabecera=new Nodo<T>(l.cabecera->dato,0);  
        tam=l.tam;

        Nodo<T> *auxOrig;//Indice para el vector copia    
        Nodo<T> *nuevo; //Reserva las nuevas zonas de memoria

        if(l.cabecera!=l.cola){

            cola=new Nodo<T>(l.cola->dato,0);
            auxOrig=l.cabecera->sig;
            aux=cabecera;
            while(auxOrig!=l.cola){
                nuevo=new Nodo<T>(auxOrig->dato,0);
                aux->sig=nuevo;
                auxOrig=auxOrig->sig;
                aux=aux->sig;
            }
            aux->sig=cola;        
        }
        else
        {
            cola=cabecera;
        }
        
    }
    return *this;
}

template<class T>
T ListaEnlazada<T>::pop_front(){
    T dato=cabecera->dato;
    this->borrarInicio();
    return dato;
}

template<class T>
T ListaEnlazada<T>::pop_back(){
    T dato=cola->dato;
    this->borrarFinal();
    return dato;
}


template<class T>
bool ListaEnlazada<T>::isEmpty(){
    if(cabecera==0)
        return true;
    else
        return false;
}

#endif	/* LISTAENLAZADA_H */

  