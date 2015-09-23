//matrix_plus.c

/**

##  ##     ##      ####
##  ##    #  #    ##  ##
######   ######   ##  ##
##  ##   #    #   ##  ##
##  ##   #    #    ####

*/

#include "matrix_plus.h"


struct matrix *new_matrix(int r, int c) {
    struct matrix *m = malloc(sizeof(struct matrix));
    m->nr = r;
    m->nc = c;
    m->data = malloc(sizeof(float *)*r);
    for (int i = 0; i<r; ++i) {
        m->data[i] = malloc(sizeof(float)*c);
        for (int j = 0; j<c; ++j) {
            m->data[i][j] = 0;
        }
    }
    return m;
}

void scan_matrix(struct matrix *m) {
    printf("Scan matrix %d by %d:\n", m->nr, m->nc);
    for (int i = 0; i < m->nr; ++i) {
        for (int j = 0; j < m->nc; ++j) {
            scanf("%f", &(m->data[i][j]));
        }
    }
    printf("\n");
}

struct matrix *create_matrix(void) {
    int r, c;
    printf("number of rows:\n");
    scanf("%d", &r);
    printf("number of cols:\n");
    scanf("%d", &c);
    struct matrix *m = new_matrix(r, c);
    scan_matrix(m);
    return m;
}

