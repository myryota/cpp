#include <iostream>
#include <vector>

const size_t kArrsize = 16;
template <typename T, typename Allocator = std::allocator<T>>
class Deque {
  Allocator alloc_;
  size_t arrnum_ = kArrsize;
  std::vector<T*> array_;
  size_t get_middle() { return (arrnum_ - 1) / 2; }

  size_t get_num_of_blocks(size_t count) { return (count / kArrsize + 1) * 2; }

  void insert() {
    if (end_.iter.second == 0) {
      if (end_.iter.first == arrnum_) {
        size_t idx = 0;
        size_t add_size = end_.iter.first - begin_.iter.first;
        arrnum_ = arrnum_ + add_size + 1;
        while (idx <= add_size) {
          array_.insert(array_.end(), 1, traits::allocate(alloc_, kArrsize));
          ++idx;
        }
      }
    }
  }

  void innerinsert() {
    if (begin_.iter.second == 0) {
      if (begin_.iter.first == 0) {
        size_t idx = 0;
        size_t add_size = end_.iter.first - begin_.iter.first;
        while (idx <= add_size) {
          array_.insert(array_.end(), 1, traits::allocate(alloc_, kArrsize));
          idx++;
        }
        end_.iter.first += add_size + 1;
        begin_.iter.first += add_size + 1;
        arrnum_ += add_size + 1;
      }
    }
  }
  void clear() {
    auto itу = this->begin();
    auto itr = array_.begin();
    while (itу != this->end()) {
      traits::destroy(alloc_, &(*itу));
      ++itу;
    }
    while (itr != array_.end()) {
      traits::deallocate(alloc_, *itr, kArrsize);
      ++itr;
    }
  }

