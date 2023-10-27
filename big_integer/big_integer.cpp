#include "big_integer.hpp"

BigInt::BigInt(int64_t num) {
  if (num == 0) {
    sign_ = '0';
    PushBack(0);
  } else {
    if (num < 0) {
      sign_ = '-';
    } else if (num > 0) {
      sign_ = '+';
    }
    while (num != 0) {
      value_.push_back(std::abs(num % kTen));
      num /= kTen;
    }
    reverse(value_.begin(), value_.end());
  }
}

BigInt::BigInt(std::string str) {
  int first = 0;
  if (str[0] == '-') {
    sign_ = '-';
    if (str[1] == '0') {
      sign_ = '0';
    }
    first += 1;
  } else if (str[0] == '0') {
    sign_ = '0';
  }
  for (size_t i = first; i < str.size(); ++i) {
    PushBack(int(str[i]) - kNum);
  }
  // reverse(value_.begin(), value_.end());
}

void BigInt::Clear() {
  std::vector<int64_t> copy;
  copy.push_back(0);
  sign_ = '0';
  value_ = copy;
}

BigInt::BigInt(const BigInt& other) { *this = other; }

size_t BigInt::Size() const { return value_.size(); }

char BigInt::Sign() const { return sign_; }

void BigInt::ChangeVal(std::vector<int64_t> num) { value_ = num; }

void BigInt::DeleteZeros() {
  if (value_.size() == 1 && value_[0] == 0) {
    return;
  }
  reverse(value_.begin(), value_.end());
  while (value_[Size() - 1] == 0) {
    value_.erase(value_.end() - 1);
  }
  reverse(value_.begin(), value_.end());
}

void DeleteZeros2(std::vector<int64_t>& vec) {
  if (vec.size() == 1 && vec[0] == 0) {
    return;
  }
  reverse(vec.begin(), vec.end());
  while (vec.back() == 0) {
    vec.erase(vec.end() - 1);
  }
  reverse(vec.begin(), vec.end());
}

void BigInt::SignChange(char other_sign) { sign_ = other_sign; }

const int64_t& BigInt::operator[](size_t index) const { return value_[index]; }

int64_t& BigInt::operator[](size_t index) { return value_[index]; }

BigInt& BigInt::operator=(const BigInt& num) {
  value_ = num.value_;
  sign_ = num.sign_;
  return *this;
}

bool operator==(const BigInt& num1, const BigInt& num2) {
  if ((num1.Size() != num2.Size()) || (num1.Sign() != num2.Sign())) {
    return false;
  }
  for (size_t j = 0; j < num1.Size(); ++j) {
    if (num1[j] != num2[j]) {
      return false;
    }
  }
  return true;
}

BigInt& BigInt::operator++() {
  BigInt k_num = 1;
  return *this += k_num;
}

BigInt& BigInt::operator--() {
  BigInt k_num = 1;
  return *this -= k_num;
}

BigInt BigInt::operator++(int) {
  BigInt copy_this = *this;
  ++(*this);
  return copy_this;
}

BigInt BigInt::operator--(int) {
  BigInt copy_this = *this;
  --(*this);
  return copy_this;
}

BigInt BigInt::operator-() const {
  BigInt copy_this = *this;
  copy_this.sign_ = '-';
  return copy_this;
}

BigInt BigInt::operator/(const BigInt& div) {
  BigInt copy_this = *this;
  copy_this /= div;
  return copy_this;
}

BigInt& BigInt::operator%=(const BigInt& mod) {
  *this = *this - (*this / mod) * mod;
  return *this;
}

BigInt BigInt::operator%(const BigInt& mod) {
  BigInt copy_this = *this;
  copy_this %= mod;
  return copy_this;
}

std::ostream& operator<<(std::ostream& output, const BigInt& num) {
  if (num.Sign() == '0') {
    output << 0;
    return output;
  }
  if (num.Sign() == '-') {
    output << '-';
  }
  for (size_t j = 0; j < num.Size(); ++j) {
    output << num[j];
  }
  return output;
}

std::istream& operator>>(std::istream& input, BigInt& num) {
  std::string str;
  input >> str;
  num = BigInt(str);
  return input;
}

std::vector<int64_t> Sum(const std::vector<int64_t>& num1,
                         const std::vector<int64_t>& num2) {
  std::vector<int64_t> copy1 = num1;
  std::vector<int64_t> copy2 = num2;
  reverse(copy1.begin(), copy1.end());
  reverse(copy2.begin(), copy2.end());
  size_t mnm = std::min(copy1.size(), copy2.size());
  size_t mxm = std::max(copy1.size(), copy2.size());
  for (size_t i = mnm; i < mxm; i++) {
    if (copy1.size() > copy2.size()) {
      copy2.push_back(0);
    } else {
      copy1.push_back(0);
    }
  }
  for (size_t i = 0; i < copy1.size(); ++i) {
    copy1[i] += copy2[i];
    if (kTen <= copy1[i]) {
      if (i < copy1.size() - 1) {
        copy1[i + 1]++;
      } else {
        copy1.push_back(1);
        copy1[copy1.size() - 2] -= kTen;
        break;
      }
      copy1[i] -= kTen;
    }
  }
  reverse(copy1.begin(), copy1.end());
  return copy1;
}

