/**

##  ##     ##      ####
##  ##    #  #    ##  ##
######   ######   ##  ##
##  ##   #    #   ##  ##
##  ##   #    #    ####

*/

//A brief test, have fun :-p


#include "matrix_plus.h"

int main(void) {
    printf("creating a square matrix...\n");
    struct matrix *m = create_matrix();
    print_matrix(m);
    //scan_matrix(m);
    //print_matrix(m);
    //printf("scalar multiply by...\n");
    //float s;
    //scanf(" %f", &s);
    //struct matrix *c = scalar_mult(m, s);
    //print_matrix(c);
    //struct matrix *a = add_matrix(m, c);
    //struct matrix *a = matrix_mult(m, c);
    //struct matrix *a = trans(m);
    //struct matrix *a = del_rc(m, 0, 1);
    //printf("let's try inverse...\n");
    //struct matrix *a = inverse(m);
    //print_matrix(a);
    //printf("determiment is so easy...\n");
    //printf("%f\n", det(m));
    //printf("checking correctness of inverse...\n");
    //struct matrix *I = matrix_mult(m, a);
    //print_matrix(I);
    rref(m);
    
    free_matrix(m);
    //free_matrix(c);
    //free_matrix(a);
    //free_matrix(I);
	printf("End of program.\n");
}

//1 2 3 4 5 6 7 8 9
//1 2 3 0 4 5 0 0 6
//1 0 0 0 1 0 0 0 1
//1 1 1 1 1 1 1 1 1
//1 0 0 0 -1 0 0 0 1

/**
1 2 3 4
5 6 7 0
8 9 0 0
10 0 0 0
*/

//1 2 3 4 5 6 7 0 8 9 0 0
//1 2 3 4 0 5 6 7 0 0 8 9
/*
1 0 3 4
0 0 6 7
0 0 8 9
*/

/* 4 6
0 0 0 0 0 1
0 0 0 2 0 2
0 0 3 3 0 3
0 4 4 4 0 4
*/