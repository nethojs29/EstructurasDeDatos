/*
  Programa:EFLF_ClaseVectorFijo.cpp
n  Fecha:12/01/15 16:52
  Descripcion:Programa que realiza las operaciones basicas con vectores: Suma, Resta, Multiplicacion por escalar,Producto punto y norma de un
   vector.
*/

#include <iostream>
#include <cstdlib>
#include "Vector.hpp"
#include "Utility.hpp"
using namespace std;

#define MAX 10
typedef float tipo;

//******************************************************************************
int Menu();
//******************************************************************************
int main ()
{
   int tam;
   int opcion;
   do{
   opcion = Menu();

   do{
      cout<<"Introduzca la dimensi\xA2n del vector: ";
      cin>>tam;
   }while(tam<0);
   try{
      Vector A(tam),B(tam),Z(tam);//declaramos los vectores para realizar las operaciones
      switch(opcion){
         case 1:
            cout<<"Introduzca el primer vector a sumar."<<endl;
            cin>>A;
            cout<<"Introduzca el segundo vector a sumar."<<endl;
            cin>>B;
            cout<<A<<endl;
            cout<<B<<endl;
            Z = A + B;
            cout<<Z<<endl;
         break;
         case 2:
            cout<<"Introduzca el primer vector a restar."<<endl;
            cin>>A;
            cout<<"Introduzca el segundo vector a restar."<<endl;
            cin>>B;
            cout<<A;
            cout<<B;
            Z = A - B;
            cout<<Z;
         break;
         case 3:
            float escalar;
            cout<<"Introduzca el vector: "<<endl;
            cin>>A;
            cout<<"Introduzca el escalar: ";
            cin>>escalar;
            cout<<"A = "<<A;
            //cout<<A<<" * "<<escalar<<" = ";
            Z = escalar*A;
            cout<<"A * "<<escalar<<" = "<<Z;
         break;
         case 4:
            float X;
            cout<<"Introduzca el primer vector a multiplicar."<<endl;
            cin>>A;
            cout<<"Introduzca el segundo vector a multiplicar."<<endl;
            cin>>B;
            X = A * B;
            cout<<A<<" * "<<B<<" = "<<X<<endl;
         break;
         case 5:
            float norma;
            cout<<"Introduzca el primer vector a obtener su norma."<<endl;
            cin>>A;
            norma = A.Norma();
            cout<<"La norma es: "<<norma<<endl;
         break;
      }
   }catch(bool){
      cout<<"No hay memoria disponible en el sistema."<<endl;
   }catch(int){
      cout<<"El tama\xA4o es negativo."<<endl;
   }
}while(opcion!=0);
   utility::pause();
   return 0;
}
//****************************************************************************//
int Menu()
{
   int opcion;
   cout<<"Programa que realiza las operaciones basicas con vectores, por favor "<<endl;
   cout<<"elige una opci\xA2n: "<<endl;
   cout<<"0) Salir."<<endl;
   cout<<"1) Suma de dos vectores."<<endl;
   cout<<"2) Resta de dos vectores."<<endl;
   cout<<"3) Producto de un vector por un escalar."<<endl;
   cout<<"4) Producto punto."<<endl;
   cout<<"5) Norma de un vector."<<endl<<endl;

   cout<<"Cu\xA0l opci\xA2n desea realizar? ";
   cin>>opcion;
   while(opcion <0 || opcion >5){
      cout<<"Error. Introduzca una opci\xA2n correcta: ";
      cin>>opcion;
   }
   return opcion;
}
//****************************************************************************//

