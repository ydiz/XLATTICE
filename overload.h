////////////////////////////////////////////////////
//Matrix
///////////////////////////////////////////////////

template<typename T, int N>
inline T& Matrix<T, N>::operator()(int i, int j)
{
  return m[i][j];
}

template<typename T, int N>
inline const T& Matrix<T, N>::operator()(int i, int j) const
{
  return m[i][j];
}

// =, +=, -=, *=, /=

template<typename T, int N>
inline Matrix<T, N>& Matrix<T, N>::operator+=(const Matrix<T, N> &rhs)
{
  *this = *this + rhs;
  return *this;
}

template<typename T, int N>
inline Matrix<T, N>& Matrix<T, N>::operator-=(const Matrix<T, N> &rhs)
{
  *this = *this - rhs;
  return *this;
}

template<typename T, int N>
inline Matrix<T, N>& Matrix<T, N>::operator*=(const Matrix<T, N> &rhs)
{
  *this = *this * rhs;
  return *this;
}


template<typename T, int N>
template<typename U>
inline typename std::enable_if<isNumber<U>::value, Matrix<T, N>&>::type Matrix<T, N>::operator*=(const U& rhs)
{
  *this = *this * rhs;
  return *this;
}

template<typename T, int N>
template<typename U>
inline typename std::enable_if<isNumber<U>::value, Matrix<T, N>&>::type Matrix<T, N>::operator/=(const U& rhs)
{
  *this = *this / rhs;
  return *this;
}

// unary -
template<typename T, int N>
inline Matrix<T, N> operator-(const Matrix<T, N> &x)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = -x.m[i][j];
  return ret;
}

// +, -, *, /
template<typename T, int N>
inline Matrix<T, N> operator+(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] + m2.m[i][j];
  return ret;
}

template<typename T, int N>
inline Matrix<T, N> operator-(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] - m2.m[i][j];
  return ret;
}

template<typename T, int N>
inline Matrix<T, N> operator*(const Matrix<T, N> &m1, const Matrix<T, N> &m2)
{
  Matrix<T, N> ret;
  ret = 0;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      for(int k=0; k<N; ++k)
        ret.m[i][j] += m1.m[i][k] * m2.m[k][j];
  return ret;
}

template<typename T, int N, typename U>
inline typename std::enable_if< isNumber<U>::value, Matrix<T, N> >::type
operator*(const Matrix<T, N> &m1, const U &x)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] * x;
  return ret;
}

template<typename T, int N, typename U>
inline typename std::enable_if< isNumber<U>::value, Matrix<T, N> >::type
operator*(const U &x, const Matrix<T, N> &m1)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] * x;
  return ret;
}

template<typename T, int N, typename U>
inline typename std::enable_if< isNumber<U>::value, Matrix<T, N> >::type
operator/(const Matrix<T, N> &m1, const U &x)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = m1.m[i][j] / x;
  return ret;
}

template<typename T, int N>
std::ostream& operator<<(std::ostream &out, const Matrix<T, N> M)
{
  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<N; ++j)
      out << M.m[i][j] << " ";
    out << std::endl;
  }
  return out;
}

////////////////////////////////////////////////////
//Vector
///////////////////////////////////////////////////

template<typename T, int N>
inline T& Vector<T, N>::operator[](int i)
{
  return v[i];
}

template<typename T, int N>
inline const T& Vector<T, N>::operator[](int i) const
{
  return v[i];
}

// =, +=, -=, *=, /=

template<typename T, int N>
inline Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N> &rhs)
{
  *this = *this + rhs;
  return *this;
}

template<typename T, int N>
inline Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N> &rhs)
{
  *this = *this - rhs;
  return *this;
}


// unary -
template<typename T, int N>
inline Vector<T, N> operator-(const Vector<T, N> &x)
{
  Vector<T, N> ret;
  for(int i=0; i<N; ++i) ret.v[i] = -x.v[i];
  return ret;
}

// +, -, *, /
template<typename T, int N>
inline Vector<T, N> operator+(const Vector<T, N> &m1, const Vector<T, N> &m2)
{
  Vector<T, N> ret;
  for(int i=0; i<N; ++i) ret.v[i] = m1.v[i] + m2.v[i];
  return ret;
}

template<typename T, int N>
inline Vector<T, N> operator-(const Vector<T, N> &m1, const Vector<T, N> &m2)
{
  Vector<T, N> ret;
  for(int i=0; i<N; ++i) ret.v[i] = m1.v[i] - m2.v[i];
  return ret;
}

