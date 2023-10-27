#include "iostream"

template <typename T, typename Allocator = std::allocator<T>>

class List {
 private:
  struct Node {
    T value;
    Node* next = nullptr;
    Node* prev = nullptr;

    explicit Node(const T& value, Node* prev = nullptr, Node* next = nullptr)
        : value(value), prev(prev), next(next) {}
    explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : prev(prev), next(next) {}
  };

 public:
  using value_type = T;
  using alloc_traits = std::allocator_traits<Allocator>;
  using node_allocator = typename alloc_traits::template rebind_alloc<Node>;
  using node_alloc_traits = std::allocator_traits<node_allocator>;
  using allocator_type =
      typename std::allocator_traits<Allocator>::allocator_type;

  List() : alloc_(static_cast<node_allocator>(Allocator())) {
    node_ = node_alloc_traits::allocate(alloc_, 1);
    node_->prev = node_;
    node_->next = node_;
  }

  List(size_t count, const T& value, const Allocator& alloc = Allocator())
      : alloc_(alloc) {
    node_ = node_alloc_traits::allocate(alloc_, 1);
    node_->next = node_;
    node_->prev = node_;
    try {
      size_t index = 0;
      while (index < count) {
        ++index;
        ++size_;
        Node* node_b = new_node_b(value);
        after(node_->prev, node_b);
      }
    } catch (...) {
      Node* copy = nullptr;
      for (Node* current = node_->next; current != node_;) {
        copy = current;
        current = current->next;
        node_alloc_traits::destroy(alloc_, copy);
        node_alloc_traits::deallocate(alloc_, copy, 1);
      }
      node_alloc_traits::deallocate(alloc_, node_, 1);
      size_ = 0;
      throw;
    }
  }

  explicit List(size_t count, const Allocator& alloc = Allocator())
      : alloc_(static_cast<node_allocator>(alloc)) {
    node_ = node_alloc_traits::allocate(alloc_, 1);
    node_->prev = node_;
    node_->next = node_;
    try {
      size_t index = 0;
      while (index < count) {
        ++index;
        ++size_;
        Node* current;
        current = node_alloc_traits::allocate(alloc_, 1);
        try {
          node_alloc_traits::construct(alloc_, current, node_->prev,
                                       node_->prev->next);
        } catch (...) {
          node_alloc_traits::deallocate(alloc_, current, 1);
          throw;
        }
        node_->prev->next = current;
      }
    } catch (...) {
      Node* copy = nullptr;
      for (Node* current = node_->next; current != node_;) {
        copy = current;
        current = current->next;
        node_alloc_traits::destroy(alloc_, copy);
        node_alloc_traits::deallocate(alloc_, copy, 1);
      }
      node_alloc_traits::deallocate(alloc_, node_, 1);
      size_ = 0;
      throw;
    }
  }

  List(const List& other)
      : alloc_(
      alloc_traits::select_on_container_copy_construction(other.alloc_)) {
    node_ = node_alloc_traits::allocate(alloc_, 1);
    node_->prev = node_;
    node_->next = node_;
    Node* current = other.node_->next;
    try {
      size_t index = 0;
      while (index < other.size_) {
        ++index;
        push_back(current->value);
        current = current->next;
      }
    } catch (...) {
      Node* current = node_->next;
      Node* copy = nullptr;
      while (current != node_) {
        copy = current;
        current = current->next;
        node_alloc_traits::destroy(alloc_, copy);
        node_alloc_traits::deallocate(alloc_, copy, 1);
      }
      node_alloc_traits::deallocate(alloc_, node_, 1);
      size_ = 0;
      throw;
    }
  }
  size_t size() const { return size_; }
  List(std::initializer_list<T> initializer,
       const Allocator& alloc = Allocator()) {
    alloc_ = static_cast<node_allocator>(alloc);
    node_ = node_alloc_traits::allocate(alloc_, 1);
    node_->next = node_;
    node_->prev = node_;
    try {
      for (auto it = initializer.begin(); it != initializer.end(); ++it) {
        Node* node_b = new_node_b(*it);
        ++size_;
        after(node_->prev, node_b);
      }
    } catch (...) {
      Node* current = node_->next;
      Node* copy = nullptr;
      while (current != node_) {
        copy = current;
        current = current->next;
        node_alloc_traits::destroy(alloc_, copy);
        node_alloc_traits::deallocate(alloc_, copy, 1);
      }
      node_alloc_traits::deallocate(alloc_, node_, 1);
      size_ = 0;
      throw;
    }
  }
  bool empty() const { return size_ == 0; }
  ~List() {
    Node* current = node_->next;
    Node* copy = nullptr;
    while (current != node_) {
      copy = current;
      current = current->next;
      node_alloc_traits::destroy(alloc_, copy);
      node_alloc_traits::deallocate(alloc_, copy, 1);
    }
    node_alloc_traits::deallocate(alloc_, node_, 1);
  }
  const T& front() const { return node_->next->value; }
  node_allocator get_allocator() { return alloc_; }
  void push_back(const T& new_val) {
    after(node_->prev, new_node_b(new_val));
    ++size_;
  }
  void push_back(T&& new_val) {
    after(node_->prev, new_node_b(std::move(new_val)));
    ++size_;
  }

