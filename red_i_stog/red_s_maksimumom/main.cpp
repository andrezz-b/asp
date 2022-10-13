#include <iostream>
#include <string>
#include <deque>

struct Node {
  int val;
  Node *next;

  Node(const int &val)
    : val(val), next(NULL)
  {}
};

struct Queue {
  Node *head, *tail;
  int size;

  Queue()
    : head(NULL), tail(NULL), size(0)
  {}

  void enqueue(const int &val) {
    Node *newNode = new Node(val);
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
      Node *tmp = head;
      head = head->next;
      delete tmp;
    }
    size--;
  }

  int getHead() {
    if (!head || !tail) return -1;

    return head->val;
  }

  int getTail() {
    if (!head || !tail) return -1;

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

  Queue q;
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