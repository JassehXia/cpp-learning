# Project 2: Contact Management System

Since you found the calculator too easy, let's step up the complexity. This project introduces **Structs**, **Vectors**, and **File I/O**—essential for real-world software.

## Objective
Build a program that can:
1. **Add** a contact (Name, Phone Number, Email).
2. **Display** all contacts in a formatted list.
3. **Save** all contacts to a file (`contacts.txt`) when the program exits.
4. **Load** contacts from that file when the program starts.

## New Concepts to Master
- **Structs**: Grouping related data (Name + Phone + Email) into one object.
- **`std::vector`**: A dynamic array that can grow (part of the Standard Template Library).
- **File Streams (`fstream`)**: Reading from and writing to files.

## Project Structure
1. Create a file named `contacts.cpp`.
2. Define a `struct Contact` at the top of your file.
3. Use a `std::vector<Contact>` to store your list in memory.
4. Use `std::ofstream` to write to a file and `std::ifstream` to read from it.

### Starter Code Snippet
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

void saveToFile(const std::vector<Contact>& contacts) {
    std::ofstream file("contacts.txt");
    for (const auto& c : contacts) {
        file << c.name << "," << c.phone << "," << c.email << "\n";
    }
}

int main() {
    std::vector<Contact> contacts;
    // 1. Load from file (if exists)
    // 2. Show menu (Add, View, Save & Exit)
    // 3. Logic...
    return 0;
}
```

## Technical Cheatsheet

Here are the most useful methods and patterns you'll need for this project:

### 1. Adding to a Vector
Use `.push_back()` to add a new struct to your list.
```cpp
Contact newContact = {"John", "123", "john@email.com"};
contacts.push_back(newContact);
```

### 2. The "Parsing" Secret (stringstream)
To read a line like `John,123,john@email.com` and split it, use `std::stringstream` and `std::getline`.
```cpp
#include <sstream>

std::string line = "John,123,john@email.com";
std::stringstream ss(line);
std::string name, phone, email;

std::getline(ss, name, ',');  // Reads until the first comma
std::getline(ss, phone, ','); // Reads until the second comma
std::getline(ss, email);      // Reads the rest
```

### 3. Displaying with Formatting
Use `\t` (tab) to make your output look like a table.
```cpp
std::cout << "Name\t\tPhone\t\tEmail" << std::endl;
for (const auto& c : contacts) {
    std::cout << c.name << "\t" << c.phone << "\t" << c.email << std::endl;
}
```

### 4. Reading from a File
```cpp
std::ifstream file("contacts.txt");
std::string line;
while (std::getline(file, line)) {
    // Process each line here
}
```
