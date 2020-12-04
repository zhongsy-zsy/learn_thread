#include <iostream>
#include <mutex>
#include <thread>

/*
阻塞当前线程直至 *this 所标识的线程结束其执行。

*this 所标识的线程的完成同步于对应的从 join() 成功返回。

*this 自身上不进行同步。同时从多个线程在同一 thread 对象上调用 join()
构成数据竞争，导致未定义行为。




让一个线程等待另外一个线程，需要的是加锁

 */

class leaen_mutex {
 private:
  std::mutex m;
  std::thread f1;
  std::thread f2;
  std::thread f3;
  std::shared_ptr<std::thread> f4;

  int sum1 = 0;
  int sum2 = 0;

 public:
  leaen_mutex() {}
  ~leaen_mutex() {}

  void thread_1() {
    for (int i = 0; i < 5000; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      std::cout << "thread_1" << std::endl;
      std::lock_guard<std::mutex> lock(m);
      sum1++;
    }
  }
  void thread_2() {
    for (int i = 0; i < 5000; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      std::cout << "thread_2" << std::endl;
      std::lock_guard<std::mutex> lock(m);
      sum1++;
    }
  }

  void thread_3() {
    for (int i = 0; i < 5000; i++) {
      // std::lock_guard(m);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      std::cout << "thread_3" << std::endl;
      sum2++;
    }
  }

  void thread_4() {
    for (int i = 0; i < 5000; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      std::cout << "thread_4" << std::endl;
      // std::lock_guard(m);
      sum2++;
    }
  }
  void output_message() {
    std::cout << "sudm_1: " << sum1 << " "
              << "sum_2: " << sum2 << std::endl;
  }

  void init() {
    f1 = std::thread(&leaen_mutex::thread_1, this);
    f2 = std::thread(&leaen_mutex::thread_2, this);
    f3 = std::thread(&leaen_mutex::thread_3, this);
    f4 = std::make_shared<std::thread>(std::bind(&leaen_mutex::thread_4, this));
    f1.join();
    f2.join();
    f3.join();
    f4->join();
  }
};

int main() {
  leaen_mutex instance;

  instance.init();
  //   while (1) {
  instance.output_message();
  //   }
}