std::vector<int64_t> GetMax(const std::vector<int64_t>& str1,
                            const std::vector<int64_t>& str2) {
  std::vector<int64_t> copy1 = str1;
  std::vector<int64_t> copy2 = str2;
  reverse(copy1.begin(), copy1.end());
  reverse(copy2.begin(), copy2.end());
  if (copy1.size() > copy2.size()) {
    return str1;
  }
  if (copy1.size() < copy2.size()) {
    return str2;
  }
  if (copy1.size() == copy2.size()) {
    for (size_t i = copy1.size(); i > 0; --i) {
      if (copy1[i - 1] > copy2[i - 1]) {
        return str1;
      }
      if (copy2[i - 1] > copy1[i - 1]) {
        return str2;
      }
    }
  }
  return str1;
}

std::vector<int64_t> GetMin(const std::vector<int64_t>& str1,
                            const std::vector<int64_t>& str2) {
  std::vector<int64_t> copy1 = str1;
  std::vector<int64_t> copy2 = str2;
  reverse(copy1.begin(), copy1.end());
  reverse(copy2.begin(), copy2.end());
  if (copy1.size() > copy2.size()) {
    return str2;
  }
  if (copy1.size() < copy2.size()) {
    return str1;
  }
  if (copy1.size() == copy2.size()) {
    for (size_t i = copy1.size(); i > 0; --i) {
      if (copy1[i - 1] > copy2[i - 1]) {
        return str2;
      }
      if (copy2[i - 1] > copy1[i - 1]) {
        return str1;
      }
    }
  }
  return str1;
}

bool FirstLessSecondPositive(const BigInt& num1, const BigInt& num2) {
  if (num1.Size() > num2.Size()) {
    return false;
  }
  if (num1.Size() < num2.Size()) {
    return true;
  }
  for (size_t i = 0; i < num1.Size(); ++i) {
    if (num1[i] > num2[i]) {
      return false;
    }
  }
  return true;
}

bool operator<(const BigInt& num1, const BigInt& num2) {
  if (num1 == num2) {
    return false;
  }
  if (num1.Sign() == '+' && num2.Sign() == '-') {
    return false;
  }
  if (num1.Sign() == '-' && num2.Sign() == '+') {
    return true;
  }
  if (num1.Sign() == '+' && num2.Sign() == '+') {
    return FirstLessSecondPositive(num1, num2);
  }
  return !FirstLessSecondPositive(num1, num2);
}

bool operator>(const BigInt& num1, const BigInt& num2) { return num2 < num1; }

bool operator>=(const BigInt& num1, const BigInt& num2) {
  return !(num1 < num2);
}

bool operator<=(const BigInt& num1, const BigInt& num2) {
  return !(num1 > num2);
}

bool operator!=(const BigInt& num1, const BigInt& num2) {
  return !(num1 == num2);
}

std::vector<int64_t> Prod(const std::vector<int64_t>& mul1,
                          const std::vector<int64_t>& mul2) {
  std::vector<int64_t> prod;
  for (size_t i = 0; i < mul1.size() + mul2.size(); ++i) {
    prod.push_back(0);
  }
  std::vector<int64_t> copy_mul1 = mul1;
  std::vector<int64_t> copy_mul2 = mul2;
  reverse(copy_mul1.begin(), copy_mul1.end());
  reverse(copy_mul2.begin(), copy_mul2.end());
  for (size_t i = 0; i < copy_mul1.size(); ++i) {
    size_t rem = 0;
    for (size_t j = 0; j < copy_mul2.size(); ++j) {
      int curr = copy_mul1[i] * copy_mul2[j] + rem;
      prod[i + j] += curr % kTen;
      rem = curr / kTen;
    }
    prod[i + copy_mul2.size()] += rem;
    rem = 0;
  }
  for (size_t i = 0; i < prod.size() - 1; ++i) {
    prod[i + 1] += prod[i] / kTen;
    prod[i] = prod[i] % kTen;
  }
  reverse(prod.begin(), prod.end());
  DeleteZeros2(prod);
  return prod;
}

