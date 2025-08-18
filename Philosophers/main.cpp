#include <memory>
#include <string>
#include <thread>
#include <iostream>
#include <print>
#include <mutex>

class Fork{
private:
    bool occupied;
    std::mutex mutex;
public: 
    void pickUp(){
        std::unique_lock lock(mutex);
        occupied = true;
    }

    void layDown(){
        occupied = false;
    }
};

class Philosopher{
private: 
    std::shared_ptr<Fork> rightFork;
    std::shared_ptr<Fork> leftFork;
    std::string name;

public:

    Philosopher(std::string name) : name(name){};

    std::shared_ptr<Fork> RightFork() const {
        return rightFork;
    }

    std::shared_ptr<Fork> &RightFork() {
        return rightFork;
    }

    std::shared_ptr<Fork> LeftFork() const {
        return leftFork;
    }

    std::shared_ptr<Fork> &LeftFork() {
        return leftFork;
    }

    void eat(){
        while(true){
            leftFork -> pickUp();
            std::println("{} left pickup leftFork", name);
            rightFork -> pickUp();
            std::println("{} right pickup rightFork", name);
            //Simulating Philosopher is eating
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::println("{} done eating", name);
            leftFork -> layDown();
            std::println("{} left laydown leftFork", name);
            rightFork -> layDown();
            std::println("{} right laydown rightFork", name);
        };
    }  
};

int main(){

    std::shared_ptr<Fork> fork1 = std::make_shared<Fork>();
    std::shared_ptr<Fork> fork2 = std::make_shared<Fork>();
    Philosopher socrates("Socrates");
    socrates.LeftFork() = fork1;
    socrates.RightFork() = fork2;
    Philosopher diogenes("Diogenes");
    diogenes.LeftFork() = fork2;
    diogenes.RightFork() = fork1;
    //socrates.eat();
    std::thread threadSocrates([&](){socrates.eat();});
    //diogenes.eat();
    std::thread threadDiogenes([&](){diogenes.eat();});
    threadSocrates.join();
    threadDiogenes.join();

    return 0;
}