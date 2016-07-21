#include <iostream>
using std::cout;
using std::cin;

int main() {
  cout << "Hello I am World, who are you:";
  char* ans = new char[10];
  cin >> ans;
  cout << "You are: " << ans << std::endl;
  return 0;
}
