#include <iostream>
#include <cstring>

int main() {
  const char* bank_caption =
    "|Welcome to the Auburn Branch of the Tiger Bank|";
  const int msg_width = strlen(bank_caption);
  int response {};
  
  for (int i = 0; i < msg_width; i++)
    std::cout << "=";

  std::cout << "\n" << bank_caption << "\n";

  for (int i = 0; i < msg_width; i++)
    std::cout << "=";

  std::cout << "\n1. Login\n2. Quit\nResponse: ";
  
  std::cin >> response;

  if (response == 1) {
    std::cout << "Welcome!\n";
    return 0;
  }
  else {
    return 0;
  }
}
