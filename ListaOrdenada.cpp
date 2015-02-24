#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Excepcion{
public:
	Excepcion(char* mensaje){strcpy(msj,mensaje);}
	char* getMensaje(){return msj;}
private:
	char msj[50];
};

template <class tipo> class Lista;
template <class tipo>
class Elemento{
    friend class Lista<tipo>;
public:
    Elemento(tipo _data, Elemento* _next = NULL): data(_data),next(_next){}
private:
    tipo data;
    Elemento* next;
};
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
class Lista{
public:
    Lista():Primero(NULL),elementos(0){}
    Lista(const Lista&);
    ~Lista();
    Lista& operator= (const Lista&);
    bool estaVacia();
    bool Extraer(tipo);
    bool BuscarElemento(tipo); // <---- HACER
    void vaciarLista();
    int getSize();
    tipo getFirst();
    void Imprimir();
    void Insertar(tipo);

private:
    Elemento <tipo>* Primero;
    int elementos;

};
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
Lista<tipo>::Lista(const Lista&A){
    *this = A;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
Lista<tipo>& Lista<tipo>::operator=(const Lista &A){
	if(this!=&A){
        int i=0;
        Elemento <tipo>*array[A.elementos];
        for(Elemento<tipo>*aux=A.Primero;aux;aux=aux->next,++i){
            array[i] = aux;
            ++elementos;
        }
        for(int i=0;i<A.elementos;++i) EnListar(array[i]->data);
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
Lista<tipo>::~Lista(){
    vaciarLista();
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
bool Lista<tipo>::estaVacia(){
    if(!Primero) return true;
    else return false;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
int Lista<tipo>::getSize(){
    return elementos;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
tipo Lista<tipo>::getFirst(){
    return Primero->data;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Lista<tipo>::vaciarLista(){
    if(estaVacia()) return;
	Elemento<tipo> *aux;
	while(!estaVacia()){
		aux = Primero;
		Primero = Primero->next;
		delete aux;
	}
	elementos=0;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Lista<tipo>::Imprimir(){
    if(!estaVacia()){
        cout<<"Primero -> ";
        for(Elemento <tipo>*aux = Primero; aux; aux = aux->next){
            cout<<aux->data<<"  ";
        }
        cout<<endl;
    }else
        throw Excepcion ("Lista sin elementos");
}
/////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Lista<tipo>::Insertar(tipo stuff){
  Elemento<tipo> * ant=NULL,*aux=Primero;

  while(aux && stuff > aux->data){
    ant = aux;
    aux = aux->next;
  }
  Elemento<tipo> * Nuevo = new Elemento<tipo>(stuff,aux);
  ant ? ant->next=Nuevo : Primero = Nuevo;
  Nuevo->next = aux;
}

//////////////////////////////////////////////////////////////////////////////
template <class tipo>
bool Lista<tipo>::Extraer(tipo stuff){
  Elemento <tipo>*aux = Primero,*ant=NULL;

  while(aux && aux->data!=stuff){
    ant = aux;
    aux = aux->next;
  }
  if(!aux) return false;
  ant ? ant->next = aux->next : Primero=aux->next;
  delete aux;
  --elementos;
  return true;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
bool Lista<tipo>::BuscarElemento(tipo stuff){
    Elemento <tipo>*aux=Primero,*ant=NULL;

    while(aux && aux->data!=stuff){
        ant = aux;
        aux = aux->next;
    }
    if(!aux) return false;
    else return true;


}
//////////////////////////////////////////////////////////////////////////////
int main(){
    try{
        Lista<int> l;
        l.Insertar(6);
        l.Insertar(30);
        l.Insertar(1);
        l.Insertar(3);

        l.Imprimir();

        if(l.BuscarElemento(1)) cout<<"yay"<<endl;
        else cout<<"meh :c"<<endl;

        l.Imprimir();
    }catch(Excepcion e){
        cout<<e.getMensaje();
    }

    cout<<endl;
    system("PAUSE");
    return 24;
}
