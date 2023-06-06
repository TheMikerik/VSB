#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct{
    int S;
    int I;
    int R;
} Sir;

typedef struct{
    float S;
    float I;
    float R;
} Sir_f;

float s_d(int s_ftion, int people){
    float res = ((float) s_ftion / (float) people);

    return res;  
}

float i_d(int i_ftion, int people){
    float res = ((float) i_ftion / (float) people);

    return res;
}

float r_d(int r_ftion, int people){
    float res = ((float) r_ftion / (float) people);

    return res;
}

float s_d_sim(float sFT, float b, float iFT){
    float res = ( sFT - (b * sFT * iFT) );

    return res;  
}

float i_d_sim(float iFT, float b, float y, float sFT){
    float res = ( iFT + (b * sFT * iFT) - (y *iFT) );

    return res;
}

float r_d_sim(float rFT, float y, float iFT){
    float res = ( rFT + (y * iFT) );

    return res;
}

int main(int args, char** load_info){
   // int args = 9;
    /*
    int args, char** load_info

    $ ./epidemic-modelling --real-data data.csv --infectious_days 8 --infections_per_day 0.3 --output output.svg
    ./epidemic-modelling data.csv 8 0.3 output.svg
    0 -> epidemic-modelling  (data-1   8-2   0.3-4 output-4)
    1 -> real-data
    2 -> data.csv (INPUT FILE) --- PATH
    3 -> infectious_days
    4 -> 8 (CAN_INFECT) --- INT
    5 -> infections_per_day
    6 -> 0.3 (IpD) --- FLOAT
    7 -> output
    8 -> .svg (OUTPUT FILE) --- PATH
    */
   char* input = load_info[1];
   char* output = load_info[4];
   if (args != 5){
        printf("Wrong arguments!");
        return 1;
   }

   else{
// Part_#1
// Opening initial CSV file
        int file_length = 0;


        FILE* fin = fopen(input, "r");

        if (fin == NULL){
            printf("Unable to load selected file.");
            return 1;
        }
        else {
            int buffer_size = 20;
            char* buffer = (char*)malloc(sizeof(char) * buffer_size);

            while(!feof(fin)){
                fgets(buffer, buffer_size, fin);
                file_length++;
            }
            fclose(fin);

//Dividing input into S, I, R parts
            FILE* fin = fopen(input, "r");
            Sir sir_init[file_length];

            for( int row = 0; !feof(fin); row++){

                fgets(buffer, buffer_size, fin);

                char* tmp_s = strtok(buffer, ";");
                sir_init[row].S = atoi(tmp_s);

                char* tmp_i = strtok(NULL, ";");
                sir_init[row].I = atoi(tmp_i);

                char* tmp_r = strtok(NULL, "\n");
                sir_init[row].R = atoi(tmp_r);

                //printf("Day %d. S: %d I: %d R: %d\n", row, sir_init[row].S, sir_init[row].I, sir_init[row].R);
            }
            fclose(fin);
            free(buffer);
            buffer = NULL;
        }
// Test Part_#1 - works (no errors/problems; sanitizer ok)

// Part_#2

// Simulation part
        //--------------------------------EDIT BEFORE SUBMITING
    int days = file_length - 1;
    int infectious_days = atoi(load_info[2]);
    float fl_infectious_days = (float) infectious_days;
    float infections_per_day = atof(load_info[3]);
        //--------------------------------THIS PART
    Sir sir_init[file_length];

    int people = sir_init->S + sir_init->I + sir_init->R;
    float b = infections_per_day;
    float y = (1/fl_infectious_days);

    Sir_f sir_init_f[file_length];

    for(int index = 0; index != file_length; index++){
        sir_init_f[index].I = i_d(sir_init[index].I, people);
        sir_init_f[index].S = s_d(sir_init[index].S, people);
        sir_init_f[index].R = r_d(sir_init[index].R, people);
    }

    Sir_f sir_simul[days];
    for(int i = 0; i != days; i++){
        if (i == 0){
            sir_simul[i].S = s_d(sir_init[i].S, people);
            sir_simul[i].I = i_d(sir_init[i].I, people);
            sir_simul[i].R = r_d(sir_init[i].R, people);
        }
        else {
            sir_simul[i].S = s_d_sim(sir_simul[i-1].S, b, sir_simul[i-1].I);
            sir_simul[i].I = i_d_sim(sir_simul[i-1].I, b, y, sir_simul[i-1].S);
            sir_simul[i].R = r_d_sim(sir_simul[i-1].R, y, sir_simul[i-1].I);
        }
    }
// Test Part_#2 - works (no errors/problems; sanitizer ok)



// Part_#3
// Creating files as input to graph
/*
    FILE* fginit = fopen("file_graph_init.txt", "w");
    int i = 0;
    for ( i = 0; i < (file_length - 1); i++){
        fprintf(fginit, "%.1f,%.1f,%.1f\n", (sir_init_f[i].S * 100), (sir_init_f[i].I * 100), (sir_init_f[i].R * 100));
    }
    fprintf(fginit, "%.1f,%.1f,%.1f", (sir_init_f[i].S * 100), (sir_init_f[i].I * 100), (sir_init_f[i].R * 100));
    fclose(fginit);


    FILE* fgsim = fopen("file_graph_simulation.txt", "w");
    i = 0;
    for (i = 0; i < (days-1); i++){
        fprintf(fgsim, "%.1f,%.1f,%.1f\n", (sir_simul[i].S * 100), (sir_simul[i].I * 100), (sir_simul[i].R * 100));
    }
    fprintf(fgsim, "%.1f,%.1f,%.1f", (sir_simul[i].S * 100), (sir_simul[i].I * 100), (sir_simul[i].R * 100));
    fclose(fgsim);
*/


    int i = 0;
    for ( i = 0; i < file_length; i++){
        sir_init_f[i].S = (sir_init_f[i].S * 100);
        sir_init_f[i].I = (sir_init_f[i].I * 100);
        sir_init_f[i].R = (sir_init_f[i].R * 100);
    }

    i = 0;
    for (i = 0; i < days; i++){
        sir_simul[i].S = (sir_simul[i].S * 100);
        sir_simul[i].I = (sir_simul[i].I * 100);
        sir_simul[i].R = (sir_simul[i].R * 100);
        
    }

// Part_#4
// Graph
    FILE* graph_init = fopen(output, "w");

/* Playground
680x365
*/
float parts = (680/file_length);
float gminx = 100;
float gminy = 15;
float gmaxx = 780;
float gmaxy = 380;

    fprintf(graph_init, "<svg viewBox=\"0 0 800 620\" class=\"chart\">\n");

//S - BLUE - INITIAL
    fprintf(graph_init, "<polyline fill=\"None\" stroke=\"#0000FF\" stroke-width=\"2\" points=\"\n");
    
    for (int i = 0; i != file_length; i++){
        fprintf(graph_init, "%.1f,%.1f\n", ((parts*i)+100), (((100-(sir_init_f[i].S))*3.65)+15));
    }
    fprintf(graph_init,"\" />\n");
//S - BLUE - SIMULATION
    fprintf(graph_init, "<polyline fill=\"None\" stroke=\"#D2CFFF\" stroke-width=\"2\" points=\"\n");
    
    for (int i = 0; i != days; i++){
        fprintf(graph_init, "%.1f,%.1f\n", ((parts*i)+100), (((100-(sir_simul[i].S))*3.65)+15));
    }
    fprintf(graph_init,"\" />\n");


//I - RED - INITIAL
    fprintf(graph_init, "<polyline fill=\"None\" stroke=\"#FF0000\" stroke-width=\"2\" points=\"\n");
    
    for (int i = 0; i != file_length; i++){
        fprintf(graph_init, "%.1f,%.1f\n", ((parts*i)+100), (((100-(sir_init_f[i].I))*3.65)+15));
    }
    fprintf(graph_init,"\" />\n");
//I - RED - SIMULATION
    fprintf(graph_init, "<polyline fill=\"None\" stroke=\"#FFD1D1\" stroke-width=\"2\" points=\"\n");
    
    for (int i = 0; i != days; i++){
        fprintf(graph_init, "%.1f,%.1f\n", ((parts*i)+100), (((100-(sir_simul[i].I))*3.65)+15));
    }
    fprintf(graph_init,"\" />\n");

//R - GREEN - INITIAL
    fprintf(graph_init, "<polyline fill=\"None\" stroke=\"#00FF00\" stroke-width=\"2\" points=\"\n");
    
    for (int i = 0; i != file_length; i++){
        fprintf(graph_init, "%.1f,%.1f\n", ((parts*i)+100), (((100-(sir_init_f[i].R))*3.65)+15));
    }
    fprintf(graph_init,"\" />\n");
//R - GREEN - SIMULATION
    fprintf(graph_init, "<polyline fill=\"None\" stroke=\"#C2EABD\" stroke-width=\"2\" points=\"\n");
    
    for (int i = 0; i != days; i++){
        fprintf(graph_init, "%.1f,%.1f\n", ((parts*i)+100), (((100-(sir_simul[i].R))*3.65)+15));
    }
    fprintf(graph_init,"\" />\n");




    fprintf(graph_init, "<g class=\"labels x-labels\">\n");

    for (int i = 0; i != file_length; i++){
        fprintf(graph_init,
           "<text x=\"%.1f\" y=\"400\">%d</text>\"\n", ((parts*i)+100), i);
    }
    fprintf(graph_init,"<text x=\"430\" y=\"430\" class=\"label-title\">Days</text>\n");
    fprintf(graph_init,"</g>\"\n");
    fprintf(graph_init,"<g class=\"labels y-labels\">\n");

    int descript = 100;
    for (int i = 0; i < 10; i++){
        fprintf(graph_init,"<text x=\"80\" y=\"%.1f\">%d</text>\n", ((i*37.5)+15), descript );
        descript = descript - 10;
    }
    fprintf(graph_init,"<text x=\"50\" y=\"200\" class=\"label-title\">SIR</text>\n");
    fprintf(graph_init,"</g>\n");

    fprintf(graph_init,"<g class=\"description\">\n");
    fprintf(graph_init,"<text x=\"120\" y=\"480\">Real data:</text>\n");
    fprintf(graph_init,"<text x=\"110\" y=\"550\">Simulation:</text>\n");
    fprintf(graph_init,"<circle cx=\"300\" cy=\"475\" r=\"20\" stroke=\"black\" stroke-width=\"1\" fill=\"blue\" />\n");
    fprintf(graph_init,"<circle cx=\"450\" cy=\"475\" r=\"20\" stroke=\"black\" stroke-width=\"1\" fill=\"red\" />\n");
    fprintf(graph_init,"<circle cx=\"600\" cy=\"475\" r=\"20\" stroke=\"black\" stroke-width=\"1\" fill=\"#00FF00\" />\n");
    fprintf(graph_init,"<circle cx=\"300\" cy=\"540\" r=\"20\" stroke=\"black\" stroke-width=\"1\" fill=\"#D2CFFF\" />\n");
    fprintf(graph_init,"<circle cx=\"450\" cy=\"540\" r=\"20\" stroke=\"black\" stroke-width=\"1\" fill=\"#FFDEDE\" />\n");
    fprintf(graph_init,"<circle cx=\"600\" cy=\"540\" r=\"20\" stroke=\"black\" stroke-width=\"1\" fill=\"#C2EABD\" />\n");
    fprintf(graph_init,"<text x=\"595\" y=\"600\">R</text>\n");
    fprintf(graph_init,"<text x=\"447\" y=\"600\">I</text>\n");
    fprintf(graph_init,"<text x=\"295\" y=\"600\">S</text>\n");
    fprintf(graph_init,"</g>\n");


    fprintf(graph_init,"</svg>");

    fclose(graph_init);

   }




    printf("\n\n\nPlease wait!\n\nProgramm now generaing the *%s*\nThis action may take max 10 seconds.\n\n", load_info[4]);
    return 0;
}