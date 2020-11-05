#include <iostream>
#include <thread>

void hello() { std::cout << "hello world" << std::endl; }  // 线程初始化函数

int main() {  // 初始线程起始于main
  std::shared_ptr<std::thread> t =
      std::make_shared<std::thread>(hello);  // 初始化线程
  t->join();  // 优先执行，因为启动新线程以后，主线程还在继续执行，防止主线程先结束
}