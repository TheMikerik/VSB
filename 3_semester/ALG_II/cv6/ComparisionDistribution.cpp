#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arrComp = {4, 5, 2, 8, 9, 3, 1};
vector<int> arrDistr = {4, 2, 2, 8, 3, 3, 1};

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

            // Urceni kolik je mensich prvku v poli
            for(int i=0; i<input_arr.size(); i++){
                int current = input_arr.at(i);

                tmp_arr.push_back(LowerCount{current, 0});

                for(int j=0; j<input_arr.size(); j++){
                    if(input_arr.at(j) < current){
                        tmp_arr[i].lower_count++;
                    }
                }
            }

            // Setrizeni pole podle poctu mensich hodnot
            for(int i=0; i<tmp_arr.size(); i++){
                int max = 0;
                int max_index = 0;
                
                for(int j=0; j<tmp_arr.size(); j++){
                    if(tmp_arr[j].lower_count >= max && tmp_arr[j].lower_count <= tmp_arr.size() - i - 1){
                        max_index = j;
                        max = tmp_arr[j].lower_count;
                    }
                }

                arr.push_back(tmp_arr[max_index]);
            }

            // Print
            for(int i=0; i<arr.size(); i++){
                cout << arr.at(i).number << endl;
            }

            cout << endl;
        }
};

class Distribution{
    private:
        int min, max;
        vector<int> freq;
        vector<int> result;

    public:
        Distribution(vector<int> input){
            this->min = *min_element(input.begin(), input.end());
            this->max = *max_element(input.begin(), input.end());

            int arr_size = max-min+1;
            this->freq.resize(arr_size, 0);
            this->result.resize(arr_size, 0);

            for(int i=0; i<freq.size(); i++){

                for(int j=0; j<freq.size()-1; j++){
                    int current = input.at(j);
                    if(i+1 == current){
                        freq[i]++;
                    }
                }
            }

            for(int i=1; i<freq.size(); i++){
                freq[i] = freq[i-1] + freq[i];
            }

            for(int i=0; i<input.size(); i++){
                int current = input.back();
                input.pop_back();

                freq[current-1] -= 1;
                
            }
        }


};

int main(){
    Comparision c(arrComp);
    Distribution d(arrDistr);
}