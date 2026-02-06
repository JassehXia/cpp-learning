#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;

class Task {
public:
  virtual void execute() = 0;

  virtual ~Task() {}
};

void runTask(std::unique_ptr<Task> task) { task->execute(); }

void safePrint(std::string message) {
  std::lock_guard<std::mutex> lock(mtx);
  std::cout << message << std::endl;
};

class DownloadTask : public Task {
public:
  void execute() override {
    safePrint("Downloading...");
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
};

int main() {
  std::vector<std::thread> threadPool;

  std::cout << "Launching 5 tasks in parallel..." << std::endl;

  for (int i = 1; i <= 5; ++i) {
    // 1. Create a new task. Each loop iteration gets its own unique object.
    auto myTask = std::make_unique<DownloadTask>();

    // 2. Launch a thread. We 'std::move' the task because a thread
    // needs to take full ownership to run it safely.
    // We pass 'i' as a simulated "ID" or data (optional).
    std::thread t(runTask, std::move(myTask));

    // 3. Move the thread handle into our list.
    // If we don't store 't', it will go out of scope and crash the program!
    threadPool.push_back(std::move(t));
  }

  // After the loop, the main thread continues immediately.
  safePrint("Main: All threads launched. Now I wait for them to finish.");

  // CRITICAL: We wait for all workers to finish their jobs.
  for (auto &t : threadPool) {
    if (t.joinable())
      t.join();
  }

  safePrint("Main: Every task is complete. Perfect timing!");
  return 0;
}
