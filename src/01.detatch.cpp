#include <iostream>
#include <thread>
#include <chrono>

void DoWork() {
    // 3초 동안 일하는 스레드
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "워커: 작업 완료! (이 메시지가 보일까요?)\n";
}

int main() {
    std::cout << "메인: 워커 스레드를 생성하고 분리(detach)합니다.\n";

    std::thread worker(DoWork);
    
    // 기다리지 않고 연결을 끊어버립니다.
    worker.detach(); 

    std::cout << "메인: 기다리지 않고 바로 프로그램을 종료합니다.\n";

    return 0;
}