/*
 * matrix Calculator Header
 * this header defines the constants, and function prototypes used
 * in a basic matrix calculator that supports 6 matrices of size 4x4.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4  /* size of square matrices */
#define MSIZE 6 /* number of matrices */
#define MAX 81  /* max length for input line (80 + '\0') */

/* macros for printing  errors */
#define UNDEFINEDMATRIXNAME printf("undefined matrix name.\n\n")
#define UNDEFINEDCOMMANDNAME printf("undefined command name.\n\n")
#define ARGUMENTERROR printf("Argument is not a real number.\n\n")
#define EXTRANEOUSTEXT printf("Extraneous text after end of command.\n\n")
#define MISSINGARGUMENT printf("Missing argument.\n\n")
#define ILLEGEALCOMMA printf("Illegal comma.\n\n")
#define MISSINGCOMMA printf("Missing comma.\n\n")
#define MULTIPLECONSECUTIVECOMMAS printf("Multiple consecutive commas.\n\n")
#define NOTASCALAR printf("Argument is not a scalar.\n\n")

/* --- macros for Constants --- */
#define MISSING -1
#define TRUE 1
#define SAME 0
#define FALSE 0
#define LEGALLENGTHFOURSLICES 4
#define LEGALLENGTHTHREESICES 3
#define LEGALLENGTHTWOSILCES 2
#define LEGALONESLICE 1
#define FIRSTEIGHT 8
#define FIRSTNINE 9
#define FIRSTTEN 10
#define SIX 6

typedef float mat[SIZE][SIZE]; /* 4x4 float matrix */

typedef struct {
  char *name; /* name of the matrix  */
  mat *mat;   /* pointer to the actual matrix data */
} mats;

/* prototypes */

/**
 * @brief reads a matrix name and up to 16 float values from a string and fills
 * the matrix if was more then 16 inputs ignore the rest.
 *
 * @param m array of matrix struct.
 * @param input sperated by commas"
 * @return pointer to the updated matrix struct.
 */
mats *read_mat(mats *m, char *input);

/**
 * @brief prints the contents of the matrix .
 *
 * @param m pointer to the matrix .
 */
void print_mat(mats *m);

/**
 * @brief add the second matrix from the first and stores the result in a third
 * matrix.
 *
 * @param a pointer to the first matrix .
 * @param b pointer to the second matrix.
 * @param c pointer to the result matrix.
 */
void add_mat(mats *a, mats *b, mats *c);

/**
 * @brief subtracts the second matrix from the first and stores the result in a
 * third matrix.
 *
 * @param a pointer to the first matrix .
 * @param b pointer to the second matrix.
 * @param c pointer to the result matrix.
 */
void sub_mat(mats *a, mats *b, mats *c);

/**
 * @brief multiplies two matrices and stores the result in a third matrix.
 *
 * @param a pointer to the first matrix .
 * @param b pointer to the second matrix.
 * @param c pointer to the result matrix.
 */
void mul_mat(mats *a, mats *b, mats *c);

/**
 * @brief multiplies a matrix by a scalar and stores the result in another
 * matrix.
 *
 * @param a pointer to the matrix to multiply.
 * @param scalar the scalar value.
 * @param c pointer to the result matrix.
 */
void mul_scalar(mats *a, float scalar, mats *c);

/**
 * @brief transposes a matrix and stores the result in another matrix.
 *
 * @param a pointer to the matrix to transpose.
 * @param c pointer to the result matrix.
 */
void trans_mat(mats *a, mats *c);

/**
 * @brief exits the program.
 */
void stop(void);

/**
 * @brief displays the welcome message and command usage guide.
 *
 * explains how to use the matrix calculator.
 */
void intro(void);

/**
 * @brief initializes the matrix structures with names with values all zero.
 *
 * @param m array of matrix structures to initialize.
 * @param matrix array of actual matrix data to associate with the structures.
 */
void init_mats(mats *m, mat *matrix);

/**
 * @brief finds the index of a matrix by its name.
 *
 * @param name the name of the matrix .
 * @param m array of matrix structures.
 * @return index of the matrix if found, missing if not found.
 */
int findIndex(const char *name, mats *m);

/**
 * @brief checks for multipale consecutive comma comma usage .
 *
 * @param s the input string to check.
 * @return 1 if  comma sequence is found, 0 if not found consecutive commas.
 */
int hasIllegalCommas(const char *s);

/**
 * @brief checks if all characters in a substring are digits, whitespace or
 * commas.
 *
 * @param str the full input string.
 * @param start start index in the string.
 * @param len End index .
 * @return TRUE if  digits, whitespace or commas, FALSE if not  digits,
 * whitespace or commas.
 */
int allDigits(const char *str, int start, int len);

/**
 * @brief checks if whitespace is followed by a comma .
 *
 * @param st The input string.
 * @return TRUE if illegal missing comma is found, FALSE if not  .
 */
int checkWhitespaceFollowedByComma(const char *st);

/**
 * @brief checks if a string ends with a comma, ignoring trailing whitespace.
 *
 * @param str The input string.
 * @return TRUE if it ends with a comma, FALSE if not found.
 */
int endsWithComma(const char *str);

/**
 * @brief checks for illegal comma usage around whitespace.
 *
 *
 *
 * @param st the input string.
 * @return TRUE if illegal comma usage is found, FALSE if not found.
 */
int illegalComma(const char *st);
/**
 * @brief remove spaces from string.
 *
 *
 *
 * @param st the input string.
 *
 */
void removeSpaces(char str[]);
/**
 * @brief remove spaces from the start of the string.
 *
 *
 *
 * @param st the input string after the spaces removed from the start.
 *
 */
void trimLeadingSpaces(char *str);
