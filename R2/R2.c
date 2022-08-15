// R2 Recitation

// Author: Jordan Strande

// Class:  CS270

// Email:  wilcox@cs.colostate.edu



// Include files

#include <stdbool.h>

#include <stdio.h>

#include <stdlib.h>

double input[3];
double exput[2]; 

void computeSphere(double radius, double *addressOfVolume)

{

    // Compute volume

    double result = (4.0 / 3.0) * (3.141593 * radius * radius * radius);



    // Dereference pointer to return result

    *addressOfVolume = result;

}



int main(int argc, char *argv[])

{
 

    // Check number of arguments

    if (argc != 2) {

        printf("usage: ./R2 double\n");

        return EXIT_FAILURE;

    }



    // Parse arguments

    double radius = atof(argv[1]);

    

    // Local variable

    double volume;



    // Call function

    computeSphere(radius, &volume);

    

    // Print volume

    printf("The volume of a sphere with radius %.5f equals %.5f.\n", radius, volume);



    // Return success

    return EXIT_SUCCESS;

}
