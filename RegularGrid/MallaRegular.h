/* 
 * File:   MallaRegular.h
 * Author: Drebin
 *
 * Created on 14 de diciembre de 2015, 12:51
 */

#ifndef MALLAREGULAR_H
#define	MALLAREGULAR_H
#include <list>
#include <vector>
#include <cmath>
#include <iostream>
#include "ErrorMallaRegular.h"
using namespace std;
//----------------------CLASE CASILLA-----------------------
template<class T>
class Casilla{
public:

    list<T> puntos;    
    Casilla():puntos(){ }
    
    void insertar(const T &dato);
    T* buscar(const T &dato);
    bool borrar(const T &dato);
   
};

template <class T>
void Casilla<T>::insertar(const T& dato){   
    puntos.push_back(dato);   
}

template <class T>
T* Casilla<T>::buscar(const T& dato){
    
    typename list<T>::iterator it=puntos.begin();
    while(it!=puntos.end())
    {
        if(*it==dato)
        {
            return &(*it);
        }
        it++;
    }
    return 0;
}

template <class T>
bool Casilla<T>::borrar(const T& dato){
    typename list<T>::iterator it=puntos.begin();
    while(it!=puntos.end())
    {
        if(*it==dato)
        {
            puntos.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

//---------------------------CLASE MALLA REGULAR ---------------
template<class T>
class MallaRegular{
private:
        
    vector<vector<Casilla<T> > > malla;
    int numeroDivisiones;//Numero de casillas que forman la malla
    
    float ratioX;//Proporcion entre la distancia en coordenadas y numero de divisiones en el eje X
    float ratioY;//Proporcion entre la distancia en coordenadas y numero de divisiones en el eje Y
    float xMin,xMax,yMin,yMax;//Posiciones de la ventana de vision
   
    /**
     * Dadas las coordenadas de un punto, devuelve la casilla en la que está 
     * Si las coordenadas no están dentro del mapa devuelve excepcion ErrorMallaRegular
     */
    Casilla<T>* obtenerCasilla(float posX,float posY);
    /**
     * Dadas las coordendas de un punto, devuelve el cuadrante referente a la malla en el que se aloja 
     * Si las coordenadas no están dentro del mapa devuelve excepcion ErrorMallaRegular
     */
    pair<int,int> obtenerPosicionMalla(float posX,float posY);
    
    
public:

    /*Constructor por defecto
    * Numero de divisiones=2; 
    * Inicialmente se genera una malla de 2x2 
    */
    MallaRegular();
    /* Constructor parametrizado  */
    MallaRegular(int _numeroDivisiones,float _xMin,float _xMax,float _yMin,float _yMax);
    /*Constructor copia*/
    MallaRegular(const MallaRegular &orig);
    /*Destructor*/
    ~MallaRegular(){};
    
    /**
     * Inserta un dato en la posicion x,y referente al mapa con el que se esta trabajando
     * En caso de que las coordenadas se salgan de rango, se lanza excepcion ErrorMallaRegular
     */
    void insertar(const T &dato,float x,float y);
    /**
     * Borra el dato situado en la posicion x,y del mapa con el que se esta trabajando 
     * True si el dato ha sido borrado , false si no ha sido borrado
     * En caso de que las coordenadas se salgan de rango, se lanza excepcion ErrorMallaRegular
     */
    bool borrar(const T &dato,float x,float y);
    /*
     * Devuelve un puntero al dato situado en la posicio x,y
     * En caso de que las coordenadas se salgan de rango, se lanza excepcion ErrorMallaRegular
     */
    T* buscar(const T &dato,float x,float y);
    /*
     * Dada el area de busqueda, acotada por x,y max/min, devuelve todos los datos que estan
     * en las casillas por las que pasa dicha restricción
     * 
     */
    list<T> buscarPorRangos(float _xMin,float _yMin,float _xMax,float _yMax);
    /*
     * Inicializa los atributos de la clase
     */
    void inicializarAtributos(int _numeroDivisiones,float _xMin,float _xMax,float _yMin,float _yMax);
    
    

};

template<class T>
MallaRegular<T>::MallaRegular(){
    
    this->numeroDivisiones=2;     
    this->xMin=0;
    this->xMax=2;
    this->yMin=0;
    this->yMax=2;
    this->ratioX=numeroDivisiones/abs(xMin-xMax);
    this->ratioY=numeroDivisiones/abs(yMin-yMax);
    
    //Ahora creo la malla vacia con:             FILAS                  COLUMNAS         
    malla.insert(malla.begin(),numeroDivisiones,vector<Casilla<T> >(numeroDivisiones));    
    
}

template<class T>
MallaRegular<T>::MallaRegular(int _numeroDivisiones,float _xMin,float _xMax,float _yMin,float _yMax){
    
    this->numeroDivisiones=_numeroDivisiones;     
    this->xMin=_xMin;
    this->xMax=_xMax;
    this->yMin=_yMin;
    this->yMax=_yMax;
    this->ratioX=numeroDivisiones/abs(xMin-xMax);
    this->ratioY=numeroDivisiones/abs(yMin-yMax);
    
              
    malla.insert(malla.begin(),numeroDivisiones,vector<Casilla<T> >(numeroDivisiones));    
}

template<class T>
MallaRegular<T>::MallaRegular(const MallaRegular& orig){

    this->numeroDivisiones=orig.numeroDivisiones;
    this->ratioX=orig.ratioX;
    this->ratioY=orig.ratioY;
    this->xMax=orig.xMax;
    this->xMin=orig.xMin;
    this->yMax=orig.yMax;
    this->yMin=orig.yMin;
    malla.clear();
    malla.insert(malla.begin(),numeroDivisiones,vector<Casilla<T> >(numeroDivisiones)); 
    
    for(int i=0;i<numeroDivisiones;i++){
    
        for(int j=0;j<numeroDivisiones;j++){
            malla[i][j]=orig.malla[i][j].puntos;        
        }    
    }
}

template<class T>
void MallaRegular<T>::inicializarAtributos(int _numeroDivisiones, float _xMin, float _xMax, float _yMin, float _yMax){
    
    this->numeroDivisiones=_numeroDivisiones;     
    this->xMin=_xMin;
    this->xMax=_xMax;
    this->yMin=_yMin;
    this->yMax=_yMax;
    this->ratioX=numeroDivisiones/abs(xMin-xMax);
    this->ratioY=numeroDivisiones/abs(yMin-yMax);
  
    malla.clear();
    malla.insert(malla.begin(),numeroDivisiones,vector<Casilla<T> >(numeroDivisiones));    

}



template<class T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(float posX, float posY){

    //Comprobar que las coordenadas no se salen del mapa   
    if(posX>=this->xMin && posX<=this->xMax && posY>=this->yMin && posY<=this->yMax){    
       
        int posMallaX=(int)(abs(posX-xMin)*this->ratioX);
        int posMallaY=(int)(abs(posY-yMin)*this->ratioY);       
        
        if(posMallaX>=malla.size() || posMallaY>=malla[0].size())
            throw ErrorMallaRegular("Posiciones generadas no son correctas");
       
        return &malla[posMallaX][posMallaY];
        
    }
    else
    {
        throw ErrorMallaRegular("Las coordenadas no son correctas");
    }
     
}


template <class T>
void MallaRegular<T>::insertar(const T &dato,float x,float y){
    
    Casilla<T> *casilla=obtenerCasilla(x,y);        
    casilla->insertar(dato);
}

template<class T>
bool MallaRegular<T>::borrar(const T& dato, float x, float y){

    Casilla<T> *casilla=obtenerCasilla(x,y);
    if(casilla->borrar(dato))
        return true;
    else
        return false;
}

template<class T>
T* MallaRegular<T>::buscar(const T &dato,float x, float y){
 
    Casilla<T> *casilla=obtenerCasilla(x,y);    
    T *aux=casilla->buscar(dato);
    if(aux)
        return aux;
    else
        throw ErrorMallaRegular("Dato no existe");
    
}

template<class T>
list<T> MallaRegular<T>::buscarPorRangos(float _xMin, float _yMin, float _xMax, float _yMax){

    pair<int,int> posMin=obtenerPosicionMalla(_xMin,_yMin);
    pair<int,int> posMax=obtenerPosicionMalla(_xMax,_yMax);
  
     
    list<T> objetosMalla;
    typename list<T>::iterator it;
    
    for(int i=posMin.first;i<=posMax.first;i++){
        
        for(int j=posMin.second;j<=posMax.second;j++){
           
            it=malla[i][j].puntos.begin();
            while(it!=malla[i][j].puntos.end()){
                
                objetosMalla.push_back(*it);
                it++;
            }
            
        }        
    }  
    
    return objetosMalla;
}


template <class T>
pair<int,int> MallaRegular<T>::obtenerPosicionMalla(float posX, float posY){

    pair<int,int> posicionMalla;
    
    //Comprobar que las coordenadas no se salen del mapa   
    if(posX>=this->xMin && posX<=this->xMax && posY>=this->yMin && posY<=this->yMax){
        
        int posMallaX=(int)(abs(posX-xMin)*this->ratioX);
        int posMallaY=(int)(abs(posY-yMin)*this->ratioY);        
        
        if(posMallaX>=malla.size() || posMallaY>=malla[0].size())
            throw ErrorMallaRegular("Posiciones generadas no son correctas");        
        
        posicionMalla=make_pair(posMallaX,posMallaY);
        return posicionMalla;
    }
    else
    {
        throw ErrorMallaRegular("Las coordenadas no son correctas");
    }
    
   
}

#endif	/* MALLAREGULAR_H */

