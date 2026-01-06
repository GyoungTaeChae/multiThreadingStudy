#include <chrono> // 시간 지연을 위한 헤더
#include <iostream>
#include <thread> // 스레드 사용을 위한 헤더

void DoWork() {
  std::cout << "워커: 2초 동안 열심히 일하는 중...\n";
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "워커: 작업 완료!\n";
}

int main() {
  std::cout << "메인: 워커 스레드를 생성합니다.\n";

  // 2. 스레드 생성 시 함수 이름(DoWork)을 전달합니다.
  // "이 함수를 별도의 스레드에서 실행해줘!"라는 뜻입니다.
  std::thread worker(DoWork);

  // 3. join()으로 기다리기
  std::cout << "메인: 워커가 끝날 때까지 기다립니다 (join)...\n";
  worker.join();

  std::cout << "메인: 워커가 끝났으니 이제 프로그램을 종료합니다.\n";

  return 0;
}

// 결과를 받아와야 하거나, 순서가 중요한 경우에 사용한다.

