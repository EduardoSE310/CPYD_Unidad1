#include <cstdlib>
#include <ctime>

srand(time(0));

class Adder {
public: 
    int add(){
        int a = 1 + (rand() % (1000 - 1 + 1));
        int b = 1 + (rand() % (1000 - 1 + 1));

        return a + b;
    }
}

int main(){
    podman run -d --replace --name CppDevContainer --network testnet -v /mnt/c/temporal/projects/:/root:z -p 20202:22 -p 8080:8080 cpp_dev_img:latest

    return 0;
}