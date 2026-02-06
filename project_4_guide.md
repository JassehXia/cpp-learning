# Project 4: Multithreaded Task Runner

Welcome to Modern C++! This project is a jump in difficulty, moving away from simple CLI apps into **concurrent programming** and **memory safety**.

## Objective
Build a "Task Runner" that can:
1. Accept a list of "Tasks" (simulated functions that take some time to run).
2. Execute these tasks in the background using **Threads** so the main program doesn't freeze.
3. Use **Smart Pointers** to manage task objects without memory leaks.
4. Log when each task starts and finishes.

## Modern C++ Concepts
- **`std::thread`**: Running code in parallel.
- **`std::mutex`**: Preventing "Race Conditions" (when two threads try to write to the screen at the same time).
- **Smart Pointers (`std::unique_ptr`)**: Automatic memory management. No more manual `delete`!
- **Lambda Functions**: Passing "blocks of code" as variables.
- **`std::chrono`**: Measuring time (e.g., simulating a 2-second task).

## Project Structure
1. Create a file named `task_runner.cpp`.
2. Define a base class `Task` with a virtual function `execute()`.
3. Use a `std::vector<std::unique_ptr<Task>>` to hold your tasks.
4. Launch threads to run `execute()` for each task.

### Modern C++ Starter Snippet
```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <memory> // For smart pointers
#include <mutex>  // For thread safety

std::mutex mtx; // Prevents garbled text when threads print at once

class Task {
public:
    virtual void execute() = 0;
    virtual ~Task() {} // Always needed for virtual classes!
};

void runTask(std::unique_ptr<Task> task) {
    task->execute();
}

int main() {
    std::vector<std::thread> threadPool;
    // Your logic to create and launch tasks...
    
    // CRITICAL: You must "join" threads before the program ends
    for (auto& t : threadPool) {
        if (t.joinable()) t.join();
    }
    return 0;
}
```

## Technical Cheatsheet

Here are the modern C++ tools you'll need for this project.

### 1. Creating a Specific Task (Inheritance)
To make a real task, you must "inherit" from the base `Task` class.
```cpp
class DownloadTask : public Task {
public:
    void execute() override {
        std::cout << "Downloading file..." << std::endl;
    }
};
```

### 2. Thread-Safe Printing (std::lock_guard)
Never lock a mutex manually! Use `std::lock_guard`. It locks the mutex when created and **automatically unlocks** it when the function ends.
```cpp
void safePrint(std::string message) {
    std::lock_guard<std::mutex> lock(mtx); // Locks here
    std::cout << message << std::endl;
} // Automatically unlocks here
```

### 3. Moving Ownership (std::move)
A `std::unique_ptr` cannot be copied (because only one thing can "own" it). To give it to a thread, you must **move** it.
```cpp
auto myTask = std::make_unique<DownloadTask>();
// Launch a thread and MOVE the task into it
std::thread t(runTask, std::move(myTask));
threadPool.push_back(std::move(t));
```

### 4. Simulating Work (sleep_for)
Real software takes time. Use this to simulate a task that takes 2 seconds.
```cpp
#include <chrono>

// Put this inside your execute() function
std::this_thread::sleep_for(std::chrono::seconds(2));
```

### 5. Using Lambdas
Lambdas are "anonymous functions". You can use them to quickly launch a thread without a separate function.
```cpp
std::thread t([]() {
    std::cout << "I am a thread running a lambda!" << std::endl;
});
```

## The Challenge
The biggest challenge here is **Memory Ownership**. Once you `std::move` a task into a thread, the pointer in your `main` function becomes null. You have to trust the thread to do its job and clean up!
