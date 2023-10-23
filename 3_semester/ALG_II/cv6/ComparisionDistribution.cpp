#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arrComp = {4, 5, 2, 8, 9, 3, 1};

struct LowerCount{
    int number;
    int lower_count;
};

class Comparision{
    private:
        vector<LowerCount> arr;

    public:
        Comparision(vector<int> input_arr){
            vector<LowerCount> tmp_arr;

            for(int i=0; i<input_arr.size(); i++){
                int current = input_arr.at(i);

                tmp_arr.push_back(LowerCount{current, 0});

                for(int j=0; j<input_arr.size(); j++){
                    if(input_arr.at(j) < current){
                        tmp_arr[i].lower_count++;
                    }
                }
            }

            for(int i=0; i<tmp_arr.size(); i++){
                int max_number = 0;
                int max_index = 0;
                
                for(int j=0; j<tmp_arr.size(); j++){
                    if(tmp_arr[j].lower_count > max_number){
                        max_index = j;
                        max_number = tmp_arr[j].number;
                    }
                }

                arr.push_back(tmp_arr[i]);
            }

            reverse(arr.begin(), arr.end());

            for(int i=0; i<arr.size(); i++){
                cout << arr.at(i).number << endl;
            }

            cout << endl;
        }
};


int main(){
    Comparision c(arrComp);
}