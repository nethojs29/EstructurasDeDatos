#include <iostream>
#include <cstdlib>
#include <new>
#include <cmath>

using namespace std;

template <class tipo>
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector::Vector(int tam):n(tam)
{
   if(n<0)throw 1;
   comp = new (nothrow) float [n];
   if(comp == NULL)throw false;
   for(int i = 0; i < n; ++i)comp[i] = 0;

   /*
   try{
      comp = new (notrhow) float [tam];
   }catch(...){//recibe cualquier cosa
      throw "No hubo memoria."
   }*/

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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector Vector::operator+(const Vector &V)const
{
   Vector Z(n);
   //if(n==V.n){
      for(int i = 0; i < n;++i)Z.comp[i] = comp[i] + V.comp[i];
   //}else throw "No se pueden sumar, los vectores tienen diferente dimension.";
   return Z;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector Vector::operator-(const Vector &V)const
{
   Vector Z(n);
   for(int i = 0; i < n;++i)Z.comp[i] = comp[i] - V.comp[i];

   return Z;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Vector Vector :: operator*(float escalar)const
{
   Vector R(n);//creamos el vector donde guardaremos la resta
   for(int i = 0; i < n; ++i)R.comp[i]=comp[i]*escalar;
   return R;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float Vector :: operator*(const Vector &V)const
{
    float producto = 0;
    for(int i=0; i<n; ++i) producto+=(comp[i]*V.comp[i]);
    return producto;

}
//*********************Funciones Amigas****************************************
ostream & operator<<(ostream &salida, const Vector &V)
{
   cout<<"[ ";
   for(int i=0; i<V.n;++i)salida<<V.comp[i]<<", ";
   cout<<"\b\b ]";
   return salida;
}
//******************************************************************************
istream & operator>>(istream &entrada,Vector &V)
{
   for(int i=0; i<V.n;++i){
      cout<<"Introduzca el componente "<<i+1<<" : "<<endl;
      entrada>>V.comp[i];
   }
   cout<<endl;
   return entrada;
}

int main(){

    cout<<endl;
    system("pause");
    return 0;
}
