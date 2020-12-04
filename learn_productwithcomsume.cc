// 问题描述

/* 试想有一个玩具, 这个玩具由两部分组成, 必须拿到这两个部分, 才能够玩。例如,
    一个玩 具鼓, 需要一个鼓锤和一个鼓才能玩。现在有两个小孩,
    他们都很喜欢玩这个玩具。当其中 一个孩子拿到了鼓和鼓锤时,
    那就可以尽情的玩耍了。当另一孩子想要玩, 他就得等待另一 孩子玩完才行。再试想,
    鼓和鼓锤被放在不同的玩具箱里, 并且两个孩子在同一时间里都想 要去敲鼓。之后,
    他们就去玩具箱里面找这个鼓。其中一个找到了鼓,
    并且另外一个找到了 鼓锤。现在问题就来了, 除非其中一个孩子决定让另一个先玩,
    他可以把自己的那部分给另 外一个孩子;
    但当他们都紧握着自己所有的部分而不给予,
    那么这个鼓谁都没法玩。 现在没有孩子去争抢玩具,
    但线程有对锁的竞争 : 一对线程需要对他们所有的互斥量做一些 操作,
    其中每个线程都有一个互斥量,且等待另一个解锁。这样没有线程能工作,
    因为他们 都在等待对方释放互斥量。这种情况就是死锁,
    它的最大问题就是由两个或两个以上的互斥量来锁定一个操作 */

/*
避免死锁的一般建议,就是让两个互斥量总以相同的顺序上锁:总在互斥量B之前锁住互斥量
A,就永远不会死锁
 */

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class thread {
 public:
  thread(){};
  ~thread() {
    t1->join();
    t1 = nullptr;
  }
  void init() {
    t2 = std::make_shared<std::thread>(&thread::consume, this);
    t1 = std::make_shared<std::thread>(&thread::product, this);
  }

  void test() { std::cout << "1" << std::endl; }

  void product() {
    while (1) {
      std::this_thread::sleep_for(std::chrono::milliseconds(20));

      std::lock_guard<std::mutex> l(m1);
      std::cout << "product 1" << std::endl;
      data_.push(6);
      data_cond.notify_one();
    }
  }

  void consume() {
    while (1) {
      std::cout << "consume 1" << std::endl;

      std::unique_lock<std::mutex> l(m1);
      std::cout << "consume 3" << std::endl;

      data_cond.wait(l, [this]() -> bool { return !data_.empty(); });
      //   data_cond.wait_for(l, std::chrono::milliseconds(1));

      std::cout << "data is:" << data_.front() << std::endl;
      data_.pop();
    }
  }
  void Getlock() { lock = std::unique_lock<std::mutex>(m1); }

 private:
  std::shared_ptr<std::thread> t1;
  std::shared_ptr<std::thread> t2;

  std::mutex m1;
  std::unique_lock<std::mutex>
      lock;  // 这个类型的好处在于，本身的实例并没有和互斥量有直接的关系
  std::queue<int> data_;
  std::condition_variable data_cond;
};

int main() {
  thread install;
  install.init();
  while (1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(70));
  }
}