template<typename T, int N>
std::ostream& operator<<(std::ostream &out, const Vector<T, N> v)
{
  out << "[";
  for(const auto &x: v)
  {
    if(&x == v.end()-1)
      out << x << "]";
    else
      out << x << ", ";
  }
  return out;
}








////////////////////////////////////////////////////
//Lattice
///////////////////////////////////////////////////

template<typename T>
inline T& Lattice<T>::operator[](int i)
{
  return _data[i];
}

template<typename T>
inline const T& Lattice<T>::operator[](int i) const
{
  return _data[i];
}

// =, +=, -=, *=, /=
template<typename T>
template<typename U>
inline typename std::enable_if<isNumber<U>::value, Lattice<T>&>::type
Lattice<T>::operator=(const U &rhs)
{
  for(int i=0; i<grid.volLocal; ++i) _data[i] = rhs;
  return *this;
}

template<typename T>
template<typename U>
inline Lattice<T>& Lattice<T>::operator+=(const U &x)
{
  *this = *this + x;
  return *this;
}

template<typename T>
template<typename U>
inline Lattice<T>& Lattice<T>::operator-=(const U &x)
{
  *this = *this - x;
  return *this;
}

template<typename T>
template<typename U>
inline Lattice<T>& Lattice<T>::operator*=(const U &x)
{
  *this = *this * x;
  return *this;
}

template<typename T>
template<typename U>
inline Lattice<T>& Lattice<T>::operator/=(const U &x)
{
  *this = *this / x;
  return *this;
}

