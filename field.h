#ifndef XField_FIELD_H
#define XField_FIELD_H

static const int Nd = 4;
// fermion field, put color index to Field, spin index to vector
template<typename T>
class Field{
public:
  std::vector<Lattice<T>> _data;
  Cartesian grid;

  Field();
  Field(const Cartesian& grid);
  template<typename U> Field(const U& x);

  template<typename U>  Field& operator+=(const U& x);
  template<typename U>  Field& operator-=(const U& x);
  template<typename U>  Field& operator*=(const U& x);
  template<typename U>  Field& operator/=(const U& x);

  Lattice<T>& operator[](int i);
  const Lattice<T>& operator[](int i) const;
};

// constructors
template<typename T>
Field<T>::Field() : _data(Nd) { grid = _data[0].grid; }

template<typename T>
Field<T>::Field(const Cartesian &_grid) : _data(Nd, Lattice<T>{_grid}) { grid = _data[0].grid; }

template<typename T>
template<typename U>
Field<T>::Field(const U& x) : _data(Nd)
{
  for(auto &data_i:  _data) data_i = x;
  grid = _data[0].grid;
}


using GaugeField = Field< Matrix<Complex, 3> >;
using RealField = Field< double >;
using ComplexField = Field< Complex >;

#endif
