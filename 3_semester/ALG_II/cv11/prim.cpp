#include <iostream>
#include <vector>

std::vector<std::vector<int> > matrix1 = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
};

std::vector<std::vector<int> > matrix2 = {
        {0, 9, 75, 0, 0},
        {9, 0, 95, 19, 42},
        {75, 95, 0, 51, 66},
        {0, 19, 51, 0, 31},
        {0, 42, 66, 31, 0}
};

std::vector<std::vector<int> > matrix3 = {
        {0, 19, 5, 0, 0},
        {19, 0, 5, 9, 2},
        {5, 5, 0, 1, 6},
        {0, 9, 1, 0, 1},
        {0, 2, 6, 1, 0}
};

bool ignoring(std::vector<int> ignore, int line){
        for(int i = 0; i < ignore.size(); i++){
                if(line == ignore[i]){
                        return true;
                }
        }
        return false;
}

void PrimeAlgorithm(std::vector<std::vector<int> > matrix, int order){
        short size = matrix.size();
        std::vector<int> result;
        std::vector<int> check;

        for (int i = 0; i < size; i++){
                int ignore = 0;
                int min = -1;
                check.push_back(i);

                for (int j = 0; j < size; j++){
                        for( int k : check ){
                                int current = matrix[k][j];
                                if ( (current < min || min == -1) && current != 0 && !ignoring(result, j) ){
                                        min = current;
                                        ignore = j;
                                }
                        }
                }
                result.push_back(ignore);
        }

        std::cout << "Matrix" << order << ": " << std::endl;
        for (int i = 0; i<result.size(); i++){
                std::cout << (char) (65+result[i]) << " \t ";
        }
        std::cout << "\n\n";
}

int main(){
        PrimeAlgorithm(matrix1, 1);
        PrimeAlgorithm(matrix2, 2);
        PrimeAlgorithm(matrix3, 3);

        return 0;
}