void free_matrix(struct matrix *m) {
    for (int i = 0; i < m->nr; ++i) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void print_matrix(const struct matrix *m) {
    for (int i = 0; i < m->nr; ++i) {
        for (int j = 0; j < m->nc; ++j) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



struct matrix *copy_matrix(const struct matrix *m) {
    struct matrix *cpy = new_matrix(m->nr, m->nc);
    for (int i = 0; i < m->nr; ++i) {
        for (int j = 0; j < m->nc; ++j) {
            cpy->data[i][j] = m->data[i][j];
        }
    }
    return cpy;
}

struct matrix *scalar_mult(const struct matrix *m, float c) {
    struct matrix *sm = new_matrix(m->nr, m->nc);
    for (int i = 0; i < m->nr; ++i) {
        for (int j = 0; j < m->nc; ++j) {
            sm->data[i][j] = m->data[i][j] * c;
        }
    }
    return sm;
}

struct matrix *add_matrix(const struct matrix *m1, const struct matrix *m2) {
    struct matrix *m = new_matrix(m1->nr, m2->nc);
    for (int i = 0; i < m->nr; ++i) {
        for (int j = 0; j < m->nc; ++j) {
            m->data[i][j] = m1->data[i][j] + m2->data[i][j];
        }
    }
    return m;
}

struct matrix *matrix_mult(const struct matrix *m1, const struct matrix *m2) {
    struct matrix *m = new_matrix(m1->nr, m2->nc);
    for (int i = 0; i < m->nr; ++i) {
        for (int j = 0; j < m->nc; ++j) {
            for (int k = 0; k < m1->nc; ++k) {
         m->data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }
    return m;
}
  
struct matrix *trans(const struct matrix *m) {
    struct matrix *t = new_matrix(m->nc, m->nr);
    for (int i = 0; i < t->nr; ++i) {
        for (int j = 0; j < t->nc; ++j) {
            t->data[i][j] = m->data[j][i];
        }
    }
    return t;
}

struct matrix *del_rc(const struct matrix *m, int r, int c) {
    struct matrix *d = new_matrix(m->nr-1, m->nc-1);
    for (int i = 0; i < d->nr; ++i) {
        for (int j = 0; j < d->nc; ++j) {
            if (i<r) {
                if(j<c) {
                    d->data[i][j] = m->data[i][j];
                } else {
                    d->data[i][j] = m->data[i][j+1];
                }
            } else {
                if(j<c) {
                    d->data[i][j] = m->data[i+1][j];
                } else {
                    d->data[i][j] = m->data[i+1][j+1];
                }
            }
        }
    }
    return d;
}




float det(const struct matrix *m) {
    if (m->nr == 1) {
        return m->data[0][0];
    }
    float d = 0;
    for (int j = 0; j<m->nc; ++j) {
        struct matrix *del = del_rc(m, 0, j);
        d += pow(-1, j) * m->data[0][j] * det(del);
        free_matrix(del);
    }
    return d;
}

struct matrix *inverse(const struct matrix *m) {
    float d = det(m);
    struct matrix *inv = new_matrix(m->nr, m->nc);
    for (int i = 0; i<m->nr; ++i) {
        for (int j = 0; j<m->nc; ++j) {
            struct matrix *del = del_rc(m, j, i);
            //print_matrix(del);
            inv->data[i][j] = pow(-1, i+j) * det(del) / d;
            free_matrix(del);
        }
    }
    return inv;
}

struct matrix *swap_row(int nr, int i, int j) {
    if (i >= nr || j >= nr) return NULL;
    struct matrix *sr = new_matrix(nr, nr);
    for (int k = 0; k < nr; ++k) {
        if (k == i) {
            sr->data[k][j] = 1;
        } else if (k == j) {
            sr->data[k][i] = 1;
        } else {
            sr->data[k][k] = 1;
        }
    }
    return sr;
}

struct matrix *mult_row(int nr, int i, float c) {
    if (i >= nr) return NULL;
    struct matrix *mr = new_matrix(nr, nr);
    for (int k = 0; k < nr; ++k) {
        if (k == i) {
            mr->data[k][k] = c;
        } else {
            mr->data[k][k] = 1;
        }
    }
    return mr;
}

struct matrix *add_mult(int nr, int i, int j, float c) {
    if (i >= nr || j >= nr) return NULL;
    struct matrix *am = new_matrix(nr, nr);
    for (int k = 0; k < nr; ++k) {
        if (k == i) {
            am->data[k][k] = 1;
            am->data[k][j] = c;
        } else {
            am->data[k][k] = 1;
        }
    }
    return am;
}


int float_zero(const float f) {
    if (-0.00000000001 < f && f < 0.00000000001) return 1;
    else return 0;
}


void rref(const struct matrix *m) {
    printf("doing RREF...\n");
    int nr = m->nr;
    int nc = m->nc;
    struct matrix *cpy = copy_matrix(m);
    struct matrix *old = cpy;
    int j = 0;
    for(int i = 0; i < nr; ++i) {
        for ( ; j < nc; ++j) {
            if (float_zero(cpy->data[i][j])) {
                int k;
                for (k = i + 1; k < nr && float_zero(cpy->data[k][j]); ++k) {}
                if (k < nr) {
                    struct matrix *sr = swap_row(nr, i, k);
                    print_matrix(sr);
                    old = cpy;
                    cpy = matrix_mult(sr, cpy);
                    printf("our matrix so far...\n");// 
                    print_matrix(cpy); //
                    free_matrix(old);
                    free_matrix(sr);
                }
            }
            if (!float_zero(cpy->data[i][j])) {
                if (!float_zero(cpy->data[i][j]-1)) {
                     struct matrix *mr = mult_row(nr, i, 1.0/cpy->data[i][j]);
                    print_matrix(mr);
                    old = cpy;
                    cpy = matrix_mult(mr, cpy);
                    printf("our matrix so far...\n");// 
                    print_matrix(cpy); //
                    free_matrix(old);
                    free_matrix(mr);
                }
                for (int l = 0; l < nr; ++l) {
                    float lj = cpy->data[l][j];
                    //printf("%f\n", lj);
                    if ((l != i) && !float_zero(lj)) {
                        struct matrix *am = add_mult(nr, l, i, 0.0 - lj);
                        print_matrix(am);
                        old = cpy;
                        cpy = matrix_mult(am, cpy);
                        printf("our matrix so far...\n");//
                        print_matrix(cpy); //
                        free_matrix(old);
                        free_matrix(am);
                    }
                }
                break;
            }
        }
    }
    printf("RREF:\n");// 
    print_matrix(cpy);
    free_matrix(cpy);
    printf("RREF is done!\n");
}






