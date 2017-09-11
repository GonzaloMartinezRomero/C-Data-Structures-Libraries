/* 
 * File:   AVL.h
 * Author: Drebin
 *
 * Created on 28 de octubre de 2015, 17:28
 */

#ifndef AVL_H
#define	AVL_H
#include <string>
using namespace std;
template<class T>
class Nodo{
public:
    T dato;
    Nodo *izq,*der;
    char bal;
    Nodo(const T &_dato){
        dato=_dato;
        izq=0;
        der=0;
        bal=0;
    }
              
};

template<class T>
class AVL{
private:
    Nodo<T> *raiz;
    int inserta(Nodo<T>* &c,const T &dato);
    void rotDerecha(Nodo<T>* &p);
    void rotIzquierda(Nodo<T>* &p);
    Nodo<T> *borraMin(Nodo<T>* &p);
    Nodo<T> *buscarDato(Nodo<T> *nodo,const  T &dato);
    void borrarDato(Nodo<T>* &nodo,const T &dato,bool &encontrado);
    
    /*Elimina el arbol en postorden*/
    void destructor(Nodo<T> *actual);
    /*Realiza una copia de orig al actual*/
    void copiarArbol(Nodo<T>* &actual,Nodo<T> *orig);
   
        
public:
            
    /*
     Constructor por defecto
     */
    AVL(){ raiz=0; };
    
    /*
     Constructor copia
     */
    AVL(const AVL &orig);
    
    /*
     Destructor
     */
    ~AVL();
    
    /**
     * Inserta un dato en el arbol AVL
     * En caso de haber claves duplicadas, el dato no se introduce
     */
    bool insertar(const T &dato);
   
    
    /*
        Busca y elimina el dato en caso de encontrarlo
     */
    bool borrar(const T &dato);
    
   /*Busca el dato en el AVL.
    En caso de no encontrarlo devuelve false, en caso contrario true*/
    bool buscar(const T &dato);
    
    /*FUNCION EXCLUSIVA PARA T=STRING*/
    bool busca_igualMayor(const string &dato);
    
    AVL<T>& operator=(const AVL &orig);
    
};



template <class T>
AVL<T>::AVL(const AVL& orig){
  
    //Borrar el que tengo
    if(raiz){
        destructor(raiz);
        raiz=0;
    }    
    
    //Generar el nuevo
    raiz=new Nodo<T>(orig.raiz->dato);
    copiarArbol(raiz,orig.raiz);
}

template <class T>
AVL<T>::~AVL(){
   
    //Borrado en postorden
    if(raiz){
        destructor(raiz);
        raiz=0;
    }
    
}

template <class T>
void AVL<T>::copiarArbol(Nodo<T>*& actual, Nodo<T>* orig){
    if(orig){
        Nodo<T> *nuevo;
        if(orig->izq){
            nuevo=new Nodo<T>(orig->izq->dato);
            actual->izq=nuevo;
        }
        if(orig->der){
            nuevo=new Nodo<T>(orig->der->dato);
            actual->der=nuevo;
        }
    
        copiarArbol(actual->izq,orig->izq);
        copiarArbol(actual->der,orig->der);
        
    }
}

template <class T>
void AVL<T>::rotDerecha(Nodo<T>*& p){
    Nodo<T> *q=p, *l;
    p=l=q->izq;
    q->izq=l->der;
    l->der=q;
    q->bal--;
    if(l->bal>0){
        q->bal-=l->bal;
    }
    l->bal--;
    if(q->bal<0){
        l->bal-=-q->bal;
    }
}

template<class T>
void AVL<T>::rotIzquierda(Nodo<T>*& p){
    Nodo<T> *q=p, *r;
    p=r=q->der;
    q->der=r->izq;
    r->izq=q;
    q->bal++;
    if(r->bal<0){
        q->bal+=-r->bal;
    }
    r->bal++;
    if(q->bal>0){
        r->bal+=q->bal;
    }

}

template <class T>
AVL<T>& AVL<T>::operator =(const AVL& orig){
    
    if(this!=&orig){
        //Borrar el que tengo
        if(raiz){
            destructor(raiz);
            raiz=0;
        }    
        //Generar el nuevo
        raiz=new Nodo<T>(orig.raiz->dato);
        copiarArbol(raiz,orig.raiz);
    }
    return *this;
    
}

