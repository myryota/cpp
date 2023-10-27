#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

namespace constants {
const int kNan = 1000;
}  // namespace constants

class String {
 public:
  String();
  ~String();
  explicit String(size_t size, char character);
  String(const char* str);
  String(const String& str);
  String& operator=(const String& str);
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  const char& operator[](size_t index) const;
  char& operator[](size_t index);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  char* Data();
  const char* Data() const;

  String& operator+=(const String& str);
  String operator*(size_t num) const;
  String& operator*=(size_t num);
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings) const;

 private:
  char* s_;
  size_t size_ = 0;
  size_t capacity_ = 0;
};

std::istream& operator>>(std::istream& inn, String& str);
std::ostream& operator<<(std::ostream& out, const String& str);

bool operator<(const String& str1, const String& str2);
bool operator>(const String& str1, const String& str2);
bool operator!=(const String& str1, const String& str2);
bool operator==(const String& str1, const String& str2);
bool operator<=(const String& str1, const String& str2);
bool operator>=(const String& str1, const String& str2);

String operator+(const String& str1, const String& str2);
char* Strstr(char* str1, const char* str2);
bool Compare(const char* str1, const char* str2);