// unary -
template<typename T>
inline Lattice<T> operator-(const Lattice<T> &x)
{
  Lattice<T> ret(x.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = - x._data[i];
  return ret;
}

// +, -, *, /
template<typename T, typename U>
inline auto operator+(const Lattice<T> &l1, const Lattice<U> &l2) -> Lattice<decltype(l1._data[0] + l2._data[0])>
{
  Lattice<decltype(l1._data[0] + l2._data[0])> ret(l1.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l1._data[i] + l2._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator+(const Lattice<T> &l, const U &x) -> Lattice<decltype(l._data[0] + x)>
{
  Lattice<decltype(l._data[0] + x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l._data[i] + x;
  return ret;
}

template<typename T, typename U>
inline auto operator+(const U &x, const Lattice<T> &l) -> Lattice<decltype(l._data[0] + x)>
{
  Lattice<decltype(l._data[0] + x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = x + l._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator-(const Lattice<T> &l1, const Lattice<U> &l2) -> Lattice<decltype(l1._data[0] - l2._data[0])>
{
  Lattice<decltype(l1._data[0] - l2._data[0])> ret(l1.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l1._data[i] - l2._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator-(const Lattice<T> &l, const U &x) -> Lattice<decltype(l._data[0] - x)>
{
  Lattice<decltype(l._data[0] - x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l._data[i] - x;
  return ret;
}

template<typename T, typename U>
inline auto operator-(const U &x, const Lattice<T> &l) -> Lattice<decltype(l._data[0] - x)>
{
  Lattice<decltype(l._data[0] - x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = x - l._data[i];
  return ret;
}


template<typename T, typename U>
inline auto operator*(const Lattice<T> &l1, const Lattice<U> &l2) -> Lattice<decltype(l1._data[0] * l2._data[0])>
{
  Lattice<decltype(l1._data[0] * l2._data[0])> ret(l1.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l1._data[i] * l2._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator*(const Lattice<T> &l, const U &x) -> Lattice<decltype(l._data[0] * x)>
{
  Lattice<decltype(l._data[0] * x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l._data[i] * x;
  return ret;
}

template<typename T, typename U>
inline auto operator*(const U &x, const Lattice<T> &l) -> Lattice<decltype(x * l._data[0])>
{
  Lattice<decltype(x * l._data[0])> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = x * l._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator/(const Lattice<T> &l1, const Lattice<U> &l2) -> Lattice<decltype(l1._data[0] / l2._data[0])>
{
  Lattice<decltype(l1._data[0] / l2._data[0])> ret(l1.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l1._data[i] / l2._data[i];
  return ret;
}

template<typename T, typename U>
inline auto operator/(const Lattice<T> &l, const U &x) -> Lattice<decltype(l._data[0] / x)>
{
  Lattice<decltype(l._data[0] / x)> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = l._data[i] / x;
  return ret;
}

template<typename T, typename U>
inline auto operator/(const U &x, const Lattice<T> &l) -> Lattice<decltype(x / l._data[0])>
{
  Lattice<decltype(x / l._data[0])> ret(l.grid);
  for(int i=0; i<ret.grid.volLocal; ++i) ret._data[i] = x / l._data[i];
  return ret;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Lattice<T> &latt)
{
  const std::string delimiter = (isMatrix<T>::value) ? "\n": "\t";
  std::vector<int> gcoor(latt.grid._ndims);
  for(int i=0; i<latt.grid.volGlobal; ++i)
  {
    gcoor = latt.grid.globalIndexToGlobalCoor(i);
    out << gcoor << delimiter << peekSite(latt, gcoor) << std::endl;
  }
  return out;
}


//////////////////////////////////////
// Field
/////////////////////////////////////

template<typename T>
inline Lattice<T>& Field<T>::operator[](int i)
{
  return _data[i];
}

template<typename T>
inline const Lattice<T>& Field<T>::operator[](int i) const
{
  return _data[i];
}

// +=, -=, *=, /=
template<typename T>
template<typename U>
inline Field<T>& Field<T>::operator+=(const U &x)
{
  *this = *this + x;
  return *this;
}

template<typename T>
template<typename U>
inline Field<T>& Field<T>::operator-=(const U &x)
{
  *this = *this - x;
  return *this;
}

template<typename T>
template<typename U>
inline Field<T>& Field<T>::operator*=(const U &x)
{
  *this = *this * x;
  return *this;
}

template<typename T>
template<typename U>
inline Field<T>& Field<T>::operator/=(const U &x)
{
  *this = *this / x;
  return *this;
}

// unary -
template<typename T>
inline Field<T> operator-(const Field<T> &x)
{
  Field<T> ret;
  ret._data = - x._data;
  return ret;
}


template<typename T, typename U>
inline auto operator+(const Field<T> &l1, const Field<U> &l2) -> Field<decltype(l1._data[0][0] + l2._data[0][0])>
{
  Field<decltype(l1._data[0][0] + l2._data[0][0])> ret;
  ret._data = l1._data + l2._data;
  return ret;
}

template<typename T, typename U>
inline auto operator-(const Field<T> &l1, const Field<U> &l2) -> Field<decltype(l1._data[0][0] - l2._data[0][0])>
{
  Field<decltype(l1._data[0][0] - l2._data[0][0])> ret;
  ret._data = l1._data - l2._data;
  return ret;
}


template<typename T, typename U>
inline auto operator*(const Field<T> &l1, const Field<U> &l2) -> Field<decltype(l1._data[0][0] * l2._data[0][0])>
{
  Field<decltype(l1._data[0][0] * l2._data[0][0])> ret;
  ret._data= l1._data * l2._data;
  return ret;
}

template<typename T, typename U>
inline auto operator*(const Field<T> &l, const U &x) -> Field<decltype(l._data[0][0] * x)>
{
  Field<decltype(l._data[0][0] * x)> ret;
  ret._data = l._data * x;
  return ret;
}

template<typename T, typename U>
inline auto operator*(const U &x, const Field<T> &l) -> Field<decltype(x * l._data[0][0])>
{
  Field<decltype(x * l._data[0][0])> ret;
  ret._data = x * l._data;
  return ret;
}

template<typename T, typename U>
inline auto operator/(const Field<T> &l1, const Field<U> &l2) -> Field<decltype(l1._data[0][0] / l2._data[0][0])>
{
  Field<decltype(l1._data[0][0] / l2._data[0][0])> ret;
  ret._data = l1._data / l2._data;
  return ret;
}

template<typename T, typename U>
inline auto operator/(const Field<T> &l, const U &x) -> Field<decltype(l._data[0][0] / x)>
{
  Field<decltype(l._data[0][0] / x)> ret;
  ret._data = l._data / x;
  return ret;
}

template<typename T, typename U>
inline auto operator/(const U &x, const Field<T> &l) -> Field<decltype(x / l._data[0][0])>
{
  Field<decltype(l._data[0][0] / x)> ret;
  ret._data = x / l._data;
  return ret;
}


template<typename  T>
std::ostream& operator<<(std::ostream& out, Field<T> field)
{
  for(int i=0; i<Nd; ++i)
  {
    std::cout << "===================== " << "mu = " << i << "  =====================" << std::endl << '\n';
    std::cout << field._data[i];
  }
  return out;
}