std::vector<int64_t> Sub(const std::vector<int64_t>& sub1,
                         const std::vector<int64_t>& sub2) {
  std::vector<int64_t> copy1 = GetMax(sub1, sub2);
  std::vector<int64_t> copy2 = GetMin(sub1, sub2);
  reverse(copy1.begin(), copy1.end());
  reverse(copy2.begin(), copy2.end());
  for (size_t i = 0; i < copy2.size(); ++i) {
    if (copy1[i] < copy2[i]) {
      for (size_t j = i + 1; j < copy1.size(); ++j) {
        if (copy1[j] > 0) {
          copy1[j] -= 1;
          copy1[i] += kTen;
          for (size_t k = i + 1; k < j; ++k) {
            copy1[k] += kNine;
          }
        }
      }
    }
    copy1[i] -= copy2[i];
  }
  reverse(copy1.begin(), copy1.end());
  DeleteZeros2(copy1);
  return copy1;
}

BigInt& BigInt::operator+=(const BigInt& add) {
  if ((*this).sign_ == '0') {
    *this = add;
  } else if (sign_ == '+') {
    if (add.sign_ == '+') {
      value_ = Sum(value_, add.value_);
    } else {
      if (GetMax(value_, add.value_) == value_) {
        value_ = Sub(value_, add.value_);
      } else {
        sign_ = '-';
        value_ = Sub(add.value_, value_);
      }
    }
  } else if (sign_ == '-') {
    if (add.sign_ == '-') {
      value_ = Sum(value_, add.value_);
    } else {
      if (GetMax(value_, add.value_) != value_) {
        sign_ = '+';
      }
      value_ = Sub(add.value_, value_);
    }
  }
  return *this;
}

BigInt& BigInt::operator-=(const BigInt& sub) {
  BigInt copy_sub = sub;
  if (copy_sub.sign_ == '-') {
    copy_sub.sign_ = '+';
  } else if (copy_sub.sign_ == '+') {
    copy_sub.sign_ = '-';
  }
  *this += copy_sub;
  return *this;
}

BigInt BigInt::operator+(const BigInt& add) const {
  BigInt copy = *this;
  copy += add;
  return copy;
}

BigInt BigInt::operator-(const BigInt& sub) const {
  BigInt copy = *this;
  copy -= sub;
  return copy;
}

BigInt& BigInt::operator*=(const BigInt& mul) {
  if (*this == 0 || mul == 0) {
    (*this).Clear();
  } else {
    (*this).value_ = Prod((*this).value_, mul.value_);
    if ((*this).sign_ == mul.sign_) {
      (*this).sign_ = '+';
    } else {
      (*this).sign_ = '-';
    }
  }
  return *this;
}

BigInt BigInt::operator*(const BigInt& mul) const {
  BigInt copy = *this;
  copy *= mul;
  return copy;
}

void Div2(BigInt& delim, BigInt& chastnoe) {
  size_t tmp = 0;
  size_t index = 0;
  while (index <= delim.Size() - 1) {
    size_t current = tmp * kTen + delim[index];
    while (current <= 1) {
      if (index + 1 == delim.Size()) {
        break;
      }
      ++index;
      chastnoe.PushBack(0);
      current *= kTen;
      current += delim[index];
    }
    chastnoe.PushBack(current / 2);
    tmp = current % 2;
    ++index;
  }
}

void BinSearch(BigInt& left_pointer, BigInt& right_pointer, BigInt& delimoe,
               BigInt& delitel) {
  while (right_pointer > left_pointer + 1) {
    BigInt middle;
    BigInt sum = left_pointer + right_pointer;
    Div2(sum, middle);
    left_pointer.DeleteZeros();
    right_pointer.DeleteZeros();
    middle.DeleteZeros();
    if (delimoe >= delitel * middle) {
      left_pointer = middle;
    } else {
      right_pointer = middle;
    }
    left_pointer.DeleteZeros();
    right_pointer.DeleteZeros();
    middle.DeleteZeros();
  }
}

void BigInt::ChangeSign(const BigInt& div) {
  if (sign_ == div.sign_) {
    sign_ = '+';
  } else {
    sign_ = '-';
  }
}

BigInt& BigInt::operator/=(const BigInt& div) {
  if (div == 0) {
    std::cout << "error\n";
    exit(-1);
  }
  if (*this == 0) {
    return *this;
  }
  if (div > *this) {
    (*this).Clear();
    return *this;
  }
  BigInt delimoe = *this;
  delimoe.sign_ = '+';
  BigInt delitel = div;
  delitel.sign_ = '+';
  BigInt left_pointer(1);
  BigInt right_pointer = *this;
  BinSearch(left_pointer, right_pointer, delimoe, delitel);
  if (right_pointer * delitel == delimoe) {
    value_ = right_pointer.value_;
  } else {
    value_ = left_pointer.value_;
  }
  ChangeSign(div);
  DeleteZeros2(value_);
  return *this;
}

void BigInt::PushBack(size_t index) { value_.push_back(index); }