#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
std::mutex m2;

/*
void m1_m2_deadlock()
{
    std::lock_guard<std::mutex> ul1(m1);
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    std::lock_guard<std::mutex> ul2(m2);

    std::cout << "m1_m2_deadlock()" << std::endl;
}

void m2_m1_deadlock()
{
    std::lock_guard<std::mutex> ul1(m2);
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    std::lock_guard<std::mutex> ul2(m1);

    std::cout << "m2_m1_deadlock()" << std::endl;
}
*/

void m1_m2_resolve_deadlock()
{
    std::unique_lock<std::mutex> ul1(m1, std::defer_lock);
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    std::unique_lock<std::mutex> ul2(m2, std::defer_lock);

    std::lock(ul1, ul2);

    std::cout << "m1_m2_resolve_deadlock()" << std::endl;
}

void m2_m1_resolve_deadlock()
{
    std::unique_lock<std::mutex> ul1(m1, std::defer_lock);
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    std::unique_lock<std::mutex> ul2(m2, std::defer_lock);

    std::lock(ul2, ul1);

    std::cout << "m2_m1_resolve_deadlock()" << std::endl;
}


int main()
{
    //std::thread thread1(m1_m2_deadlock);
    //std::thread thread2(m2_m1_deadlock);

    std::thread thread1(m1_m2_resolve_deadlock);
    std::thread thread2(m2_m1_resolve_deadlock);

    thread1.join();
    thread2.join();

    return 0;
}