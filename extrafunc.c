#include "mymat.h"
/* displays an introduction and usage guide for the matrix calculator */
void intro() {
  printf("Welcome to the Matrix Calculator!\n\n");
  printf("Available matrices: MAT_A to MAT_F\n");
  printf(
      "Supported commands: read_mat, print_mat, add_mat, sub_mat, mul_mat,\n");
  printf("mul_scalar, trans_mat, stop\n\n");

  printf("* Note: Input lines must be no longer than 80 characters.\n\n");

  printf("Command Guide:\n\n");

  printf("1. read_mat - Loads up to 16 numbers into a matrix (unused values "
         "are 0).\n");
  printf("   Usage: read_mat MAT_X, val1, val2, ..., val16\n");
  printf("   * MAT_X is one of MAT_A to MAT_F\n");
  printf("   * Requires a space/tab before the matrix name\n");
  printf("   * Each number must be followed by a comma (except the last)\n\n");

  printf("2. print_mat - Displays the contents of a matrix.\n");
  printf("   Usage: print_mat MAT_X\n");
  printf("   * Only spaces/tabs allowed after the matrix name\n\n");

  printf("3. add_mat - Adds two matrices and stores the result in a third.\n");
  printf("   Usage: add_mat MAT_X, MAT_Y, MAT_Z\n\n");

  printf("4. sub_mat - Subtracts MAT_Y from MAT_X and stores the result in "
         "MAT_Z.\n");
  printf("   Usage: sub_mat MAT_X, MAT_Y, MAT_Z\n\n");

  printf("5. mul_mat - Multiplies two matrices and stores the result.\n");
  printf("   Usage: mul_mat MAT_X, MAT_Y, MAT_Z\n\n");

  printf("6. mul_scalar - Multiplies a matrix by a number and stores the "
         "result.\n");
  printf("   Usage: mul_scalar MAT_X, scalar, MAT_Z\n\n");

  printf("7. trans_mat - Transposes a matrix and stores the result.\n");
  printf("   Usage: trans_mat MAT_X, MAT_Y\n\n");

  printf("8. stop - Exits the program.\n");
  printf("   Usage: stop\n\n");
}

/* initializes matrix structures with names and zeroed matrices */
void init_mats(mats *m, mat *matrix) {
  const char *names[] = {"MAT_A", "MAT_B", "MAT_C", "MAT_D", "MAT_E", "MAT_F"};
  int i = 0;
  for (i = 0; i < MSIZE; i++) {
    m[i].name = (char *)names[i]; /* assign name to each matrix */
    m[i].mat = &matrix[i];        /* assign pointer to matrix data */
  }
  for (i = 0; i < MSIZE; i++) {
    memset(m[i].mat, 0, sizeof(mat)); /* initialize all values to 0 */
  }
}

/* finds the index of a matrix name in the matrix array */
int findIndex(const char *name, mats *m) {
  int i;
  for (i = 0; i < MSIZE; i++) {
    if (strcmp(m[i].name, name) == 0) {
      return i;
    }
  }
  return MISSING; /* not found */
}

/* checks for illegal commas two commas or more separated only by spaces */
int hasIllegalCommas(const char *s) {
  while (*s) {
    if (*s == ',') {
      s++;
      while (*s == ' ') {
        s++; /* skip spaces */
      }
      if (*s == ',') {
        return TRUE; /* ture if found illegal  comma */
      }
    } else {
      s++;
    }
  }
  return FALSE;
}
/* checks if all characters in a substring are digits, whitespace, or commas */
int allDigits(const char *str, int start, int len) {
  int i;
  int dotSeen = 0;   /* Flag: whether '.' has appeared in current token */
  int minusSeen = 0; /* Flag: whether '-' has appeared in current token */
  int inToken = 0;   /* Flag: whether currently inside a number token */

  for (i = start; i < len; i++) {
    char ch = str[i];

    if (isdigit(ch)) {
      /* Digit is always valid, mark we are inside a token */
      inToken = 1;
    } else if (ch == '.') {
      /*
       * Decimal point '.' rules:
       * - Allowed only once per token (check dotSeen)
       * - If at start of token (inToken == 0), next character must be digit
       * - Dot itself counts as part of token
       */
      if (dotSeen) {
        return FALSE; /* invalid: multiple dots in token */
      }
      if (inToken == 0) {
        /* Check next character exists and is digit */
        if (i + 1 >= len || !isdigit(str[i + 1])) {
          return FALSE; /* invalid: '.' not followed by digit */
        }
      }
      dotSeen = 1;
      inToken = 1;
    } else if (ch == '-') {
      /*
       * Minus sign '-' rules:
       * - Allowed only once per token (minusSeen)
       * - Allowed only at start of token (inToken == 0)
       */
      if (inToken || minusSeen) {
        return FALSE; /* invalid '-' position or repeated */
      }
      minusSeen = 1;
    } else if (ch == ',' || isspace((unsigned char)ch)) {
      /*
       * Comma or whitespace ends the current token,
       * so reset all flags to allow new token to start.
       */
      dotSeen = 0;
      minusSeen = 0;
      inToken = 0;
    } else {
      /* Any other character is invalid */
      return FALSE;
    }
  }

  /* If no invalid characters or formatting found, return TRUE */
  return TRUE;
}

/* checks if whitespace is followed  by a comma */
int checkWhitespaceFollowedByComma(const char *st) {
  char *s = strchr(st, ' ');
  if (s == NULL) {
    return FALSE;
  }

  s++;
  while (isspace((unsigned char)*s)) {
    s++;
  }

  while (*s && *(s + 1)) {
    if (isspace((unsigned char)*s)) {
      if (*(s - 1) == ',') {
        return FALSE;
      }
      s++;
      if (!isspace((unsigned char)*s) && *s != ',')
        return TRUE;
    } else {
      s++;
    }
  }
  return FALSE;
}
/* Checks if the given string ends with a comma  */
int endsWithComma(const char *str) {
  size_t len = strlen(str);
  if (len == 0)
    return 0;

  while (len > 0 && isspace(str[len - 1]))
    len--;

  return (len > 0 && str[len - 1] == ',');
}
/* Checks for illegal comma usage before or after whitespace */
int illegalComma(const char *st) {
  char *str = strchr(st, ' ');
  if (str == NULL) {
    return FALSE;
  }
  if (str != st && *(str - 1) == ',') {
    return TRUE;
  }
  str++;
  while (isspace((unsigned char)*str)) {
    str++;
  }

  if (*str == ',') {
    return TRUE;
  }

  return FALSE;
}
void removeSpaces(char str[]) {
  int i, j = 0;
  /*creates anew string without spaces*/
  for (i = 0; str[i] != '\0'; i++) {
    if (!isspace((unsigned char)str[i])) {
      str[j++] = str[i];
    }
  }

  str[j] = '\0'; /* ending the new string*/
}
void trimLeadingSpaces(char *str) {
    char *start = str;

    /* Skip leading whitespace characters */
    while (isspace((unsigned char)*start)) {
        start++;
    }

    /* Shift the string left */
    if (start != str) {
        strcpy(str, start);
    }
}
