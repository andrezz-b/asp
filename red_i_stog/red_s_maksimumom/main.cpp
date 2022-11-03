#include <iostream>
#include <string>
#include <deque>

template <typename T> struct Node {
  T val;
  Node<T> *next;

  Node(const T &val)
    : val(val), next(NULL)
  {}
};

template <typename T> struct Queue {
  Node<T> *head, *tail;
  int size;

  Queue()
    : head(NULL), tail(NULL), size(0)
  {}

  void enqueue(const T &val) {
    Node<T> *newNode = new Node<T>(val);
    if (!head || !tail) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    size++;
  }

  void dequeue() {
    if (!head || !tail) return;

    if (head == tail) {
      delete head;
      head = NULL;
      tail =  NULL;
    } else {
      Node<T> *tmp = head;
      head = head->next;
      delete tmp;
    }
    size--;
  }

  T getHead() {
    if (!head || !tail) return (T) -1;

    return head->val;
  }

  T getTail() {
    if (!head || !tail) return (T) -1;

    return tail->val;
  }

  bool isEmpty() {
    return head == NULL;
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::string op;

  Queue<int> q;
  std::deque<int> maxQ;

  for (int i = 0; i < n; ++i) {
    std::cin >> op;

    if (op == "max") {
      if (q.isEmpty()) {
        std::cout << "-\n";
      } else {
        std::cout << maxQ.front() << "\n";
      }

    } else if (op == "enqueue") {
      int x;
      std::cin >> x;
      q.enqueue(x);
      while (!maxQ.empty() && x > maxQ.back()) {
        maxQ.pop_back();
      }
      maxQ.push_back(x);
    } else if (op == "dequeue") {
      if (maxQ.front() == q.getHead()) {
        maxQ.pop_front();
      }
      q.dequeue();
    }
  }

  return 0;
}