 public:
  Allocator get_allocator() { return alloc_; }
  using traits = std::allocator_traits<Allocator>;
  ~Deque() { clear(); }
  void memory_init(const Allocator& allocator = Allocator()) {
    alloc_ = allocator;
    try {
      size_t index = 0;
      while (index < arrnum_) {
        array_[index] = traits::allocate(alloc_, kArrsize);
        index++;
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  Deque(size_t count, const Allocator& allocator = Allocator())
      : begin_(get_middle(), 0, this),
        end_(get_middle(), 0, this),
        array_(arrnum_),
        arrnum_(get_num_of_blocks(count)) {
    try {
      memory_init(allocator);
      size_t ind = 1;
      while (ind <= count) {
        traits::construct(alloc_, &array_[end_.iter.first][end_.iter.second]);
        ++end_;
        ind++;
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  Deque(size_t count, const T& value, const Allocator& allocator = Allocator())
      : begin_(get_middle(), 0, this),
        end_(get_middle(), 0, this),
        array_(arrnum_),
        arrnum_(get_num_of_blocks(count)) {
    try {
      memory_init(allocator);
      size_t ind = 1;
      while (ind <= count) {
        traits::construct(alloc_, &array_[end_.iter.first][end_.iter.second],
                          value);
        ++end_;
        ind++;
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  void swap(const Deque& other) {
    Deque tmp(std::move(other));
    if (traits::propagate_on_container_copy_assignment::value and
        tmp.alloc_ != other.alloc_) {
      tmp.alloc_ = other.alloc_;
    }
    std::swap(alloc_, tmp.alloc_);
    std::swap(begin_, tmp.begin_);
    std::swap(arrnum_, tmp.arrnum_);
    std::swap(end_, tmp.end_);
    std::swap(array_, tmp.array_);
    begin_.array = this;
    end_.array = this;
  }

  Deque(std::initializer_list<T> init, const Allocator& allocator = Allocator())
      : arrnum_(init.size()),
        end_(get_middle(), 0, this),
        begin_(get_middle(), 0, this),
        array_(arrnum_) {
    try {
      auto iter = init.begin();
      memory_init(allocator);
      while (iter != init.end()) {
        traits::construct(alloc_, &array_[end_.iter.first][end_.iter.second],
                          *iter);
        ++end_;
        ++iter;
      }
    } catch (...) {
      clear();
      throw;
    }
  }
  Deque(const Allocator& allocator = Allocator())
      : end_(get_middle(), 0, this),
        begin_(get_middle(), 0, this),
        array_(arrnum_) {
    memory_init(allocator);
  }
  Deque(const Deque& other)
      : arrnum_(other.arrnum_),
        begin_(get_middle(), 0, this),
        end_(get_middle(), 0, this),
        array_(arrnum_) {
    try {
      size_t ind = 0;
      memory_init(traits::select_on_container_copy_construction(other.alloc_));
      while (ind < other.size()) {
        traits::construct(alloc_, &array_[end_.iter.first][end_.iter.second],
                          other[ind]);
        ++end_;
        ++ind;
      }
    } catch (...) {
      clear();
      throw;
    }
  }

  Deque& operator=(const Deque& other) {
    swap(other);
    return *this;
  }

  Deque(Deque&& other)
      : array_(std::move(other.array_)),
        begin_(std::move(other.begin_)),
        end_(std::move(other.end_)),
        arrnum_(std::move(other.arrnum_)),
        alloc_(std::move(other.alloc_)) {
    other.end_ = {get_middle(), 0, &other};
    end_.array = this;
    other.begin_ = {get_middle(), 0, &other};
    begin_.array = this;
  }

  Deque& operator=(Deque&& other) noexcept {
    Deque tmp = std::move(other);
    *this = tmp;
    return *this;
  }

  size_t size() const {
    return (end_.iter.first - begin_.iter.first - 1) * kArrsize + kArrsize -
        begin_.iter.second + end_.iter.second;
  }

  bool empty() const { return size() == 0; };

  T& operator[](size_t index) { return *(begin_ + index); }

  const T& operator[](size_t index) const { return *(begin_ + index); }
  const T& at(size_t index) const {
    if (index < size()) {
      return this->operator[](index);
    }
    throw std::out_of_range("out of deque");
  }

  T& at(size_t index) {
    if (index < size()) {
      return this->operator[](index);
    }
    throw std::out_of_range("out of deque");
  }

  void push_back(const T& value) {
    insert();
    traits::construct(alloc_, array_[end_.iter.first] + end_++.iter.second,
                      value);
  }

  void push_back(T&& value) {
    insert();
    traits::construct(alloc_, &array_[end_.iter.first][end_.iter.second],
                      std::forward<T>(value));
    ++end_;
  }

  template <class... Args>
  void emplace_back(Args&&... args) {
    insert();
    traits::construct(alloc_, array_[end_.iter.first] + end_++.iter.second,
                      std::forward<Args>(args)...);
  }

  template <class... Args>
  void emplace_front(Args&&... args) {
    insert();
    --begin_;
    traits::construct(alloc_, array_[begin_.iter.first] + begin_.iter.second,
                      std::forward<Args>(args)...);
  }

  void push_front(const T& value) {
    innerinsert();
    --begin_;
    traits::construct(alloc_, array_[begin_.iter.first] + begin_.iter.second,
                      value);
  }

  void push_front(T&& value) {
    innerinsert();
    --begin_;
    traits::construct(alloc_, array_[begin_.iter.first] + begin_.iter.second,
                      std::forward<T>(value));
  }

  void pop_front() {
    traits::destroy(alloc_, array_[begin_.iter.first] + begin_.iter.second);
    ++begin_;
  }

  void pop_back() {
    traits::destroy(alloc_, &array_[end_.iter.first][end_.iter.second]);
    --end_;
  }

  template <bool IsConst>
  struct CommonIterator {
    operator CommonIterator<true>() const {
      return CommonIterator<true>(iter.first, iter.second);
    }

    using difference_type = std::ptrdiff_t;
    using value_type = typename std::conditional<IsConst, const T, T>::type;
    using iterator_category = std::random_access_iterator_tag;
    using pointer = typename std::conditional<IsConst, const T*, T*>::type;
    using reference = typename std::conditional<IsConst, const T&, T&>::type;

    CommonIterator(size_t array, size_t index) {
      iter.second = index;
      iter.first = array;
    }

    CommonIterator(size_t array, size_t index, Deque<T, Allocator>* container)
        : array(container) {
      iter.second = index;
      iter.first = array;
    }

    CommonIterator& operator++() {
      if (iter.second != kArrsize - 1) {
        ++iter.second;
        return *this;
      }
      iter.second = 0;
      ++iter.first;
      return *this;
    }

    CommonIterator& operator--() {
      if (iter.second != 0) {
        --iter.second;
        return *this;
      }
      iter.second = kArrsize - 1;
      --iter.first;
      return *this;
    }

    CommonIterator& operator-=(size_t copy) {
      *this += (-copy);
      return *this;
    }

    CommonIterator operator--(int) {
      CommonIterator copy = *this;
      operator--();
      return copy;
    }

    CommonIterator operator++(int) {
      CommonIterator res = *this;
      operator++();
      return res;
    }

    CommonIterator& operator+=(size_t size) {
      iter.first = (iter.first * kArrsize + iter.second + size) / kArrsize;
      iter.second = (iter.second + size) % kArrsize;
      return *this;
    }

    CommonIterator operator+(size_t size) const {
      CommonIterator copy = *this;
      copy += size;
      return copy;
    }

    bool operator<(const CommonIterator& rhs) const {
      return (iter.first == rhs.iter.first && iter.second < rhs.iter.second) ||
          (iter.first < rhs.iter.first);
    }

    bool operator>(const CommonIterator& rhs) const { return rhs < *this; }

    bool operator==(const CommonIterator& rhs) const {
      return *this >= rhs && *this <= rhs;
    }
    bool operator>=(const CommonIterator& rhs) const { return !(*this < rhs); }

    bool operator!=(const CommonIterator& rhs) const { return !(*this == rhs); }

    bool operator<=(const CommonIterator& rhs) const { return !(*this > rhs); }

    difference_type operator-(const CommonIterator& rhs) {
      return (iter.first - rhs.iter.first - 1) * kArrsize + kArrsize -
          rhs.iter.second + iter.second;
    }

    reference operator*() {
      return *((array->array_)[iter.first] + iter.second);
    }

    pointer operator->() const {
      return ((array->array_)[iter.first] + iter.second);
    }

    CommonIterator operator-(size_t size) const {
      CommonIterator copy = *this;
      copy -= size;
      return copy;
    }

    std::pair<size_t, size_t> iter;
    Deque<T, Allocator>* array;
  };
  using iterator = CommonIterator<false>;

  iterator begin() { return begin_; }

  CommonIterator<true> begin() const { return begin_; }

  iterator end() { return end_; }

  using const_iterator = CommonIterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  CommonIterator<true> end() const { return end_; }

  CommonIterator<true> cbegin() const { return begin_; }

  CommonIterator<true> cend() const { return end_; }

  std::reverse_iterator<iterator> rbegin() {
    return std::make_reverse_iterator(end());
  }

  std::reverse_iterator<const_iterator> rbegin() const {
    return std::make_reverse_iterator(end());
  }

  std::reverse_iterator<iterator> rend() {
    return std::make_reverse_iterator(begin());
  }

  std::reverse_iterator<const_iterator> rend() const {
    return std::make_reverse_iterator(begin());
  }

  std::reverse_iterator<const_iterator> crbegin() const { return cend(); }

  std::reverse_iterator<const_iterator> crend() const { return cbegin(); }

  void insert(iterator pos, const T& value) {
    if (pos == begin()) {
      push_front(value);
      return;
    }
    if (pos != begin()) {
      push_back(*(end() - 1));
      iterator index = end() - 2;
      while (index > pos) {
        *index = *(index - 1);
        index--;
      }
      *pos = value;
    }
  }

  void emplace(iterator pos, T&& value) {
    if (pos == begin()) {
      emplace_front(value);
      return;
    }
    if (pos != begin()) {
      iterator index = end() - 2;
      emplace_back(*(end() - 1));
      while (index > pos) {
        *index = *(index - 1);
        index--;
      }
      *pos = value;
    }
  }

  void erase(iterator pos) {
    if (pos == begin()) {
      pop_front();
      return;
    }
    iterator index = pos + 1;
    while (index < end()) {
      *(index - 1) = *index;
      index++;
    }
    pop_back();
  }

 private:
  iterator begin_;
  iterator end_;
};