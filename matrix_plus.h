/**

##  ##     ##      ####
##  ##    #  #    ##  ##
######   ######   ##  ##
##  ##   #    #   ##  ##
##  ##   #    #    ####

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct matrix {
    int nr;
    int nc;
    float **data;
};

struct matrix *new_matrix(int r, int c);

void scan_matrix(struct matrix *m);

struct matrix *create_matrix(void);

void free_matrix(struct matrix *m);

void print_matrix(const struct matrix *m);

struct matrix *copy_matrix(const struct matrix *m);

struct matrix *scalar_mult(const struct matrix *m, float c);

struct matrix *add_matrix(const struct matrix *m1, const struct matrix *m2);

struct matrix *matrix_mult(const struct matrix *m1, const struct matrix *m2);
  
struct matrix *trans(const struct matrix *m);

struct matrix *del_rc(const struct matrix *m, int r, int c);

float det(const struct matrix *m);

struct matrix *inverse(const struct matrix *m);

struct matrix *swap_row(int nr, int i, int j);

struct matrix *mult_row(int nr, int i, float c);

struct matrix *add_mult(int nr, int i, int j, float c);

int float_zero(const float f);

void rref(const struct matrix *m);    

