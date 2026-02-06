# Project 1: Multi-Tool Calculator

This project will help you master the basic syntax of C++.

## Objective
Build a command-line tool that can:
1. Perform basic arithmetic (Add, Subtract, Multiply, Divide).
2. Convert temperatures (Celsius to Fahrenheit and vice versa).

## Required Concepts
- Data types (`int`, `double`, `char`).
- Input/Output (`std::cin`, `std::cout`).
- Control Flow (`if-else`, `switch`).
- Loops (`do-while` for keeping the program running).

## Starter Steps
1. Create a file named `calculator.cpp`.
2. Wrap your main logic in a `while(true)` loop.
3. Use `std::cin` to read a menu choice.
4. Implement the logic for each menu option.

### Sample Code Structure
```cpp
#include <iostream>

int main() {
    int choice;
    do {
        std::cout << "1. Add\n2. Multiply\n3. Exit\nChoice: ";
        std::cin >> choice;
        // Your logic here
    } while (choice != 3);
    return 0;
}
```