template <class T>
int AVL<T>::inserta(Nodo<T>*& c,const T& dato){
    Nodo<T> *p=c;
    int deltaH=0;
    if(!p){
        p=new Nodo<T>(dato);
        c=p;
        deltaH=1;
    }
    else if(dato>p->dato){
          if(inserta(p->der,dato)){
              p->bal--;
              if(p->bal==-1) deltaH=1;
              else if(p->bal==-2){
                      if(p->der->bal==1) rotDerecha(p->der);                      
                      rotIzquierda(c);
                 }
              }
          }
        
    else if(dato<p->dato){
        if(inserta(p->izq,dato)){
            p->bal++;
            if(p->bal==1) deltaH=1;
            else if(p->bal==2){
                if(p->izq->bal==-1) rotIzquierda(p->izq);
                rotDerecha(c);
            }
        }
    }  
    return deltaH;
        
}

template <class T>
void AVL<T>::destructor(Nodo<T>* actual){
    
    if(actual){
         
        if(actual->izq)
        {
            destructor(actual->izq);
        }
        if(actual->der)
        {
            destructor(actual->der);
        }
       
        delete actual;
    }
}

template <class T>
Nodo<T> *AVL<T>::borraMin(Nodo<T>* &p){
    Nodo<T> *result;
    if(p){
        if(p->izq)
            return borraMin(p->izq);
        else
        {
            result=p;
            p=p->der;
            return result;
        }
    }
}

template <class T>
void AVL<T>::borrarDato(Nodo<T>*& p,const T& dato,bool &encontrado){
    
    if(p){
        if(dato<p->dato)
            borrarDato(p->izq,dato,encontrado);
        else{
            if(dato>p->dato)
                borrarDato(p->der,dato,encontrado);
            else{
                Nodo<T> *temp=p;
                if(!p->izq)
                    p=p->der;
                else
                    if(!p->der)
                        p=p->izq;
                    else if(p->izq && p->der){
                        temp=borraMin(p->der);
                        p->dato=temp->dato;
                    }
                delete temp;
                temp=0;                                 
                encontrado=true;
                }
        }
    }
   
}

template <class T>
Nodo<T>* AVL<T>::buscarDato(Nodo<T> *nodo,const T& dato){
    if(nodo){
        
        if(nodo->dato==dato){
            return nodo;
        }
        else
        {
            //Hay que buscar el dato por la derecha
            if(dato>nodo->dato){
                return buscarDato(nodo->der,dato);
            }
            else
            {
            //Bucar el dato por la izquierda
                return buscarDato(nodo->izq,dato);
            }
        }
    }
    else{
        return 0;
    }
}

template <class T>
bool AVL<T>::buscar(const T& dato){
    Nodo<T> *p=buscarDato(raiz,dato);
    if(p){         
        return true;
    }
    else
    {         
        return false;
    }
}

template <class T>
bool AVL<T>::insertar(const T& dato){
    
    if(!buscarDato(raiz,dato)){
        inserta(raiz,dato);       
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool AVL<T>::borrar(const T& dato){
    bool estado=false;
    borrarDato(raiz,dato,estado);    
    if(estado)
        return true;
    else
        return false;
}

template <class T>
bool AVL<T>::busca_igualMayor(const string& dato){
    Nodo<T> *p=raiz;
    //Nodo<T> *anterior=0;
    int cont=0;
    string aux;
    
    
    while(p){
        
        aux=p->dato;
        for(int i=0;i<dato.size();i++){
            if(dato[i]==aux[i])
                cont++;
        }

        if(cont==dato.size())
            return true;
            //return p->dato;
        
        if(dato>p->dato){
            //anterior=p;
            p=p->der;
        }            
        else{
            if(dato<p->dato){
                //anterior=p;
                p=p->izq;
            }
            else
            {
                return false;
            }
            
        }
        cont=0;
    }
    //return anterior->dato;
    return false;
}


#endif	/* AVL_H */

