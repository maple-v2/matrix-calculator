#include "mymat.h"

/*
 * main function - matrix calculator
 *
 * this program initializes a set of 6 predefined matrices with zeros and
 * enters an infinite loop waiting for user commands.
 * The user can perform the following operations:
 * - read_mat
 * - print_mat
 * - add_mat
 * - sub_mat
 * - mul_mat
 * - mul_scalar
 * - trans_mat
 * - stop
 *
 * the program performs error checking for invalid syntax,
 * undefined matrix names, illegal/missing commas, missing arguments,
 * and incorrect command usage.
 */
int main() {
  mats m[MSIZE];     /* array of matrix structs */
  mat matrix[MSIZE]; /* array of 6 matrices */
  char command[MAX]; /* buffer to hold full command input */
  char func[20], arg1[20], arg2[20], arg3[20],
      extra[20];              /* broken down for the command and matrix name  */
  float scalar;               /* Scalar value  */
  int index1, index2, index3; /* indexes of matrices */
  mats *selected;             /* pointer to selected matrix */
  char *rest;                 /* pointer to rest of the command string */
  int i;

  init_mats(m, matrix); /* initialize matrix names and set values to zero */
  intro(); /*gives intro to how the user should use the calculator*/
  while (TRUE) {
    printf("Enter command or type 'stop' to quit:\n\n");

  if (fgets(command, sizeof(command), stdin) == NULL) {
  printf("error, EOF reached. Exiting.\n");
  break;
}

command[strcspn(command, "\n")] = '\0';   /* remove newline */
trimLeadingSpaces(command);               /*  remove leading spaces */

if (command[0] == '\0') {
  printf(" whitespace-only input.\n\n");
  continue;
}

printf("the command is: %s\n\n", command);

sscanf(command, "%19s", func);            /*  command keyword */
removeSpaces(func);   
    /* check for consecutrive commas after the command */
    if (hasIllegalCommas(command)) {
      MULTIPLECONSECUTIVECOMMAS;
      continue;
    }
    /* check if the string ends with comma */
    if (endsWithComma(command)) {
      EXTRANEOUSTEXT;
      continue;
    }
    /* check for illegal comma after the command */
    if (illegalComma(command)) {
      ILLEGEALCOMMA;
      continue;
    }
    /* check for If missing commas when needed */
    if (checkWhitespaceFollowedByComma(command)) {
      MISSINGCOMMA;
      continue;
    }

    /* check if arguments are missing for add,mul,sub and scalar mul operations */
    if ((strcmp(func, "add_mat") == SAME || strcmp(func, "sub_mat") == SAME ||
         strcmp(func, "mul_mat") == SAME||strcmp(func, "mul_scalar") == SAME) &&
        sscanf(command, "%19s %19[^,] , %19[^,] , %19s", func, arg1, arg2,
               arg3) < LEGALLENGTHFOURSLICES) {
      MISSINGARGUMENT;
      continue;
    }

    /* check if arguments are too many for add,mul,sub and scalar mul operations */
    else if (sscanf(command, "%19s %19[^,] , %19[^,] ,%19[^,] , %19s", func, arg1, arg2,
                    arg3,extra) > LEGALLENGTHFOURSLICES &&
             (strcmp(func, "add_mat") == SAME ||
              strcmp(func, "sub_mat") == SAME ||
              strcmp(func, "mul_mat") == SAME||
           strcmp(func, "mul_scalar") == SAME)) {
      EXTRANEOUSTEXT;
      continue;
    }

    /* transpose matrix command checks */
    else if (sscanf(command, "%19s %19[^,] , %19s", func, arg1, arg2) <
                 LEGALLENGTHTHREESICES &&
             strcmp(func, "trans_mat") == SAME) {
      MISSINGARGUMENT;
      continue;
    } else if (sscanf(command, "%19s %19[^,] , %19[^,] , %19s", func, arg1,
                      arg2, extra) > LEGALLENGTHTHREESICES &&
               strcmp(func, "trans_mat") == SAME) {
      EXTRANEOUSTEXT;
      continue;
    }

    /* print_mat command validation */
    else if (sscanf(command, "%19s %19s", func, arg1) < LEGALLENGTHTWOSILCES &&
             strcmp(func, "print_mat") == SAME) {
      MISSINGARGUMENT;
      continue;
    } else if (sscanf(command, "%19s %19[^,]  , %19s", func, arg1, extra) >
                   LEGALLENGTHTWOSILCES &&
               strcmp(func, "print_mat") == SAME) {
      EXTRANEOUSTEXT;
      continue;
    }

    /* stop command should not take arguments */
    else if (sscanf(command, "%19s %19s", func, extra) > LEGALONESLICE &&
             strcmp(func, "stop") == SAME) {
      EXTRANEOUSTEXT;
      continue;
    }

    /* print_mat execution */
    if (strncmp(command, "print_mat", FIRSTNINE) == SAME) {
      int found = MISSING;
      rest = strchr(command, ' ');
      if (rest == NULL) {
        MISSINGARGUMENT;
        continue;
      }
      rest++;
      while (isspace(*rest)) {
        rest++;
      }

      for (i = 0; i < MSIZE; i++) {
        size_t len = strlen(m[i].name);
        if (strncmp(rest, m[i].name, len) == SAME &&
            (rest[len] == ',' || rest[len] == '\0' || isspace(rest[len]))) {
          found = i;
          print_mat(&m[i]);
          break;
        }
      }
      if (found == MISSING) {
        UNDEFINEDMATRIXNAME;
        continue;
      }
    }

    /* read_mat execution and argument validation */
    else if (strncmp(command, "read_mat", FIRSTEIGHT) == SAME) {
      int found = FALSE;
      rest = strchr(command, ' ');
      if (rest == NULL) {
        MISSINGARGUMENT;
        continue;
      }

      rest++;
      while (isspace(*rest))
        rest++;

      for (i = 0; i < MSIZE; i++) {
        size_t len = strlen(m[i].name);
        size_t inputLen = strlen(rest);
        if (strncmp(rest, m[i].name, len) == SAME &&
            (rest[len] == ',' || rest[len] == '\0' || isspace(rest[len]))) {
          found = TRUE;

          if (allDigits(rest, SIX, inputLen) == FALSE) {
            ARGUMENTERROR;
            break;
          }
          if (rest[len] == '\0') {
            MISSINGARGUMENT;
            break;
          }

          if (checkWhitespaceFollowedByComma(rest)) {
            MISSINGCOMMA;
            break;
          }

          selected = read_mat(m, rest);
          print_mat(selected);
          break;
        }
      }
      if (!found) {
        UNDEFINEDMATRIXNAME;
        continue;
      }
    }

    else if (sscanf(command, "%19s %19[^,] , %19[^,] , %19s", func, arg1, arg2,
                    arg3) == LEGALLENGTHFOURSLICES) {

      char *endptr;

      removeSpaces(arg1);
      removeSpaces(arg2);
      removeSpaces(arg3);

      /* Find matrix indices */
      index1 = findIndex(arg1, m);
      index2 = findIndex(arg2, m);
      index3 = findIndex(arg3, m);

      if (strcmp(func, "mul_scalar") == SAME) {
        /* Validate scalar conversion */
        scalar = strtod(arg2, &endptr);
        if (endptr == arg2 || *endptr != '\0') {
          NOTASCALAR; /* scalar is invalid */
          continue;
        }

        if (index1 == MISSING || index3 == MISSING) {
          UNDEFINEDMATRIXNAME;
          continue;
        }

        mul_scalar(&m[index1], (float)scalar, &m[index3]);
        print_mat(&m[index3]);
      } else {
        if (index1 == MISSING || index2 == MISSING || index3 == MISSING) {
          UNDEFINEDMATRIXNAME;
          continue;
        }
/*add ,mul,sub oppretors*/
        if (strcmp(func, "add_mat") == SAME) {
          add_mat(&m[index1], &m[index2], &m[index3]);
          printf("You added %s and %s, and saved the result in %s.\n",
                 m[index1].name, m[index2].name, m[index3].name);
          print_mat(&m[index3]);
        } else if (strcmp(func, "sub_mat") == SAME) {
          sub_mat(&m[index1], &m[index2], &m[index3]);
          printf("You subtracted %s and %s, and saved the result in %s.\n",
                 m[index1].name, m[index2].name, m[index3].name);
          print_mat(&m[index3]);
        } else if (strcmp(func, "mul_mat") == SAME) {
          mul_mat(&m[index1], &m[index2], &m[index3]);
          printf("You multiplied %s and %s, and saved the result in %s.\n",
                 m[index1].name, m[index2].name, m[index3].name);
          print_mat(&m[index3]);
        } else {
          UNDEFINEDCOMMANDNAME;
        }
      }
    }

    /* transpose matrix */
    else if (sscanf(command, "%19s %19[^,] , %19s", func, arg1, arg2) ==
             LEGALLENGTHTHREESICES) {
      removeSpaces(arg1);
      removeSpaces(arg2);

      index1 = findIndex(arg1, m);
      index3 = findIndex(arg2, m);
      if (index1 == MISSING || index3 == MISSING) {
        UNDEFINEDMATRIXNAME;
        continue;
      }

      if (strcmp(func, "trans_mat") == SAME) {
        trans_mat(&m[index1], &m[index3]);
        printf("you transposed  %s , and saved the result in %s.\n",
               m[index1].name, m[index3].name);
        print_mat(&m[index3]);
      } else {
        UNDEFINEDCOMMANDNAME;
      }
    }

    /* exit program */
    else if (strcmp(command, "stop") == SAME) {
      stop();
    }

    /* unknown command if it doesnt match */
    else {
      UNDEFINEDCOMMANDNAME;
    }
  }

  return 0;
}
