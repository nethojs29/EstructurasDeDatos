#ifndef _VECTOR_HPP
#define _VECTOR_HPP
#include <iostream>
#include <cmath>

using namespace std;

class Vector{
   friend ostream & operator<<(ostream &, const Vector &);
   friend istream & operator>>(istream &, Vector &);
   friend Vector operator*(float escalar, Vector &V){return V*escalar;}
   public:
      explicit Vector(int);
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
#endif