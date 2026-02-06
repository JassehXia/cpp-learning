#include <iostream>

int main() {
  int choice;
  do {
    std::cout << "\n--- Calculator ---\n";
    std::cout << "1. Add\n2. Multiply\n3. Exit\nChoice: ";
    std::cin >> choice;
    if (choice == 1) {
      int num1, num2;
      std::cout << "Enter two numbers to add: ";
      std::cin >> num1 >> num2;
      std::cout << "Result: " << num1 + num2 << std::endl;
    } else if (choice == 2) {
      int num1, num2;
      std::cout << "Enter two numbers to multiply: ";
      std::cin >> num1 >> num2;
      std::cout << "Result: " << num1 * num2 << std::endl;
    }
  } while (choice != 3);
  return 0;
}