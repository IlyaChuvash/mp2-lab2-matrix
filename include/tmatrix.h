// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size exceeds MAX_VECTOR_SIZE");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept //Конструктор перемещения
      : sz(v.sz), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;

          pMem = new T[sz];
          for (size_t i = 0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept//Перемещающее присваивание
  {
      if (this != &v) {
          delete[] pMem;

          pMem = v.pMem;
          sz = v.sz;

          v.sz = 0;
          v.pMem = nullptr;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }
  T* data() const noexcept { return pMem; }
     
  // индексация
  T& operator[](size_t ind)
  {
      return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) {
          throw out_of_range("Out of range");
      }
      return this->pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) {
          throw out_of_range("Out of range");
      }
      return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz == v.sz) {
          for (size_t i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) {
                  return false;
              }
          }
          return true;
      }
      return false;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (this->sz == v.sz) {
          for (size_t i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) {
                  return true;
              }
          }
          return false;
      }
      return true;
  }

  // скалярные операции
  TDynamicVector operator+(T val) const
  {
	  TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] + val;
      }
      return result;
  }
  TDynamicVector operator-(T val) const
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] - val;
      }
      return result;
  }
  TDynamicVector operator*(T val) const
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] * val;
      }
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) const
  {
      if (sz != v.sz) {
          throw std::invalid_argument("Vectors sizes are not equal");
	  }
	  TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] + v.pMem[i];
      }
      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v) const
  {
      if (sz != v.sz) {
          throw std::invalid_argument("Vectors sizes are not equal");
      }
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] - v.pMem[i];
      }
      return result;
  }
  T operator*(const TDynamicVector& v) const noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw std::invalid_argument("Vectors sizes are not equal");
      }
	  T result = 0;
      for (size_t i = 0; i < sz; i++) {
          result += pMem[i] * v.pMem[i];
      }
	  return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE)
        throw std::out_of_range("Matrix size exceeds MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  using TDynamicVector<TDynamicVector<T>>::size;
  
  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if(sz == m.sz)
      {
          for (size_t i = 0; i < sz; i++) {
              for (size_t j = 0; j < sz; j++) {
                  if (pMem[i][j] != m.pMem[i][j]) {
                      return false;
                  }
              }
          }
          return true;
      }
      return false;
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
	  TDynamicMatrix<T> result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i][j] = pMem[i][j] * val;
          }
      }
	  return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) {
          throw std::invalid_argument("Matrix and vector dimensions don't match for multiplication");
	  }
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i] += pMem[i][j] * v[j];;
          }
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw std::invalid_argument("Matrix dimensions don't match for multiplication");
      }

	  TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i][j] = pMem[i][j] + m.pMem[i][j];
          }
      }
	  return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw std::invalid_argument("Matrix dimensions don't match for multiplication");
	  }

	  TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i][j] = pMem[i][j] - m.pMem[i][j];
          }
      }
	  return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw std::invalid_argument("Matrix dimensions don't match for multiplication");
      }

      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < sz; k++) {
              T temp = pMem[i][k];
              for (size_t j = 0; j < sz; j++) {
                  result[i][j] += temp * m.pMem[k][j];
              }
          }
      }
      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              istr >> m[i][j];
          }
      }
      return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              ostr << m[i][j];
              if (j < m.sz - 1) {
                  ostr << ' ';
              }
          }
          ostr << '\n';
      }
      return ostr;
  }
};

#endif
