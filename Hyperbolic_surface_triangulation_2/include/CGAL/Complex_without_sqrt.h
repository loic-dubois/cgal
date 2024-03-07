// Copyright (c) 2024
// INRIA Nancy (France), and Université Gustave Eiffel Marne-la-Vallée (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL$
// $Id$
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
// Author(s)     : Vincent Despré, Loïc Dubois, Monique Teillaud

// This file contains the declaration and the implementation of the class Complex_without_sqrt

#ifndef CGAL_COMPLEX_WITHOUT_SQRT
#define CGAL_COMPLEX_WITHOUT_SQRT

#include <fstream>
#include <sstream>

namespace CGAL {

/*
Templated by a field FT. Represents a complex number over FT.
*/
template <class FT>
class Complex_without_sqrt {
private:
  typedef Complex_without_sqrt<FT>            _Self;
  FT _real, _imag;

public:
  typedef FT Ft;

  Complex_without_sqrt();
  Complex_without_sqrt(const FT& real);
  Complex_without_sqrt(const FT& real, const FT& imag);

  void set_real(const FT& real);
  void set_imag(const FT& imag);

  FT real() const;
  FT imag() const;

  FT squared_modulus() const;
  _Self conjugate() const;
  _Self operator+(const _Self& other) const;
  _Self operator-(const _Self& other) const;
  _Self operator-() const;
  _Self operator*(const _Self& other) const;
  _Self operator/(const _Self& other) const;
};

template<class FT> bool operator==(const Complex_without_sqrt<FT>& z1, const Complex_without_sqrt<FT>& z2);
template<class FT> bool operator!=(const Complex_without_sqrt<FT>& z1, const Complex_without_sqrt<FT>& z2);

template<class FT>std::ostream& operator<<(std::ostream& s, const Complex_without_sqrt<FT>& z);
template<class FT>void operator>>(std::istream& s, Complex_without_sqrt<FT>& z);

// Returns the cross ratio (d-b)*(c-a) / ((d-a)*(c-b))
template<class FT> Complex_without_sqrt<FT> cross_ratio(Complex_without_sqrt<FT> a, Complex_without_sqrt<FT> b, Complex_without_sqrt<FT> c, Complex_without_sqrt<FT> d);
// Returns d such that (d-b)*(c-a) / ((d-a)*(c-b)) = cratio
template<class FT> Complex_without_sqrt<FT> fourth_point_from_cross_ratio(Complex_without_sqrt<FT> a, Complex_without_sqrt<FT> b, Complex_without_sqrt<FT> c, Complex_without_sqrt<FT> cratio);


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<class FT>
Complex_without_sqrt<FT>::Complex_without_sqrt(){
  _real = FT(0);
  _imag = FT(0);
}

template<class FT>
Complex_without_sqrt<FT>::Complex_without_sqrt(const FT& real){
  _real = real;
  _imag = FT(0);
}

template<class FT>
Complex_without_sqrt<FT>::Complex_without_sqrt(const FT& real, const FT& imag){
  _real = real;
  _imag = imag;
}

////////////////////////////////////////////////////////////////////////////////

template<class FT>
void Complex_without_sqrt<FT>::set_real(const FT& real){
  _real = real;
}

template<class FT>
void Complex_without_sqrt<FT>::set_imag(const FT& imag){
  _imag = imag;
}

////////////////////////////////////////////////////////////////////////////////

template<class FT>
FT Complex_without_sqrt<FT>::real() const{
  return _real;
}

template<class FT>
FT Complex_without_sqrt<FT>::imag() const{
  return _imag;
}

////////////////////////////////////////////////////////////////////////////////

template<class FT>
FT Complex_without_sqrt<FT>::squared_modulus() const{
  return _real*_real + _imag*_imag;
}

template<class FT>
Complex_without_sqrt<FT> Complex_without_sqrt<FT>::conjugate() const{
  return Complex_without_sqrt<FT>(_real, -_imag);
}

template<class FT>
Complex_without_sqrt<FT> Complex_without_sqrt<FT>::operator+(const Complex_without_sqrt<FT>& other) const{
  return Complex_without_sqrt<FT>(_real+other.real(), _imag+other.imag());
}

template<class FT>
Complex_without_sqrt<FT> Complex_without_sqrt<FT>::operator-(const Complex_without_sqrt<FT>& other) const{
  return Complex_without_sqrt<FT>(_real-other.real(), _imag-other.imag());
}

template<class FT>
Complex_without_sqrt<FT> Complex_without_sqrt<FT>::operator-() const{
  return Complex_without_sqrt<FT>(-_real, -_imag);
}

template<class FT>
Complex_without_sqrt<FT> Complex_without_sqrt<FT>::operator*(const Complex_without_sqrt<FT>& other) const{
  return Complex_without_sqrt<FT>(_real*other.real()-_imag*other.imag(), _real*other.imag()+_imag*other.real());
}

template<class FT>
Complex_without_sqrt<FT> Complex_without_sqrt<FT>::operator/(const Complex_without_sqrt<FT>& other) const{
  FT m2 = other.squared_modulus();
  return Complex_without_sqrt<FT>(_real/m2, _imag/m2)*other.conjugate();
}

////////////////////////////////////////////////////////////////////////////////

template<class FT>
bool operator==(const Complex_without_sqrt<FT>& z1, const Complex_without_sqrt<FT>& z2){
  return (z1.real()==z2.real() && z1.imag()==z2.imag());
}

template<class FT>
bool operator!=(const Complex_without_sqrt<FT>& z1, const Complex_without_sqrt<FT>& z2){
  return !operator==(z1, z2);
}

////////////////////////////////////////////////////////////////////////////////

template<class FT>
std::ostream& operator<<(std::ostream& s, const Complex_without_sqrt<FT>& z){
  s << z.real() << std::endl << z.imag() << std::endl;
  return s;
}

template<class FT>
void operator>>(std::istream& s, Complex_without_sqrt<FT>& z){
  std::string line;
  std::getline(s, line);
  z.set_real(FT(line));
  std::getline(s, line);
  z.set_imag(FT(line));
}

////////////////////////////////////////////////////////////////////////////////

template<class FT>
Complex_without_sqrt<FT> cross_ratio(Complex_without_sqrt<FT> a, Complex_without_sqrt<FT> b, Complex_without_sqrt<FT> c, Complex_without_sqrt<FT> d){
  return (d-b)*(c-a) / ((d-a)*(c-b));
}

template<class FT>
Complex_without_sqrt<FT> fourth_point_from_cross_ratio(Complex_without_sqrt<FT> a, Complex_without_sqrt<FT> b, Complex_without_sqrt<FT> c, Complex_without_sqrt<FT> cratio){
  return ( cratio*a*(c-b) + b*(a-c) ) / ( cratio*(c-b) + (a-c) );
}

} // namespace CGAL

#endif // CGAL_COMPLEX_WITHOUT_SQRT