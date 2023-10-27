#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class BigInt {
 public:
  BigInt() = default;

  BigInt& operator=(const BigInt& num);

  ~BigInt() = default;

  BigInt(int64_t num);

  BigInt(std::string str);

  void Clear();

  size_t Size() const;

  char Sign() const;

  BigInt(const BigInt& other);

  int64_t& operator[](size_t index);

  const int64_t& operator[](size_t index) const;

  void ChangeVal(std::vector<int64_t> num);

  void DeleteZeros();

  void SignChange(char other_sign);

  void PushBack(size_t index);

  void ChangeSign(const BigInt& div);

  BigInt& operator+=(const BigInt& add);
  BigInt& operator-=(const BigInt& sub);
  BigInt& operator*=(const BigInt& mul);
  BigInt& operator/=(const BigInt& div);
  BigInt& operator%=(const BigInt& mod);

  BigInt operator+(const BigInt& add) const;
  BigInt operator-(const BigInt& sub) const;
  BigInt operator*(const BigInt& mul) const;
  BigInt operator/(const BigInt& div);
  BigInt operator%(const BigInt& mod);

  BigInt& operator++();
  BigInt& operator--();
  BigInt operator++(int);
  BigInt operator--(int);

  BigInt operator-() const;

 private:
  std::vector<int64_t> value_;
  char sign_ = '+';
};

void DeleteZeros2(std::vector<int64_t>& vec);
void Div2(BigInt& delim, BigInt& chastnoe);

void BinSearch(BigInt& left_pointer, BigInt& right_pointer, BigInt& delimoe,
               BigInt& delitel);
std::vector<int64_t> Sum(const std::vector<int64_t>& num1,
                         const std::vector<int64_t>& num2);
std::vector<int64_t> Prod(const std::vector<int64_t>& mul1,
                          const std::vector<int64_t>& mul2);
std::vector<int64_t> Sub(const std::vector<int64_t>& sub1,
                         const std::vector<int64_t>& sub2);

std::vector<int64_t> GetMax(const std::vector<int64_t>& str1,
                            const std::vector<int64_t>& str2);
std::vector<int64_t> GetMin(const std::vector<int64_t>& str1,
                            const std::vector<int64_t>& str2);

bool FirstLessSecondPositive(const BigInt& num1, const BigInt& num2);

bool operator<(const BigInt& num1, const BigInt& num2);
bool operator==(const BigInt& num1, const BigInt& num2);
bool operator!=(const BigInt& num1, const BigInt& num2);
bool operator<=(const BigInt& num1, const BigInt& num2);
bool operator>=(const BigInt& num1, const BigInt& num2);
bool operator>(const BigInt& num1, const BigInt& num2);

std::istream& operator>>(std::istream& input, BigInt& num);
std::ostream& operator<<(std::ostream& output, const BigInt& num);

static const int64_t kTen = 10;
static const int64_t kNum = 48;
static const int64_t kNine = 9;
