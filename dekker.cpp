#include <iostream>
#include <pthread.h>

volatile bool flag0;
volatile bool flag1;
volatile int turn;

long count;
long count0;
long count1;
const long limit = 10*1000*1000;

void* f0(void *arg) {
    while (true) {
        // acquire
        flag0 = true;
        __sync_synchronize(); // mfence
        while (flag1) {
             if (turn != 0) {
                 flag0 = false;
                 while (turn != 0) {
                 }
                 flag0 = true;
             }
        __sync_synchronize(); // mfence
        }
        // critical section
        ++count0;
        ++count;
        // yield
        turn = 1;
        flag0 = false;
        __sync_synchronize(); // mfence
        // exit
        if (count0 == limit)
            return 0;
    }
}

void* f1(void *arg) {
    while (true) {
        // acquire
        flag1 = true;
        __sync_synchronize(); // mfence
        while (flag0) {
             if (turn != 1) {
                 flag1 = false;
                 while (turn != 1) {
                 }
                 flag1 = true;
             }
        __sync_synchronize(); // mfence
        }
        // critical section
        ++count1;
        ++count;
        // yield
        turn = 0;
        flag1 = false;
        __sync_synchronize(); // mfence
        // exit
        if (count1 == limit)
            return 0;
    }
}

int main(int argc, char** argv) {
    pthread_t t0, t1;

    pthread_create(&t0, 0, f0, 0);
    pthread_create(&t1, 0, f1, 0);
    pthread_join(t0, 0);
    pthread_join(t1, 0);
    std::cout << count << std::endl;
    return 0;
}
