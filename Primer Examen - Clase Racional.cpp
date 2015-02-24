/*
    Nombre: main.cpp
    Autor: Jesús Ernesto Jaramillo Salazar
    Descripción: Programa que utiliza el objeto Racional para denotar una fracción y con él operar mediante la
                 utilización de la clase Arreglo.
    Fecha: Febrero 11 del 2015
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <conio2.h>


using namespace std;

class Excepcion{

public:
	Excepcion(char* mensaje){strcpy(msj,mensaje);}
	char* getMensaje(){return msj;}
private:
	char msj[50];
};

//*******************************************************************
class Racional{
public:

    friend ostream & operator<<(ostream &, const Racional &);
    friend istream & operator>>(istream &, Racional &);

    Racional(){}
    Racional(int,int);

    void Simplificar();
    void Imprimir();
    void Capturar();

    Racional& operator=(const Racional&);
    Racional operator+(const Racional&) const;
    Racional operator-(const Racional&) const;
    Racional operator*(const Racional&) const;
    Racional operator/(const Racional&) const;

    bool operator>(const Racional&)const;
    bool operator>=(const Racional&)const;
    bool operator==(const Racional&)const;
    bool operator!=(const Racional&)const;
    bool operator<(const Racional&)const;
    bool operator<=(const Racional&)const;

private:
    int denominador, numerador;

};

template<class tipo> class Arreglo;

//**************************************************************************
template <class tipo>
istream & operator>>(istream &entrada,Arreglo<tipo> &V){
    for(int i=0;i<V.elementos;++i){
        cout<<"Da el elemento "<<i+1<<": "<<endl;
        cin>>V.arr[i];
    }
}
//********************************************************************************
template <class tipo>
ostream & operator<<(ostream &salida, const Arreglo<tipo> &V){
   for(int i=0; i<V.elementos;++i)salida<<V.arr[i]<<" ";

   return salida;
}
//**************************************************************
template <class tipo>
class Arreglo{

public:
    friend istream & operator>> <>(istream &,Arreglo&);
    friend ostream & operator<< <>(ostream &,const Arreglo<tipo>&);


    Arreglo(int n):elementos(n){arr = new (nothrow) tipo [elementos];}
    Arreglo(const Arreglo&);
    ~Arreglo();
    Arreglo& operator=(const Arreglo&A);

    tipo& operator[](int i) { return *(arr + i); }

    void Imprimir();
    void Capturar();
    void OrdenarDes();
    void OrdenarAsc();

private:
    int elementos;
    tipo* arr;
};

  //**********************************************************\\
 //                  METODOS CLASE ARREGLO                     \\
//**************************************************************\\

template <class tipo>
Arreglo<tipo>::Arreglo(const Arreglo&A){
    *this = A;
}
//**********************************************************************
template<class tipo>
Arreglo<tipo>::~Arreglo(){
    delete [] arr;
}
//************************************************************************
template <class tipo>
Arreglo<tipo>& Arreglo<tipo>::operator=(const Arreglo<tipo>&A){
    if(this != &A){
      if(elementos != A.elementos){
         if(!arr)
            delete [] arr;
         elementos = A.elementos;
         arr = new (nothrow) tipo [elementos];
      }
      for(int i = 0; i < elementos; ++i)arr[i] = A.arr[i];
   }
   return *this;
}
//**********************************************************************************
template <class tipo>
void Arreglo<tipo>::Imprimir(){
    for(int i=0;i<elementos;++i){
        cout<<arr[i]<<"  ";
    }
}
//*******************************************************************************
template <class tipo>
void Arreglo<tipo>::OrdenarAsc(){
    for(int i=0;i<elementos;++i){
    	int menor;
    	tipo aux;
    	menor = i;
    	for (int j=i+1;j<elementos;j++){
			if(arr[j]<arr[menor])menor = j;
    	}
    	aux=arr[i];
    	arr[i]=arr[menor];
    	arr[menor]=aux;
    }
}
//***************************************************************************
template <class tipo>
void Arreglo<tipo>::OrdenarDes(){
    for(int i=0;i<elementos;++i){
    	int mayor;
    	tipo aux;
    	mayor = i;
    	for (int j=i+1;j<elementos;j++){
            if(arr[j]>arr[mayor])mayor = j;
    	}
    	aux=arr[i];
    	arr[i]=arr[mayor];
    	arr[mayor]=aux;
    }
}

  //**********************************************************\\
 //                 METODOS CLASE RACIONAL                     \\
//**************************************************************\\

Racional::Racional(int x, int y) : numerador(x),denominador(y){

    if(denominador==0){
        textcolor(RED);
        throw Excepcion("Denominador no puede ser 0");
    }
    if(denominador<0){
        numerador*=-1;
        denominador*=-1;
    }
}
//************************************************************************
void Racional::Simplificar(){
    for(int i=2;i<81;++i){
            if(numerador % i == 0 && denominador % i == 0){
                numerador/=i;
                denominador/=i;
            }
        }
}
//*************************************************************************
ostream & operator<<(ostream &salida, const Racional &R){
    cout<<R.numerador<<"/"<<R.denominador;
}
//*************************************************************************
istream & operator>>(istream &entrada,Racional &R){
    cout<<"Numerador: ";
    cin>>R.numerador;
    cout<<"Denominador: ";
    cin>>R.denominador;
    if(R.denominador==0){
        textcolor(RED);
        throw Excepcion("Denominador no puede ser 0, est\xa0 indefinido");
    }

}
//*************************************************************************
Racional& Racional::operator=(const Racional& A){
    numerador = A.numerador;
    denominador = A.denominador;
    return *this;
}
//**************************************************************************
Racional Racional::operator+(const Racional&A)const{
    Racional aux(1,1);
    aux.numerador = numerador*A.denominador + denominador*A.numerador;
    aux.denominador = denominador*A.denominador;

    aux.Simplificar();

    return aux;
}
//**************************************************************************
Racional Racional::operator-(const Racional&A)const{
    Racional aux(1,1);
    aux.numerador = numerador*A.denominador - denominador*A.numerador;
    aux.denominador = denominador*A.denominador;

    aux.Simplificar();

    return aux;
}
//**************************************************************************
Racional Racional::operator*(const Racional&A)const{
    Racional aux(1,1);
    aux.numerador = numerador*A.numerador;
    aux.denominador = denominador*A.denominador;

    return aux;
}
//**************************************************************************
Racional Racional::operator/(const Racional&A)const{
    Racional aux(1,1);
    aux.numerador = numerador*A.denominador;
    aux.denominador = denominador*A.numerador;

    return aux;
}
//**************************************************************************
bool Racional::operator>(const Racional&A)const{
    double x, y;
    x = (double)numerador/denominador;
    y = (double)A.numerador/A.denominador;

    if(x>y){
        return true;
    }else{
        return false;
    }
}
//***************************************************************************
bool Racional::operator>=(const Racional&A)const{
    double x,y;
    x = (double)numerador/denominador;
    y = (double)A.numerador/A.denominador;

    if(x>=y){
        return true;
    }else{
        return false;
    }
}
//***************************************************************************
bool Racional::operator==(const Racional&A)const{
    double x,y;
    x = (double)numerador/denominador;
    y = (double)A.numerador/A.denominador;

    if(x==y){
        return true;
    }else{
        return false;
    }
}
//***************************************************************************
bool Racional::operator!=(const Racional&A)const{
    double x,y;
    x = (double)numerador/denominador;
    y = (double)A.numerador/A.denominador;

    if(x!=y){
        return true;
    }else{
        return false;
    }
}
//****************************************************************************
bool Racional::operator<(const Racional&A)const{
    double x,y;
    x = (double)numerador/denominador;
    y = (double)A.numerador/A.denominador;

    if(x<y){
        return true;
    }else{
        return false;
    }
}
//*****************************************************************************
bool Racional::operator<=(const Racional&A)const{
    double x,y;
    x = (double)numerador/denominador;
    y = (double)A.numerador/A.denominador;

    if(x<=y){
        return true;
    }else{
        return false;
    }
}

  //**********************************************************\\
 //                           MAIN                             \\
//**************************************************************\\


int main()
{
    textcolor(WHITE);
    int n,opc;
    try{
        cout<<"n: ";
        cin>>n;

        if(n<=0){
            textcolor(RED);
            throw Excepcion("Valor no v\xa0lido.\n");
        }

        Arreglo <Racional> arr(n);
        cin>>arr;

        cout<<endl;
        cout<<arr;

        cout<<endl<<endl;
        cout<<"De qu\x82 forma quiere ordenar el arreglo?"<<endl;
        cout<<"1) Descendente    2) Ascendente: ";
        cin>>opc;

        if(opc<1 || opc>2){
            textcolor(RED);
            throw Excepcion("Opci\xa2n no disponible");
        }

        if(opc==1) arr.OrdenarDes();
        if(opc==2) arr.OrdenarAsc();
        cout<<endl<<"Arreglo ordenado";
        cout<<arr;

        Racional aux(0,1);
        for(int i=0;i<n;++i) aux = aux+arr[i];

        cout<<endl<<endl<<"Suma de todo el arreglo: ";
        textcolor(YELLOW);
        cout<<aux;
        textcolor(WHITE);

        Racional auxx(1,1);
        for(int i=0;i<n;++i) auxx = auxx*arr[i];

        cout<<endl<<endl<<"Producto de todo el arreglo: ";
        textcolor(YELLOW);
        cout<<auxx;
        textcolor(WHITE);

        cout<<endl;
        return 0;
    }catch(Excepcion e){
        cout<<endl<<e.getMensaje();
        textcolor(WHITE);
    }
}
