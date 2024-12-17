#include <iostream>
#include <ctime>
#include <unistd.h>

#define sleepTimeSec 1
#define arraySize 12

void from_right(std::string array[]){
  for(int i = arraySize -1; i > -1; i--){
    std::cout << "LED " << array[i] << std::endl;
    usleep(sleepTimeSec * 1000000 / arraySize);
  }
}

void from_left(std::string array[]){
  for(int i = 0; i < arraySize; i++){
    std::cout << "LED " << array[i] << std::endl;
    usleep(sleepTimeSec * 1000000 / arraySize);
  }
}


int main(){
  std::string array[arraySize] = {"00000000", "10000000","11000000","11100000",
                           "01110000","00111000","00011100","00001110",
                           "00000111", "00000011", "00000001","00000000"};

  std::string arr[arraySize] = {
    "0", "1", "2", "3", "4", "5", "6", "7"
  };

  from_right(array);
  from_left(array);

}