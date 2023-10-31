#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Heap {
private:
    vector<int> heap_array;
public:
    Heap(void) {}

    void swap(int *a, int *b)
    {
    int temp = *b;
    *b = *a;
    *a = temp;
    }

    int size(){
        return this->heap_array.size();
    }

    void print(){
        for (int i=0; i<this->size(); i++){
            cout << this->heap_array[i] << " ";
        }
        cout << endl;
    }

    void insert(int number){
        this->heap_array.push_back(number);

        if(this->size() == 1){
            return;
        }
        else {
            for(int i = this->size()/2 - 1; i>=0; i--){

                int root = i;
                int left = i * 2 + 1;
                int right = i * 2 + 2;
                
                if(heap_array[left] > heap_array[root] && left <= this->size()-1){
                    swap(&heap_array[root], &heap_array[left]);
                }
                
                if(heap_array[right] > heap_array[root] && right <= this->size()-1){
                    swap(&heap_array[root], &heap_array[right]);
                }
            }
        }

    }
    
    void remove(){
        int top = 0;
        int last = size()-1;

        swap(&heap_array[top], &heap_array[last]);
        heap_array.pop_back();
        last = heap_array[size()-1];
        heap_array.pop_back();
        insert(last);
    }
};

int main(){
    Heap heap;

    heap.insert(11);
    heap.insert(3);
    heap.insert(6);
    heap.insert(1);
    heap.insert(2);
    heap.insert(12);
    heap.insert(15);

    heap.print();
    cout << endl;

    heap.remove();
    heap.print();
    cout << endl;

    heap.remove();
    heap.print();
    cout << endl;

    return 0;
}