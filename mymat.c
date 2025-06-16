
#include "mymat.h"

/* reads a matrix name and up to 16 float values into matrix */
mats *read_mat(mats *m, char *input) {
  char *token;
  float value;
  int index, count = 0;
  char matName[6];

  token = strtok(input, ","); /* get matrix name */
  if (token != NULL) {
    strncpy(matName, token, 5); /* copy matrix name (max 5 chars) */
    matName[5] = '\0';          /* Null-terminate */
  }

  index = findIndex(matName, m); /* find index of matrix by name */

  /* read up to 16 float values and fill matrix */
  while ((token = strtok(NULL, ",")) && count < SIZE * SIZE) {
    value = atof(token); /* convert string to float */
    (*m[index].mat)[count / SIZE][count % SIZE] = value; /* assign to matrix */
    count++;
  }

  return &m[index]; /* return pointer to matrix struct */
}

/* prints the contents of a matrix  */
void print_mat(mats *m) {
  int rows, cols;

  printf(" The matrix of name %s is:\n\n", m->name);
  for (rows = 0; rows < SIZE; rows++) {
    for (cols = 0; cols < SIZE; cols++) {
      printf("%10.2f", (*m->mat)[rows][cols]); /* print value with 2 decimals */
    }
    printf("\n");
  }
}

/* adds two matrices and stores result in third */
void add_mat(mats *a, mats *b, mats *c) {
  int i, j;
  mat temp;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      temp[i][j] = (*a->mat)[i][j] + (*b->mat)[i][j];
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      (*c->mat)[i][j] = temp[i][j];
}

/* subtracts matrix b from matrix a and stores result in c */
void sub_mat(mats *a, mats *b, mats *c) {
  int i, j;
  mat temp;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      temp[i][j] = (*a->mat)[i][j] - (*b->mat)[i][j];
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      (*c->mat)[i][j] = temp[i][j];
}

/* multiplies two matrices and stores result in third */
void mul_mat(mats *a, mats *b, mats *c) {
  int i, j, k;
  mat temp = {0}; /* initialize temporary result matrix to 0 */
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++) {
      temp[i][j] = 0;
      for (k = 0; k < SIZE; k++)
        temp[i][j] += (*a->mat)[i][k] * (*b->mat)[k][j];
    }
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      (*c->mat)[i][j] = temp[i][j];
}

/* multiplies matrix a by a scalar and stores result in c */
void mul_scalar(mats *a, float scalar, mats *c) {
  int i, j;
  mat temp;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      temp[i][j] = (*a->mat)[i][j] * scalar;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      (*c->mat)[i][j] = temp[i][j];
}

/* transposes matrix a and stores result in c */
void trans_mat(mats *a, mats *c) {
  int i, j;
  mat temp;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      temp[i][j] = (*a->mat)[j][i];
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      (*c->mat)[i][j] = temp[i][j];
}

/* stops the program */
void stop(void) { exit(0); }
