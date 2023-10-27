#include <algorithm>
#include <iostream>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix();
  Matrix(std::vector<std::vector<T>> vec);
  Matrix(T elem);
  Matrix<N, M, T>& operator+=(const Matrix<N, M, T>& matrix);
  Matrix<N, M, T>& operator-=(const Matrix<N, M, T>& matrix);
  Matrix<N, M, T> operator+(const Matrix<N, M, T>& matrix);
  Matrix<N, M, T> operator-(const Matrix<N, M, T>& matrix);
  Matrix<N, M, T> operator*(const T& elem);
  Matrix<M, N, T> Transposed();
  T& operator()(size_t index_i, size_t index_j);
  const T& operator()(size_t index_i, size_t index_j) const;
  bool operator==(const Matrix<N, M, T>& matrix);
  template <size_t L>
  Matrix<N, L, T> operator*(const Matrix<M, L, T>& matrix);

 private:
  std::vector<std::vector<T>> MyMatrix_;
};

template <size_t N, typename T>
class Matrix<N, N, T> {
 public:
  Matrix();
  Matrix(std::vector<std::vector<T>> vec);
  Matrix(T elem);
  Matrix<N, N, T>& operator+=(const Matrix<N, N, T>& matrix);
  Matrix<N, N, T>& operator-=(const Matrix<N, N, T>& matrix);
  Matrix<N, N, T> operator+(const Matrix<N, N, T>& matrix);
  Matrix<N, N, T> operator-(const Matrix<N, N, T>& matrix);
  Matrix<N, N, T> operator*(const T& elem);
  Matrix<N, N, T> Transposed();
  T& operator()(size_t index_i, size_t index_j);
  const T& operator()(size_t index_i, size_t index_j) const;
  bool operator==(const Matrix<N, N, T>& matrix);
  template <size_t L>
  Matrix<N, L, T> operator*(const Matrix<N, L, T>& matrix);
  T Trace();

 private:
  std::vector<std::vector<T>> MyMatrix_;
};

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix() {
  //  MyMatrix_.resize(N);
  for (size_t i = 0; i < N; ++i) {
    MyMatrix_.push_back(std::vector<T>(M));
  }
}

template <size_t N, typename T>
Matrix<N, N, T>::Matrix() {
  //  MyMatrix_.resize(N);
  for (size_t i = 0; i < N; ++i) {
    MyMatrix_.push_back(std::vector<T>(N));
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(std::vector<std::vector<T>> vec) {
  for (size_t i = 0; i < N; ++i) {
    MyMatrix_.push_back(std::vector<T>(M));
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < M; ++ii) {
      MyMatrix_[i][ii] = vec[i][ii];
    }
  }
}

template <size_t N, typename T>
Matrix<N, N, T>::Matrix(std::vector<std::vector<T>> vec) {
  for (size_t i = 0; i < N; ++i) {
    MyMatrix_.push_back(std::vector<T>(N));
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < N; ++ii) {
      MyMatrix_[i][ii] = vec[i][ii];
    }
  }
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(T elem) {
  for (size_t i = 0; i < N; ++i) {
    MyMatrix_.push_back(std::vector<T>(M));
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < M; ++ii) {
      MyMatrix_[i][ii] = elem;
    }
  }
}

template <size_t N, typename T>
Matrix<N, N, T>::Matrix(T elem) {
  for (size_t i = 0; i < N; ++i) {
    MyMatrix_.push_back(std::vector<T>(N));
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < N; ++ii) {
      MyMatrix_[i][ii] = elem;
    }
  }
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t index_i, size_t index_j) {
  return MyMatrix_[index_i][index_j];
}

template <size_t N, typename T>
T& Matrix<N, N, T>::operator()(size_t index_i, size_t index_j) {
  return MyMatrix_[index_i][index_j];
}

template <size_t N, size_t M, typename T>
const T& Matrix<N, M, T>::operator()(size_t index_i, size_t index_j) const {
  return MyMatrix_[index_i][index_j];
}

