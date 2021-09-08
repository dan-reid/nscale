//
//  nscale.c
//  nscale
//
//  Created by Daniel Reid on 08/09/2021.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("usage: nscale notes midinote\n");
        return 1;
    }
    
    int notes = atoi(argv[1]);
    int midinote = atoi(argv[2]);
    
    if (notes < 1) {
        printf("Error: notes must be positive\n");
        return 1;
    }
    
    if (notes > 24) {
        printf("Error: notes cannot not be greater than 24\n");
        return 1;
    }
    
    if (midinote < 0) {
        printf("Error: MIDI value must be positive\n");
        return 1;
    }
    
    if (midinote > 127) {
        printf("Error: max value for MIDI is 127\n");
        return 1;
    }
    
    double ratio = pow(2.0, 1.0 / 12.0);
    double c5 = 220.0 * pow(ratio, 3);
    double c0 = c5 * pow(0.5, 5);
    double frequency = c0 * pow(ratio, midinote);
    
    double intervals[24];
    
    ratio = pow(2.0, 1.0 / notes);
    for(int i = 0; i < notes; i++) {
        intervals[i] = frequency;
        frequency *= ratio;
        printf("note %i: %f\n", i, intervals[i]);
    }
    
    
    return 0;
}
