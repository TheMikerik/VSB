#include <iostream>
#include <vector>
#include <list>

const char* numberWords[] = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
        "seventeen", "eighteen", "nineteen", "twenty",
        "twenty-one", "twenty-two", "twenty-three", "twenty-four", "twenty-five",
        "twenty-six", "twenty-seven", "twenty-eight", "twenty-nine",
        "thirty", "thirty-one", "thirty-two", "thirty-three", "thirty-four", "thirty-five",
        "thirty-six", "thirty-seven", "thirty-eight", "thirty-nine",
        "forty", "forty-one", "forty-two", "forty-three", "forty-four", "forty-five",
        "forty-six", "forty-seven", "forty-eight", "forty-nine",
        "fifty", "fifty-one", "fifty-two", "fifty-three", "fifty-four", "fifty-five",
        "fifty-six", "fifty-seven", "fifty-eight", "fifty-nine",
        "sixty", "sixty-one", "sixty-two", "sixty-three", "sixty-four", "sixty-five",
        "sixty-six", "sixty-seven", "sixty-eight", "sixty-nine",
        "seventy", "seventy-one", "seventy-two", "seventy-three", "seventy-four", "seventy-five",
        "seventy-six", "seventy-seven", "seventy-eight", "seventy-nine",
        "eighty", "eighty-one", "eighty-two", "eighty-three", "eighty-four", "eighty-five",
        "eighty-six", "eighty-seven", "eighty-eight", "eighty-nine",
        "ninety", "ninety-one", "ninety-two", "ninety-three", "ninety-four", "ninety-five",
        "ninety-six", "ninety-seven", "ninety-eight", "ninety-nine", "one hundred"
};


template <typename T>

class HashTable {
private:
    std::vector<
            std::list <
                    std::pair<
                            int,
                            T
                    >
            >
    > table;
    int size;

public:
    HashTable(int size) : table(size), size(size) {}

    void insert(int key, T value){
        int location = key % this->size;
        std::pair<int, T> item = std::make_pair(key, value);

        table[location].push_back(item);
    }
    T search(int key){
        int location = key % this->size;
        std::list<std::pair<int, T> > bucket = table[location];

        for (auto item = bucket.begin(); item != bucket.end(); item++) {
            if (item->first == key) {
                return item->second;
            }
        }

        return "Item was not found!";
    }
    bool remove(int key){
        int location = key % this->size;
        std::list<std::pair<int, T> > *bucket = &table[location];

        for (auto item = bucket->begin(); item != bucket->end(); item++) {
            if (item->first == key) {
                bucket->erase(item);
                std::cout << "success\n";
                return true;
            }
        }
        std::cout << "failed (number do not exist)\n";
        return false;
    }

    void print(){
        for(int bucket = 0; bucket < this->size; bucket++){
            std::list<std::pair<int, T> > items = table[bucket];
            std::cout << "[Bucket_" << bucket << "] ";
            for (auto item = items.begin(); item != items.end(); item++){
                std::cout << "\tID_" << item->first << ":" << item->second << "\t";
            }
            std::cout << std::endl;
        }
    }
};

int main(){
    HashTable<const char*> ht(27);

    for (int i = 0; i < 100; i++) {
        ht.insert(i, numberWords[i]);
    }

    std::cout << "\n\n----------------Searching:\n";
    for (int i = 0; i < 10; i++){
        std::cout << "Searching " << i*13 << ": \t" << ht.search(i*13) << "\n";
    }

    std::cout << "\n\n----------------Print:\n";
    ht.print();

    std::cout << "\n\n----------------Deletion:\n";
    for (int i = 0; i < 10; i++) {
        std::cout << "Deleting " << i * 13 << ": ";
        ht.remove(i*13);
    }

    std::cout << "\n\n----------------Print:\n";
    ht.print();



    return 0;
}


// mermaid -> ds ....... # = povinny atributs