#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int writescale(FILE*, int, double*, double, int);
void printscale(int, double*, double, int);
double calcfreq(int, double, double);

int main(int argc, char* argv[]) {
    int notes;
    double frequency;
    FILE* fp = NULL;
    
    int isfreq = 0;
    int write_interval = 0;
    int playit = 0;
    
    while(argc > 1) {
        if (argv[1][0] == '-') {
            char flag = argv[1][1];
            if (flag == 'f') {
                isfreq = 1;
            } else if (flag == 'i') {
                write_interval = 1;
            } else if (flag == 'p') {
                playit = 1;
            } else {
                printf("error: unkown flag: %s\n", argv[1]);
                return 1;
            }
            
            argc--;
            argv++;
        } else {
            break;
        }
    }
    
    
    double ratio = pow(2.0, 1.0 / 12.0);
    
    notes = atoi(argv[1]);
    if (notes < 1 || notes > 24) {
        printf("error: value for notes arg must be in the range 1-24");
        return 1;
    }
    
    if (isfreq) {
        frequency = atof(argv[2]);
        if (frequency < 0.0) {
            printf("error: frequence cannot be negative");
            return 1;
        }
    } else {
        int midinote = atoi(argv[2]);
        if (midinote < 0 || midinote > 127) {
            printf("error: MIDI value must be in the range 1-127\n");
            return 1;
        }
        
        frequency = calcfreq(midinote, ratio, 2.0);
    }
    
    if (argc == 4) {
        printf("writing to file: %s\n", argv[3]);
        fp = fopen(argv[3], "w");
        
        if (fp == NULL) {
            printf("warning: unable to create file: %s\n\n", argv[3]);
            perror("");
        }
    }
    
    ratio = pow(2.0, 1.0 / notes);
    
    int count = notes + 1; // calcuate octave
    double intervals[count];
    double* ptr = intervals;
    int err;
    for(int i = 0; i < count; i++) {
        *ptr = frequency;
        frequency *= ratio;
        printscale(i, ptr, ratio, write_interval);
        
        if (fp) {
            err = writescale(fp, i, ptr, pow(ratio, i), write_interval);
            if (err < 0) {
                perror("there was an error while writing the file.\n");
                break;
            }
        }
        
        ptr++;
    }
    
    if (fp) {
        printf("finished writing file\n");
        fclose(fp);
    }
    
    return 0;
}

int writescale(FILE* fp, int i, double* ptr, double ratio, int write_interval) {
    if (write_interval) {
        return fprintf(fp, "%d:\t%f\t%f\n", i, pow(ratio, i), *ptr);
    }
    return fprintf(fp, "%d:\t%f\n", i, *ptr);
}

void printscale(int i, double* ptr, double ratio, int write_interval) {
    if (write_interval) {
        printf("%d:\t%f\t%f\n", i, pow(ratio, i), *ptr);
    } else {
        printf("%d:\t%f\n", i, *ptr);
    }
}

double calcfreq(int midinote, double ratio, double interval) {
    double c5 = 220.0 * pow(ratio, 3);
    double c0 = c5 * pow(0.5, 5);
    return c0 * pow(ratio, midinote);
}
