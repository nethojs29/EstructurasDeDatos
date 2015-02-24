#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <conio2.h>

using namespace std;

//***************************************************************
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
      float Norma(){return sqrt((*this)*(*this));}
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
//********************************************************************
template <class tipo> class Pila;
template <class tipo>
class Elemento{
    friend class Pila<tipo>;
public:
    Elemento(tipo _data, Elemento* _next = NULL): data(_data),next(_next){}
private:
    tipo data;
    Elemento* next;
};
//*********************************************************************
template <class tipo>
class Pila{
public:
    Pila():Tope(NULL), elementos(0){}
    Pila(const Pila&);
    ~Pila();
    Pila & operator=(const Pila&);
    bool estaVacia(){return !Tope;}
    void Insertar(tipo);
    tipo Extraer()throw (Excepcion);
    void Imprimir()throw (Excepcion);
    tipo obtenerTope() const;
    int numElementos();
    void vaciarPila();
private:
    Elemento<tipo>* Tope;
    int elementos;
};
/////////////////////////////////////////////////////////////
template <class tipo>
Pila<tipo>::~Pila(){
	vaciarPila();
}
/////////////////////////////////////////////////////////////
template <class tipo>
Pila<tipo>::Pila(const Pila&A){
    *this = A;
}
/////////////////////////////////////////////////////////////
template <class tipo>
void Pila<tipo>::Insertar(tipo _data){
	Elemento <tipo>*aux = new Elemento<tipo>(_data,Tope);
	Tope = aux;
	++elementos;
}
/////////////////////////////////////////////////////////////
template <class tipo>
tipo Pila<tipo>::obtenerTope()const{
    if(estaVacia()) throw Excepcion("Pila sin elementos");
    return Tope->data;
}
/////////////////////////////////////////////////////////////
template <class tipo>
tipo Pila<tipo>::Extraer()throw (Excepcion){
	if(estaVacia()) throw Excepcion("Pila sin elementos");
	Elemento<tipo> *aux = Tope;
	tipo _data = Tope -> data;
	Tope = Tope -> next;
	delete aux;
	--elementos;
	return _data;
}
/////////////////////////////////////////////////////////////
template <class tipo>
void Pila<tipo>::Imprimir()throw (Excepcion){
    if(!estaVacia()){
        cout<<"Tope ->";
        for(Elemento <tipo>*aux = Tope; aux; aux = aux->next){
            cout<<aux->data<<" ";
        }
    }else{
        throw Excepcion("Pila sin elementos");
    }
}
/////////////////////////////////////////////////////////////
template <class tipo>
void Pila<tipo>::vaciarPila(){
	if(estaVacia()) return;
	Elemento<tipo> *aux;
	while(!estaVacia()){
		aux = Tope;
		Tope = Tope->next;
		delete aux;
	}
	elementos=0;
}
/////////////////////////////////////////////////////////////
template <class tipo>
Pila<tipo>& Pila<tipo>::operator=(const Pila &A){
	if(this!=&A){
        int i=0;
        Elemento <tipo>*array[A.elementos];
        for(Elemento<tipo>*aux=A.Tope;aux;aux=aux->next,++i){
            array[i] = aux;
            ++elementos;
        }
        for(int i=elementos-1; i>=0 ; --i) Insertar(array[i]->data);
	}
	return *this;
}

int main() throw (Excepcion){
    try{
        textcolor(CYAN); cout<<"Cyan ";
        textcolor(WHITE); cout<<"= Pila de Vectores"<<endl;

        textcolor(YELLOW); cout<<"Amarillo ";
        textcolor(WHITE); cout<<"= Pila de Dobles"<<endl;

        textcolor(GREEN); cout<<"Verde ";
        textcolor(WHITE); cout<<"= Pila de Enteros\n\n"<<endl;

        //**********************************
        ////         PILA DE VECTORES
        //***********************************
        Pila<Vector> vectores,v;
        Vector aux(3);

        textcolor(CYAN);

        cout<<"Primer vector para meter en la pila:"<<endl;
        cin>>aux;
        vectores.Insertar(aux);
        cout<<"Segundo vector para meter en la pila:"<<endl;
        cin>>aux;
        vectores.Insertar(aux);

        cout<<"Pila de vectores: "<<endl;
        vectores.Imprimir();
        cout<<"\nSe copia la pila en otra."<<endl;
        v=vectores;
        cout<<"\nPrimera pila:"<<endl;
        vectores.Imprimir();
        cout<<"\n\nSegunda pila:"<<endl;
        v.Imprimir();

        Vector x = v.Extraer();
        cout<<"\n\nSe extrae el vector: "<<x<<endl;
        cout<<"\nLa pila qued\xa2: ";
        v.Imprimir();

        //**********************************
        ////         PILA DE DOBLES
        //***********************************

        double auxx;
        Pila<double> dobles,d;

        textcolor(YELLOW);

        cout<<"\n\nPrimer doble para meter en la pila:";
        cin>>auxx;
        dobles.Insertar(auxx);
        cout<<"Segundo doble para meter en la pila:";
        cin>>auxx;
        dobles.Insertar(auxx);

        cout<<"Pila de dobles: "<<endl;
        dobles.Imprimir();
        cout<<"\nSe copia la pila en otra."<<endl;
        d=dobles;
        cout<<"\nPrimera pila:"<<endl;
        dobles.Imprimir();
        cout<<"\n\nSegunda pila:"<<endl;
        d.Imprimir();

        double y = d.Extraer();
        cout<<"\n\nSe extrae el doble: "<<y<<endl;
        cout<<"\nLa pila qued\xa2: ";
        d.Imprimir();

        //**********************************
        ////         PILA DE CADENAS
        //***********************************
        Pila<int> cadenas,c;
        int auxxx;

        textcolor(GREEN);

        cout<<"\n\nPrimer entero para meter en la pila:";
        cin>>auxxx;
        cadenas.Insertar(auxxx);
        cout<<"Segunda entero para meter en la pila:";
        cin>>auxxx;
        cadenas.Insertar(auxxx);

        cout<<"Pila de enteros: "<<endl;
        cadenas.Imprimir();
        cout<<"\nSe copia la pila en otra."<<endl;
        c=cadenas;
        cout<<"\nPrimera pila:"<<endl;
        cadenas.Imprimir();
        cout<<"\n\nSegunda pila:"<<endl;
        c.Imprimir();

        int z = c.Extraer();
        cout<<"\n\nSe extrae el entero: "<<z<<endl;
        cout<<"\nLa pila qued\xa2: ";
        c.Imprimir();

        textcolor(WHITE);

    }catch(Excepcion e){
        cout<<e.getMensaje();
    }

    cout<<endl;
    return 0;
}
