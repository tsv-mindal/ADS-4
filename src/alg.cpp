// Copyright 2021 NNTU-CS
template<typename T>
class TPQueue  {
  private:
  T* arr;
  int size;
  int begin, end;
  int count;
  int stepBack(int index) {
    int r = --index;
    if (r < 0)
      r += size + 1;
    return r;
  }
  int stepForward(int index) {
    int r = ++index;
    if (r > size)
      r -= size + 1;
    return r;
  }
  public:
  TPQueue( ):
  size(100),
  begin(0), end(0), count(0) {
    arr = new T[size + 1];
  }
  ~TPQueue() {
    delete[] arr;
  }
  void push(const T& item) {
    assert(count < size);
    if (isEmpty()) {
      arr[end] = item;
    } else {
      int current = stepBack(end);
      if (arr[current].prior >= item.prior) {
        arr[end] = item;
      } else {
        do {
          arr[stepForward(current)] = arr[current];
          current = stepBack(current);
        } while (arr[current].prior < item.prior &&
                 stepForward(current) != begin);
        arr[stepForward(current)] = item;
      }
    }
    end = stepForward(end);
    count++;
  }
  T pop() {
    assert(count > 0);
    T item = arr[begin];
    count--;
    begin = stepForward(begin);
    return item;
  }
  T get() const {
    assert(count > 0);
    return arr[begin];
  } 
  bool isEmpty() const {
    return count == 0;
  }
  bool isFull() const {
    return count == size;
  }
};
struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
