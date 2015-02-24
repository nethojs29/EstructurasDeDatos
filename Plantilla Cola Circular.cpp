#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Utility.hpp"


using namespace std;
using namespace utility;

class Vector{
   friend ostream & operator<<(ostream &, const Vector &);
   friend istream & operator>>(istream &, Vector &);
   friend Vector operator*(float escalar, Vector &V){return V*escalar;}
   public:
      Vector(int);
      Vector(const Vector &);
      ~Vector();
      Vector & operator=(const Vector &);
      Vector operator+(const Vector &) const;
      Vector operator-(const Vector &) const;
      Vector operator*(float escalar) const;
      float operator*(const Vector &) const;
   private:
      int n;//tamaño del vector
      float *comp;//componentes del vector
};
//*********************Funciones Amigas****************************************
ostream & operator<<(ostream &salida, const Vector &V)
{
   cout<<"(";
   for(int i=0; i<V.n;++i)salida<<V.comp[i]<<", ";
   cout<<"\b\b)";
   return salida;
}
//******************************************************************************
istream & operator>>(istream &entrada,Vector &V)
{
   for(int i=0; i<V.n;++i){
      cout<<"Introduzca el componente "<<i+1<<": ";
      entrada>>V.comp[i];
   }
   cout<<endl;
   return entrada;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector::Vector(int tam):n(tam)
{
   if(n<0)throw 1;
   comp = new (nothrow) float [n];
   if(comp == NULL)throw false;
   for(int i = 0; i < n; ++i)comp[i] = 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector::~Vector()
{
   delete [] comp;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector::Vector(const Vector &V): n(-1),comp(NULL)
{
   *this = V;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector & Vector::operator=(const Vector &V)
{
   if(this != &V){//evita la auto asignacion
      if(n != V.n){
         if(!comp)
            delete [] comp;
         n = V.n;//redimencionamos
         comp = new (nothrow) float [n];
         //if(comp == NULL){...}
      }
      for(int i = 0; i < n; ++i)comp[i] = V.comp[i];
   }
   return *this;
}
//****************************************************************

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
    Cola():Ultimo(NULL),elementos(0){}
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
        for(Elemento<tipo>*aux=A.Ultimo->next;i<A.elementos;aux=aux->next,++i){
            array[i] = aux;
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
    if(!Ultimo) return true;
    else return false;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Cola<tipo>::Encolar(tipo _data){
    Elemento<tipo>* Nuevo = new Elemento<tipo>(_data);
    if(estaVacia()){
        Nuevo->next = Nuevo;
    }else{
        Nuevo->next = Ultimo->next;
        Ultimo->next = Nuevo;
    }
    Ultimo = Nuevo;
    ++elementos;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
tipo Cola<tipo>::Desencolar(){
    if(estaVacia()) throw Excepcion ("puuuuuuuum");
    else{
        tipo aux = Ultimo->next->data;
        Elemento<tipo> *auxx = Ultimo->next;
        Ultimo->next = auxx->next;

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
    return Ultimo->next->data;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Cola<tipo>::vaciarCola(){
    if(estaVacia()) return;
	Elemento<tipo> *aux;
	while(!estaVacia()){
		aux = Ultimo->next;
        if(aux->next == Ultimo){
            delete aux;
            break;
        }else{
            Ultimo->next = Ultimo->next->next;    
            delete aux;
        }
	}
	Ultimo = NULL;
	elementos=0;
}
//////////////////////////////////////////////////////////////////////////////
template <class tipo>
void Cola<tipo>::Imprimir(){
    int i=0;
    if(!estaVacia()){
        cout<<"Primero -> ";
        for(Elemento <tipo>*aux = Ultimo->next; i<elementos; aux = aux->next,++i){
            cout<<aux->data<<"  ";
        }
        cout<<"<- Ultimo"<<endl;
    }else
        throw Excepcion ("Cola sin elementos");
}

/////////////////////////////////////////////////////////////////////////////

int main(){
    try{
        Cola<Vector> vectores,v;
        Vector aux(3);

        cout<<"Primer vector para meter en la cola:"<<endl;
        cin>>aux;
        vectores.Encolar(aux);
        cout<<"Segundo vector para meter en la cola:"<<endl;
        cin>>aux;
        vectores.Encolar(aux);

        cout<<"Cola de vectores: "<<endl;
        vectores.Imprimir();
        cout<<"\nSe copia la cola en otra."<<endl;
        v=vectores;
        cout<<"\nPrimera cola:"<<endl;
        vectores.Imprimir();
        cout<<"\n\nSegunda cola:"<<endl;
        v.Imprimir();

        Vector x = v.Desencolar();
        cout<<"\n\nSe extrae el vector: "<<x<<endl;
        cout<<"\nLa cola qued\xa2: ";
        v.Imprimir();

////////////////////////////////////////////////////////////////

        Cola<char> cadenas, c;
        char auxx;

        cout<<"Primer caracter para meter en la cola:"<<endl;
        cin>>auxx;
        cadenas.Encolar(auxx);
        cout<<"Segundo caracter para meter en la cola:"<<endl;
        cin>>auxx;
        cadenas.Encolar(auxx);

        cout<<"Cola de caracteres: "<<endl;
        cadenas.Imprimir();
        cout<<"\nSe copia la cola en otra."<<endl;
        c=cadenas;
        cout<<"\nPrimera cola:"<<endl;
        cadenas.Imprimir();
        cout<<"\n\nSegunda cola:"<<endl;
        c.Imprimir();

        char y = c.Desencolar();
        cout<<"\n\nSe extrae el caracter: "<<y<<endl;
        cout<<"\nLa cola qued\xa2: ";
        c.Imprimir();

/////////////////////////////////////////////////////////////////////////////////

        Cola<double> dobles, d;
        double auxxx;

        cout<<"Primer doble para meter en la cola:"<<endl;
        cin>>auxxx;
        dobles.Encolar(auxxx);
        cout<<"Segundo doble para meter en la cola:"<<endl;
        cin>>auxxx;
        dobles.Encolar(auxxx);

        cout<<"Cola de dobles: "<<endl;
        cadenas.Imprimir();
        cout<<"\nSe copia la cola en otra."<<endl;
        d=dobles;
        cout<<"\nPrimera cola:"<<endl;
        dobles.Imprimir();
        cout<<"\n\nSegunda cola:"<<endl;
        d.Imprimir();

        double z = d.Desencolar();
        cout<<"\n\nSe extrae el doble: "<<z<<endl;
        cout<<"\nLa cola qued\xa2: ";
        d.Imprimir();
    }catch(Excepcion e){
        cout<<e.getMensaje();
    }

    cout<<endl;
    system("PAUSE");
    return 24;
}


