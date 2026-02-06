#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Contact {
  std::string name;
  std::string phone;
  std::string email;
};

void saveToFile(const std::vector<Contact> &contacts) {
  std::ofstream file("contacts.txt");
  for (const auto &c : contacts) {
    file << c.name << "," << c.phone << "," << c.email << "\n";
  }
}

void displayContacts(const std::vector<Contact> &contact) {
  std::cout << "Name\t\tPhone\t\tEmail" << std::endl;
  for (const auto &c : contact) {
    std::cout << c.name << "\t" << c.phone << "\t" << c.email << std::endl;
  }
}

int main() {
  std::vector<Contact> contacts;
  std::string name, number, email;

  // TIP: Always initialize variables. Without "= 0", 'choice' starts with a
  // random "garbage" value from your computer's memory!
  int choice = 0;

  do {
    std::cout << "\n--- Contacts ---\n";
    std::cout << "1. Add\n2. View\n3. Exit\nChoice: ";

    // MISSING: You need this line to actually stop and wait for the user
    // to type their choice!
    std::cin >> choice;

    // IMPORTANT: When you use 'cin >>' and then 'getline', you need this line.
    // It clears the "Enter" key you pressed from the computer's memory so
    // it doesn't skip the name prompt below.
    std::cin.ignore();

    if (choice == 1) {
      std::cout << "Enter the name: ";
      // IMPROVEMENT: Use 'getline' instead of 'cin >>'.
      // 'cin' stops at the first space, so "John Doe" would just become "John".
      std::getline(std::cin, name);

      std::cout << "Enter the phone number: ";
      std::getline(std::cin, number);

      std::cout << "Enter the email: ";
      std::getline(std::cin, email);

      contacts.push_back({name, number, email});
      std::cout << "Contact added!" << std::endl;
    } else if (choice == 2) {
      displayContacts(contacts);
    } else if (choice == 3) {
      saveToFile(contacts);
    } else {
      std::cout << "Invalid choice. Please try again." << std::endl;
    }
  } while (choice != 3);

  return 0;
}

// NEXT LEVEL CHALLENGE:
// Right now, if you close the app and reopen it, your contacts disappear
// from the screen (even though they are in contacts.txt).
// Can you write a 'loadFromFile' function to read them back into the
// 'contacts' vector when the program starts?
