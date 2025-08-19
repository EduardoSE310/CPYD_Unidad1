#include <random>
#include <thread>
#include <print>

class Adder {
private:
    int results[10];

public: 
    Adder(){
        for(int i=0; i<10; i++){
            results[i] = 0;
        }
    }

    void add(int threadId){        
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, 1000);
        
        int result = 0;

        for(int i=0; i<100; i++){
            result += dist(rng);
        }

        std::println("Sum of thread {} = {}\n", threadId, result);

        this->results[threadId] = result;
    }

    void compareAdds(){
        int max = 0;
        int index = 0;

        std::thread thread1([&](){ add(0); });
        std::thread thread2([&](){ add(1); });
        std::thread thread3([&](){ add(2); });
        std::thread thread4([&](){ add(3); });
        std::thread thread5([&](){ add(4); });
        std::thread thread6([&](){ add(5); });
        std::thread thread7([&](){ add(6); });
        std::thread thread8([&](){ add(7); });
        std::thread thread9([&](){ add(8); });
        std::thread thread10([&](){ add(9); });

        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
        thread5.join();
        thread6.join();
        thread7.join();
        thread8.join();
        thread9.join();
        thread10.join();

        for(int i=0; i<10; i++){
            if(results[i] > max){
                max = results[i];
                index = i;
            }
        }

        std::println("Thread {} has the highest score with {}\n", index, max);
    }
};

int main(){
    Adder adder;

    adder.compareAdds();

    return 0;
}