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

template <class tipo> class Cola;
template <class tipo>
class Elemento{
    friend class Cola<tipo>;
public:
    Elemento(tipo _data, Elemento* _next = NULL): data(_data),next(_next){}
private:
    tipo data;
    Elemento* next;
};
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
class Cola{
public:
    Cola():Primero(NULL),Ultimo(NULL),elementos(0){}
    Cola(const Cola&);
    ~Cola();
    Cola& operator= (const Cola&);
    bool estaVacia();
    void Encolar(tipo);
    tipo Desencolar();
    void vaciarCola();
    int getSize();
    tipo getFirst();
    void Imprimir();

private:
    Elemento <tipo>* Primero;
    Elemento <tipo>* Ultimo;
    int elementos;

};
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
Cola<tipo>::Cola(const Cola&A){
    *this = A;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
Cola<tipo>& Cola<tipo>::operator=(const Cola &A){
	if(this!=&A){
        int i=0;
        Elemento <tipo>*array[A.elementos];
        for(Elemento<tipo>*aux=A.Primero;aux;aux=aux->next,++i){
            array[i] = aux;
            ++elementos;
        }
        for(int i=0;i<A.elementos;++i) Encolar(array[i]->data);
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
Cola<tipo>::~Cola(){
    vaciarCola();
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
bool Cola<tipo>::estaVacia(){
    if(!Primero) return true;
    else return false;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Cola<tipo>::Encolar(tipo _data){
    Elemento<tipo>* Nuevo = new Elemento<tipo>(_data);
    if(!estaVacia())
        Ultimo->next = Nuevo;
    else
        Primero = Nuevo;
    Ultimo = Nuevo;
    ++elementos;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
tipo Cola<tipo>::Desencolar(){
    if(estaVacia()) throw Excepcion ("puuuuuuuum");
    else{
        tipo aux = Primero->data;
        Elemento<tipo> *auxx = Primero;
        Primero = Primero->next;

        if(!Primero) Ultimo=NULL;

        delete auxx;
        --elementos;
        return aux;
    }
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
int Cola<tipo>::getSize(){
    return elementos;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
tipo Cola<tipo>::getFirst(){
    return Primero->data;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Cola<tipo>::vaciarCola(){
    if(estaVacia()) return;
	Elemento<tipo> *aux;
	while(!estaVacia()){
		aux = Primero;
		Primero = Primero->next;
		delete aux;
	}
	Ultimo = NULL;
	elementos=0;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Cola<tipo>::Imprimir(){
    if(!estaVacia()){
        cout<<"Primero -> ";
        for(Elemento <tipo>*aux = Primero; aux; aux = aux->next){
            cout<<aux->data<<"  ";
        }
        cout<<"<- Ultimo"<<endl;
    }else
        throw Excepcion ("Cola sin elementos");
}
int main(){
    try{
        Cola<int> c;
        c.Encolar(1);
        c.Encolar(3);
        c.Encolar(6);
        c.Imprimir();
        cout<<endl;
        c.Desencolar();
        c.Imprimir();
        Cola<int> d;
        d = c;
        d.Imprimir();
        d.vaciarCola();
        d.Imprimir();
    }catch(Excepcion e){
        cout<<e.getMensaje();
    }

    cout<<endl;
    system("PAUSE");
    return 24;
}


/*
    COLA CIRCULAR


    Elemento * Nuevo = new Elemento(valor, Ultimo->next);
    Ultimo->next = Nuevo;
    Ultimo = Nuevo;

        CASO SIN ELEMENTOS

        if(estaVacia())
            Elemento * Nuevo = new Elemento (valor);
            Nuevo->Sig = Nuevo;
        else
            Elemento * Nuevo new Elemento(valor, Ultimo->sig);
            Ultimo->sig = Nuevo;
        Ultimo = Nuevo;

        CASO CON UN SOLO ELEMENTO
        Igual :3

        DESENCOLAR CON UN ELEMENTO

        if(estaVacia()) throw Excepcion ("puuuuuuuum");
    else{
        tipo aux = Ultimo->Sig->data;
        Elemento<tipo> *auxx = Ultimo->sig;
        Ultimo->sig = auxx->sig;

        if(!Ultimo) Ultimo=NULL; <--- NO SÉ SI VA D:

        delete auxx;
        --elementos;
        return aux;
    }
*/
