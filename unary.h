#ifndef XLATTICE_UNARY_H
#define XLATTICE_UNARY_H

// unary: adj, sum, trace, real
///////////////////
// adj
///////////////////
template<typename T, int N>
inline Matrix<T, N> adj(const Matrix<T, N> &mat)
{
  Matrix<T, N> ret;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = std::conj(mat.m[j][i]);
  return ret;
}

template<typename T>
inline Lattice<T> adj(const Lattice<T> &lat)
{
  Lattice<T> ret(lat.grid);
  for(int i=0; i<lat.grid.volLocal; ++i) ret._data[i] = adj(lat._data[i]);
  return ret;
}

template<typename T, int N>
inline Field<T, N> adj(const Field<T, N> &U)
{
  Field<T, N> ret;
  for(int i=0; i<N; ++i) ret._data[i] = adj(U._data[i]);
  return ret;
}

///////////////////
// trace
///////////////////
template<typename T, int N>
inline T trace(const Matrix<T, N> &mat)
{
  T ret = 0;
  for(int i=0; i<N; ++i) ret += mat.m[i][i];
  return ret;
}

template<typename T>
inline auto trace(const Lattice<T> &lat) -> Lattice<decltype(trace(lat[0]))>
{
  Lattice<decltype(trace(lat[0]))> ret(lat.grid);
  for(int i=0; i<lat.grid.volLocal; ++i) ret._data[i] = trace(lat._data[i]);
  return ret;
}

template<typename T, int N>
inline auto trace(const Field<T, N>& U) -> Field<decltype(trace(U[0][0])), N>
{
  Field<decltype(trace(U[0][0])), N> ret;
  for(int i=0; i<N; ++i) ret._data[i] = trace(U._data[i]);
  return ret;
}

///////////////////
// sum
///////////////////

template<typename T>
inline T sum(const Lattice<T>& lat)
{
  T ret;
  for(int i=0; i<lat.grid.volLocal; ++i) ret += lat._data[i];
  ret = lat.grid.sumMPI(ret); // sum over processes
  return ret;
}

template<typename T, int N>
inline T sum(const Field<T, N>& U)
{
  T ret;
  for(int mu=0; mu<N; ++mu) ret += sum(U._data[mu]);
  return ret;
}

///////////////////
// real
///////////////////
template<typename T, int N>
inline auto real(const Matrix<T, N> &mat) -> Matrix<decltype(real(mat(0,0))), N>
{
  Matrix<decltype(real(mat(0,0))), N> ret = 0;
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      ret.m[i][j] = real(mat.m[i][j]);
  return ret;
}

template<typename T>
inline auto real(const Lattice<T> &lat) -> Lattice<decltype(real(lat[0]))>
{
  Lattice<decltype(real(lat[0]))> ret(lat.grid);
  for(int i=0; i<lat.grid.volLocal; ++i)
  {
    ret._data[i] = real(lat._data[i]);
  }

  return ret;
}

template<typename T, int N>
inline auto real(const Field<T, N>& U) -> Field<decltype(real(U[0][0])), N>
{
  Field<decltype(real(U[0][0])), N> ret;
  for(int i=0; i<N; ++i) ret._data[i] = real(U._data[i]);
  return ret;
}

#endif
