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

#include <vector>
#include <iostream>
#include <algorithm>

class Distribution {
private:
    int min, max;
    std::vector<int> freq;
    std::vector<int> result;

public:
    Distribution(std::vector<int> input) {
        this->min = *min_element(input.begin(), input.end());
        this->max = *max_element(input.begin(), input.end());

        int arr_size = max - min + 1;
        this->freq.resize(arr_size, 0);
        this->result.resize(input.size(), 0);

        // Freq count
        for (int i = 0; i < input.size(); i++) {
            freq[input[i] - min]++;
        }
        for (int i = 1; i < freq.size(); i++) {
            freq[i] += freq[i - 1];
        }

        // Sort the array based on freqs
        for (int i = input.size() - 1; i >= 0; i--) {
            int current = input[i];
            result[freq[current - min] - 1] = current;
            freq[current - min]--;
        }

        // Print
        for (int i = 0; i < result.size(); i++) {
            std::cout << result[i] << std::endl;
        }
    }
};


int main(){
    Comparision c(arrComp);
    Distribution d(arrDistr);
}