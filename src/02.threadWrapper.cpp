#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

class ThreadWrapper {
public:
  explicit ThreadWrapper(std::function<void()> func) : thread_(func) {}

  ~ThreadWrapper() {
    if (thread_.joinable()) {
      thread_.join();
    }
  }

  // 복사/이동 금지
  ThreadWrapper(const ThreadWrapper &) = delete;
  ThreadWrapper &operator=(const ThreadWrapper &) = delete;
  ThreadWrapper(ThreadWrapper &&) = delete;
  ThreadWrapper &operator=(ThreadWrapper &&) = delete;

private:
  std::thread thread_;
};

void Task1() {
  std::cout << "Task1 시작\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "Task1 완료\n";
}

void Task2() {
  std::cout << "Task2 시작\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  std::cout << "Task2 완료\n";
}

int main() {
  std::cout << "=== 메인 스레드 시작 ===\n";

  {
    ThreadWrapper worker1(Task1);
    ThreadWrapper worker2(Task2);

    std::cout << "작업 스레드들 실행 중...\n";

    // 스코프를 벗어나면 자동으로 조인됨!
  }

  std::cout << "=== 메인 스레드 종료 ===\n";
  return 0;
}