template <size_t N, typename T>
const T& Matrix<N, N, T>::operator()(size_t index_i, size_t index_j) const {
  return MyMatrix_[index_i][index_j];
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < M; ++ii) {
      MyMatrix_[i][ii] += matrix(i, ii);
    }
  }
  return *this;
}

template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator+=(const Matrix<N, N, T>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < N; ++ii) {
      MyMatrix_[i][ii] += matrix(i, ii);
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator+(const Matrix<N, M, T>& matrix) {
  Matrix<N, M, T> copy_this = *this;
  copy_this += matrix;
  return copy_this;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator+(const Matrix<N, N, T>& matrix) {
  Matrix<N, N, T> copy_this = *this;
  copy_this += matrix;
  return copy_this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix<N, M, T>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < M; ++ii) {
      MyMatrix_[i][ii] -= matrix(i, ii);
    }
  }
  return *this;
}

template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator-=(const Matrix<N, N, T>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < N; ++ii) {
      MyMatrix_[i][ii] -= matrix(i, ii);
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator-(const Matrix<N, M, T>& matrix) {
  Matrix<N, M, T> copy_this = *this;
  copy_this -= matrix;
  return copy_this;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator-(const Matrix<N, N, T>& matrix) {
  Matrix<N, N, T> copy_this = *this;
  copy_this -= matrix;
  return copy_this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator*(const T& elem) {
  Matrix<N, M, T> copy_this = *this;
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < M; ++ii) {
      copy_this(i, ii) *= elem;
    }
  }
  return copy_this;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator*(const T& elem) {
  Matrix<N, N, T> copy_this = *this;
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < N; ++ii) {
      copy_this(i, ii) *= elem;
    }
  }
  return copy_this;
}

template <size_t N, size_t M, typename T>
bool Matrix<N, M, T>::operator==(const Matrix<N, M, T>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < M; ++ii) {
      if (matrix(i, ii) != MyMatrix_[i][ii]) {
        return false;
      }
    }
  }
  return true;
}

template <size_t N, typename T>
bool Matrix<N, N, T>::operator==(const Matrix<N, N, T>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < N; ++ii) {
      if (matrix(i, ii) != MyMatrix_[i][ii]) {
        return false;
      }
    }
  }
  return true;
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() {
  Matrix<M, N, T> matrix_t;
  for (size_t i = 0; i < M; ++i) {
    for (size_t ii = 0; ii < N; ++ii) {
      matrix_t(i, ii) = MyMatrix_[ii][i];
    }
  }
  return matrix_t;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::Transposed() {
  Matrix<N, N, T> matrix_t;
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < N; ++ii) {
      matrix_t(i, ii) = MyMatrix_[ii][i];
    }
  }
  return matrix_t;
}

template <size_t N, size_t M, typename T>
template <size_t L>
Matrix<N, L, T> Matrix<N, M, T>::operator*(const Matrix<M, L, T>& matrix) {
  Matrix<N, L, T> product;
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < L; ++ii) {
      for (size_t j = 0; j < M; ++j) {
        product += MyMatrix_[i][j] * matrix(j, ii);
      }
    }
  }
  return product;
}

template <size_t N, typename T>
template <size_t L>
Matrix<N, L, T> Matrix<N, N, T>::operator*(const Matrix<N, L, T>& matrix) {
  Matrix<N, L, T> product;
  for (size_t i = 0; i < N; ++i) {
    for (size_t ii = 0; ii < L; ++ii) {
      for (size_t j = 0; j < N; ++j) {
        product(i, ii) += MyMatrix_[i][j] * matrix(j, ii);
      }
    }
  }
  return product;
}

template <size_t N, typename T>
T Matrix<N, N, T>::Trace() {
  T trace;
  for (size_t i = 0; i < N; ++i) {
    trace += MyMatrix_[i][i];
  }
  return trace;
}
