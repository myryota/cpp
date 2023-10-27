#include "string.hpp"

using namespace constants;

String::String() {
  s_ = new char[1];
  s_[0] = '\0';
  size_ = 0;
  capacity_ = 0;
}

String::~String() { delete[] s_; }

String::String(size_t size, char character)
    : s_(new char[size + 1]), size_(size), capacity_(size) {
  memset(s_, character, size);
  s_[size] = '\0';
}

String::String(const char* str) {
  size_ = strlen(str);
  capacity_ = size_;
  s_ = new char[capacity_ + 1];
  for (size_t j = 0; j < size_; ++j) {
    s_[j] = str[j];
  }
  s_[size_] = '\0';
}

String::String(const String& str) {
  capacity_ = str.capacity_;
  size_ = str.size_;
  s_ = new char[capacity_ + 1];
  memcpy(s_, str.s_, size_);
  s_[size_] = '\0';
}

String& String::operator=(const String& str) {
  if (&str == this) {
    return *this;
  }
  delete[] s_;
  capacity_ = str.capacity_;
  size_ = str.size_;
  s_ = new char[capacity_ + 1];
  memcpy(s_, str.s_, size_);
  s_[size_] = '\0';
  return *this;
}

void String::Clear() { size_ = 0; }

void String::PushBack(char character) {
  if (size_ == capacity_) {
    Reserve(2 * size_);
  }
  s_[size_] = character;
  size_ += 1;
  s_[size_] = '\0';
}

void String::PopBack() {
  if (size_ > 0) {
    size_ -= 1;
    s_[size_] = '\0';
  }
}

void String::Resize(size_t new_size) {
  if (capacity_ < new_size) {
    Reserve(new_size);
  }
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  size_t size = size_;
  Resize(new_size);
  for (size_t k = size; k <= new_size - 1; ++k) {
    s_[k] = character;
  }
  s_[size] = '\0';
}

void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    char* str = new char[new_cap + 1];
    strcpy(str, s_);
    delete[] s_;
    capacity_ = new_cap;
    s_ = str;
  } else if (capacity_ == 0) {
    delete[] s_;
    s_ = new char[kNan];
    capacity_ = kNan;
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    char* str = new char[size_ + 1];
    strcpy(str, s_);
    delete[] s_;
    s_ = str;
  }
}

void String::Swap(String& other) {
  std::swap(s_, other.s_);
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
}

const char& String::operator[](size_t index) const { return s_[index]; }

char& String::operator[](size_t index) { return s_[index]; }

const char& String::Front() const { return s_[0]; }

char& String::Front() { return s_[0]; }

const char& String::Back() const { return s_[size_ - 1]; }

char& String::Back() { return s_[size_ - 1]; }

bool String::Empty() const { return size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

char* String::Data() { return &s_[0]; }

const char* String::Data() const { return &s_[0]; }

bool operator<(const String& str1, const String& str2) {
  return strcmp(str1.Data(), str2.Data()) < 0;
}

bool operator>(const String& str1, const String& str2) {
  return strcmp(str1.Data(), str2.Data()) > 0;
}

bool operator==(const String& str1, const String& str2) {
  return strcmp(str1.Data(), str2.Data()) == 0;
}

bool operator!=(const String& str1, const String& str2) {
  return strcmp(str1.Data(), str2.Data()) != 0;
}

bool operator<=(const String& str1, const String& str2) {
  return !(str1 > str2);
}

bool operator>=(const String& str1, const String& str2) {
  return !(str1 < str2);
}

String& String::operator+=(const String& str) {
  Reserve(str.Size() + size_);
  Resize(capacity_);
  strcat(s_, str.Data());
  return *this;
}

String operator+(const String& str1, const String& str2) {
  String str = str1;
  str += str2;
  return str;
}

String String::operator*(size_t num) const {
  if (num == 0) {
    return String();
  }
  String str = *this;
  str.Reserve(str.Size() * num);
  for (size_t j = 0; j < num - 1; ++j) {
    for (size_t i = 0; i < size_; ++i) {
      str.PushBack(s_[i]);
    }
  }
  return str;
}

String& String::operator*=(size_t num) {
  *this = *this * num;
  return *this;
}

std::istream& operator>>(std::istream& inn, String& str) {
  char chr;
  while (inn >> chr and std::isspace(chr) == 0) {
    str.PushBack(chr);
  }
  return inn;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  for (size_t i = 0; i < str.Size(); i++) {
    out << str[i];
  }
  return out;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> answer;
  char* res = s_;
  char* str = Strstr(res, delim.Data());
  char* tmp = new char[Size()];
  while (str != nullptr) {
    strncpy(tmp, res, str - res);
    tmp[str - res] = '\0';
    answer.push_back(String(tmp));
    res = str + delim.Size();
    str = Strstr(res, delim.Data());
  }
  answer.push_back(String(res));
  delete[] tmp;
  return answer;
}

String String::Join(const std::vector<String>& strings) const {
  if (strings.empty()) {
    return String();
  }
  String str = strings[0];
  for (size_t j = 1; j < strings.size(); ++j) {
    str += (*this + strings[j]);
  }
  return str;
}

char* Strstr(char* str1, const char* str2) {
  while (*str1 != '\0') {
    if ((*str1 == *str2) && Compare(str1, str2)) {
      return str1;
    }
    str1 += 1;
  }
  return nullptr;
}

bool Compare(const char* str1, const char* str2) {
  while (*str1 != 0 && *str2 != 0) {
    if (*str1 != *str2) {
      return false;
    }
    str2 += 1;
    str1 += 1;
  }
  return (*str2 == '\0');
}