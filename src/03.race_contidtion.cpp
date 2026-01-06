#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

bool lock_guard = true;
int global_counter = 0;
std::mutex counter_mutex; // 카운터 보호용 Mutex

void IncrementCounter(int iterations) {
  for (int i = 0; i < iterations; ++i) {
    if (lock_guard) {
      std::lock_guard<std::mutex> lock(counter_mutex);
      global_counter++; // Race Condition!
    } else {
      global_counter++;
    }
  }
}

int main() {
  const int kThreadCount = 10;
  const int kIterations = 100000;

  std::vector<std::thread> threads;

  std::cout << "=== Race Condition 테스트 ===\n";
  std::cout << "스레드 수: " << kThreadCount << "\n";
  std::cout << "반복 횟수: " << kIterations << "\n";
  std::cout << "기대값: " << (kThreadCount * kIterations) << "\n\n";
  if (lock_guard) {
    std::cout << "Mutex로 보호됨\n\n";
  } else {
    std::cout << "Mutex로 보호되지 않음\n\n";
  }
  // 스레드 생성
  for (int i = 0; i < kThreadCount; ++i) {
    threads.emplace_back(IncrementCounter, kIterations);
  }

  // 모든 스레드 대기
  for (auto &thread : threads) {
    thread.join();
  }

  std::cout << "실제값: " << global_counter << "\n";
  std::cout << "차이: " << (kThreadCount * kIterations - global_counter)
            << "\n";

  return 0;
}