  void push_front(const T& new_val) {
    after(node_, new_node_f(new_val));
    ++size_;
  }

  void push_front(T&& new_val) {
    after(node_, new_node_f(std::move(new_val)));
    ++size_;
  }
  T& back() { return node_->prev->value; }
  void pop_back() { remove(node_->prev); }

  void pop_front() { remove(node_->next); }
  const T& back() const { return node_->prev->value; }
  List& operator=(const List& other) {
    if (this == &other) {
      return *this;
    }
    List current(other);
    if (node_alloc_traits ::propagate_on_container_copy_assignment::value) {
      current.alloc_ = other.alloc_;
    }
    std::swap(current.alloc_, alloc_);
    std::swap(current.node_, node_);
    std::swap(current.size_, size_);
    return *this;
  }
  T& front() { return node_->next->value; }
  template <bool IsConst>
  class Iterator {
   public:
    Iterator operator++(int) {
      Iterator res = *this;
      ++(*this);
      return res;
    }
    using difference_type = std::ptrdiff_t;
    explicit Iterator(Node* node_ptr) : ptr_(node_ptr) {}
    Iterator& operator++() {
      ptr_ = ptr_->next;
      return *this;
    }
    using value_type = typename std::conditional<IsConst, const T, T>::type;
    template <bool TM>
    bool operator!=(const Iterator<TM>& iter) const {
      return !(ptr_ == iter.ptr_);
    }

    Iterator& operator--() {
      ptr_ = ptr_->prev;
      return *this;
    }
    using reference = typename std::conditional<IsConst, const T&, T&>::type;
    reference operator*() const { return ptr_->value; }
    using pointer = typename std::conditional<IsConst, const T*, T*>::type;
    pointer operator->() const { return &(ptr_->value); }
    Iterator operator--(int) {
      Iterator copy = *this;
      ptr_ = ptr_->prev;
      return copy;
    }
    template <bool TM>
    bool operator==(const Iterator<TM>& iter) const {
      return ptr_ == iter.ptr_;
    }
    explicit operator Iterator<true>() { return Iterator<true>(ptr_); }
    using iterator_category = std::bidirectional_iterator_tag;

   private:
    Node* ptr_;
  };

  using reverse_iterator = std::reverse_iterator<Iterator<false>>;
  using const_iterator = Iterator<true>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  using iterator = Iterator<false>;
  const_iterator end() const { return const_iterator(node_); }
  iterator end() { return iterator(node_); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_iterator begin() const { return const_iterator(node_->next); }

  const_iterator cbegin() const { return const_iterator(node_->next); }
  const_iterator cend() const { return const_iterator(node_); }

  reverse_iterator rend() { return reverse_iterator(begin()); }
  iterator begin() { return iterator(node_->next); }

 private:
  size_t size_ = 0;
  Node* node_;
  node_allocator alloc_;

  Node* new_node_b(const T& temp) {
    Node* pointer = node_alloc_traits::allocate(alloc_, 1);
    try {
      node_alloc_traits::construct(alloc_, pointer, temp, node_->prev,
                                   node_->prev->next);
    } catch (...) {
      node_alloc_traits::deallocate(alloc_, pointer, 1);
      throw;
    }
    return pointer;
  }

  Node* new_node_b(T&& temp) {
    Node* pointer = nullptr;
    try {
      pointer = node_alloc_traits::allocate(alloc_, 1);
      node_alloc_traits::construct(alloc_, pointer, std::move(temp),
                                   node_->prev, node_->prev->next);
    } catch (...) {
      if (pointer) {
        node_alloc_traits::deallocate(alloc_, pointer, 1);
      }
      throw;
    }
    return pointer;
  }
  void after(Node* first, Node* second) const {
    first->next = second;
    second->next->prev = second;
  }

  template <class Type>
  Node* new_node_f(Type&& temp) {
    Node* pointer = node_alloc_traits::allocate(alloc_, 1);
    try {
      node_alloc_traits::construct(alloc_, pointer, std::forward<Type>(temp),
                                   node_, node_->next);
    } catch (...) {
      node_alloc_traits::deallocate(alloc_, pointer, 1);
      throw;
    }
    return pointer;
  }

  void remove(Node* p_node) {
    if (p_node != node_) {
      p_node->prev->next = p_node->next;
      p_node->next->prev = p_node->prev;
      --size_;
      node_alloc_traits ::destroy(alloc_, p_node);
      node_alloc_traits ::deallocate(alloc_, p_node, 1);
    }
  }
};
