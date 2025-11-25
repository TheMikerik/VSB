#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore.h>

// velikost kruhového bufferu
#define N 5

// globální semafory podle předlohy
sem_t mutex_sem; // chrání kritickou sekci
sem_t empty_sem; // počet prázdných slotů
sem_t full_sem;  // počet zaplněných slotů

// kruhový buffer realizovaný přes std::vector
std::vector<std::string> buffer(N);
size_t in_index = 0;
size_t out_index = 0;

void producer(std::string *item)
{
    sem_wait(&empty_sem); // čekej na volné místo
    sem_wait(&mutex_sem); // vstup do kritické sekce

    buffer[in_index] = std::move(*item);
    in_index = (in_index + 1) % N;

    sem_post(&mutex_sem); // opusť kritickou sekci
    sem_post(&full_sem);  // přibylo zaplněné místo
}

void consumer(std::string *item)
{
    sem_wait(&full_sem);  // čekej na zaplněné místo
    sem_wait(&mutex_sem); // vstup do kritické sekce

    *item = std::move(buffer[out_index]);
    out_index = (out_index + 1) % N;

    sem_post(&mutex_sem); // opusť kritickou sekci
    sem_post(&empty_sem); // uvolnilo se prázdné místo
}

int main()
{
    sem_init(&mutex_sem, 0, 1);
    sem_init(&empty_sem, 0, static_cast<unsigned int>(N));
    sem_init(&full_sem, 0, 0);

    std::vector<std::string> items_to_produce{
        "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh"
    };

    std::thread producer_thread([&] {
        for (auto &value : items_to_produce) {
            std::string copy = value; // vlastní kopie pro předání pointeru
            std::cout << "[producer] generating: " << copy << '\n';
            producer(&copy);
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }
    });

    std::thread consumer_thread([&] {
        for (size_t i = 0; i < items_to_produce.size(); ++i) {
            std::string item;
            consumer(&item);
            std::cout << "  [consumer] received: " << item << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        }
    });

    producer_thread.join();
    consumer_thread.join();

    sem_destroy(&mutex_sem);
    sem_destroy(&empty_sem);
    sem_destroy(&full_sem);

    return 0;
}