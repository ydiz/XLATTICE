Take types as arguments or returns -- use class template

Don't forget `typename` before `std::enable_if<>::type`

use `typename std::enable_if` on return types; do not use it on arguments. Otherwise T cannot be deduced.

```
template<int N>
template<typename T>
typename std::enable_if<isNumber<T>::value, Matrix<N>>::type Matrix<N>::operator=(T x)
{
  for(int i=0; i<N; ++i) m[i][i] = x;
}
```

----

## specialization of class template

```
template<typename T>
struct isNumber{
  static const bool value = std::is_arithmetic<T>::value; // integral or float-point number
};

template<typename T>
 struct isNumber<std::complex<T>>{
  static const bool value = true;
};

```

the second part is not redefinition. the <xxx> after class name indicates it is a template specialization.

----
template member function in template class. use two `template`

```
template<int N>
class Matrix{
    Complex m[N][N];
public:
  template<typename T>
  typename std::enable_if<isNumber<T>::value, Matrix<N>>::type operator=(T x);
};

template<int N>
template<typename T>
typename std::enable_if<isNumber<T>::value, Matrix<N>>::type Matrix<N>::operator=(T x)
{
  for(int i=0; i<N; ++i) m[i][i] = x;
}
```

---

## template functions and ordinary functions overload
e.g.

```
template<typename T> T sqrt(T);
template<typename T> complex<T> sqrt(complex<T>);
double sqrt(double);

void f(complex<double> z)
{
sqrt(2); // sqrt<int>(int)
sqrt(2.0); // sqrt(double)
sqrt(z); // sqrt<double>(complex<double>)
}
```

overload resolution:  
1. Choose available template functions, and **find the most specialized one**. (e.g. For sqrt(z), `complex<T> sqrt(complex<T>)` is prefered over `T sqrt(T)` )
2. Do overload resolution for these most specialized **template function specializations + ordinary functions**. (e.g. For sqrt(2), compare `sqrt<int>(int)` and `sqrt(double)`, the first one is an exact match and is prefered)
3. If a function and a specialization are equally good match, the function is prefered. (e.g. For sqrt(6.0), compare`sqrt<double>(double)` and `sqrt(double)`, both are good match. Choose the ordinary function)


----

SFINAE: substitution failure is not an error.  
It only causes the template to be ignored; that is, the template doesn't contribute a specialization to the overload set.


---

use a type defined in the public section of a template class, need `typename` keyword


---

## user-defined specializations
### Complete specialization:
```
template<typename T> struct isComplex {
  static const bool value = false;
};
template<> struct isComplex<ComplexF> {
  static const bool value = true;
};
template<> struct isComplex<ComplexD> {
  static const bool value = true;
};
```

`typename<>` indicates this is a complete specialization. All template parameters are specified.

### partial specialization

```
template<typename T, int N>
class Matrix; // N-dimensional Matrix of Ts

template<typename T>
class Matrix<T,0> { // specialization for N==1
T val;
};

template<typename T>
class Matrix<T,0> { // specialization for N=1
T∗ elem;
int sz; // number of elements
};

template<typename T>
class Matrix<T,2> { // specialization for N=2
T∗ elem;
int dim1; // number of rows
int dim2; // number of columns
};

```
