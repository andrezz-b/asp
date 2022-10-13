#include <iostream>
#include <stack>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  std::cin >> n;

  std::string command;

  std::stack<std::string> history;
  // Pomocni stack koji pamti ako idemo nazad sa stranice pa naprijed
  std::stack<std::string> buffer;

  history.push("HOME");

  for (int i = 0; i < n; ++i) {
    std::cin >> command;

    if (command == "VISIT") {
      std::string siteName;
      std::cin >> siteName;
      history.push(siteName);
      // Pomocni buffer se briše kada dodamo novu stranicu
      // jer više ne možemo dohvatiti te stranice
      // history: H > a > b > c
      // BACK, history: H > a > b, buffer: c
      // VISIT f, hisotry: H > a > b > f
      // BACK, hisotry: H > a > b, buffer: c > f
      // FORWARD, hisotry: H > a > b > f, buffer: c
      // FORWARD, hisotry: H > a > b > f > c | ovo ispadne jer buffer nismo izbrisali
      // jer nakon sto odemo na novu stranicu forward vise nikad nece voditi na stranicu iz buffera
      while (!buffer.empty()) buffer.pop();

    } else if (command == "FORWARD") {
      if (!buffer.empty()) {
        history.push(buffer.top());
        buffer.pop();
      }
    } else if (command == "BACK") {
      if (history.top() != "HOME") {
        buffer.push(history.top());
        history.pop();
      }

    }

    std::cout << history.top() << "\n";
  }

  return 0;
}