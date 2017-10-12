/**Author:21300505 LEE Kihyuk, 21500788 HEO Kyujin, 21600137 KIM Jongseong*/
#include "z3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define SIZE 9

int main() {
   FILE *finput, *fformula; //according txt file

   finput = fopen("input.txt", "r");
   if (finput == NULL) {
      printf("input file open is not successful\n");
      return-1;
   }

   fformula = fopen("formula.txt", "w");

   int i, j, n, r, s, m, index, astfornum;
   int astnum = 0;
   int formulacnt = 0; //counts the number of formulas
   char ary[SIZE][SIZE] = { 0 }; //first array for storing question
   char ans[SIZE][SIZE][SIZE] = { '0' }; //array to hold variable value
   char ch;


   //reading and storing sudoku question to array
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         fscanf(finput, "%c", &ary[i][j]);
         fgetc(finput);
      }
   }

   //printing sudoku question
   printf("The sudoku question is \n");
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         printf("%c ", ary[i][j]);
         if (ary[i][j] == '*') {
            astnum++;
         }
      }
      printf("\n");
   }

   printf("\n\n");

   //copying array to variables with binary(3-d)
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         for (n = 0; n < SIZE; n++) {
            if (ary[i][j] == n + '1') {
               ans[i][j][n] = '1';
               formulacnt++;
            }
            else if (ary[i][j] == '*')
               ans[i][j][n] = '*';
            else
               ans[i][j][n] = '0';
         }
      }
   }

   //counting asterisk formula number
   if (astnum = 4)
      astfornum = 6;
   else if (astnum = 3)
      astfornum = 3;
   else if (astnum = 2)
      astfornum = 1;
   else
      astfornum = 0;

   //printing format of formula.txt
   fprintf(fformula, "p cnf 729\n");

   //printing formula what was given
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         for (n = 0; n < SIZE; n++) {
            if (ans[i][j][n] == '1') {
               fprintf(fformula, "%d 0\n", (81 * i) + (9 * j) + n + 1);
            }
         }
      }
   }

   //printing formula at least one number in one row
   for (i = 0; i < SIZE; i++) {
      for (n = 0; n < SIZE; n++) {
         for (j = 0; j < SIZE; j++) {
            fprintf(fformula, "%d ", (81 * i) + (9 * j) + n + 1);
         }
         fprintf(fformula, "0\n");
      }
   }

   //printing formula at least one number in one column
   for (j = 0; j < SIZE; j++) {
      for (n = 0; n < SIZE; n++) {
         for (i = 0; i < SIZE; i++) {
            fprintf(fformula, "%d ", (81 * i) + (9 * j) + n + 1);
         }
         fprintf(fformula, "0\n");
      }
   }

   //printing formula at least one number in one block
   for (r = 0; r < 3; r++) {
      for (s = 0; s < 3; s++) {
         for (n = 0; n < SIZE; n++) {
            for (i = 0; i < SIZE / 3; i++) {
               for (j = 0; j < SIZE / 3; j++) {
                  fprintf(fformula, "%d ", (81 * (3 * r + i)) + (9 * (3 * s + j)) + n + 1);
               }
            }
            fprintf(fformula, "0\n");
         }
      }
   }

   //printing formula of only one value per cell
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         for (n = 0; n < SIZE - 1; n++) {
            for (m = n + 1; m < SIZE; m++) {
               fprintf(fformula, "%d ", -((81 * i) + (9 * j) + n + 1));
               fprintf(fformula, "%d ", -((81 * i) + (9 * j) + m + 1));
               fprintf(fformula, "0\n");
            }
         }
      }
   }

   //printing formula of only one value per column
   for (j = 0; j < SIZE; j++) {
      for (n = 0; n < SIZE; n++) {
         for (i = 0; i < SIZE - 1; i++) {
            for (m = i + 1; m < SIZE; m++) {
               fprintf(fformula, "%d ", -((81 * i) + (9 * j) + n + 1));
               fprintf(fformula, "%d ", -((81 * m) + (9 * j) + n + 1));
               fprintf(fformula, "0\n");
            }
         }
      }
   }

   //printing formula of only one value per row
   for (i = 0; i < SIZE; i++) {
      for (n = 0; n < SIZE; n++) {
         for (j = 0; j < SIZE - 1; j++) {
            for (m = j + 1; m < SIZE; m++) {
               fprintf(fformula, "%d ", -((81 * i) + (9 * j) + n + 1));
               fprintf(fformula, "%d ", -((81 * i) + (9 * m) + n + 1));
               fprintf(fformula, "0\n");
            }
         }
      }
   }

   //storing location of asterisk
   int loc[4][2] = { 0 };
   astnum = 0;

   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         if (ary[i][j] == '*') {
            index = 0;
            loc[astnum][index++] = i + 1;
            loc[astnum++][index] = j + 1;
         }
      }
   }

   //printing formula for asterisk
   index = 0;
   for (i = 0; i < astnum - 1; i++) {
      for (j = astnum - i - 1; j > 0; j--) {
         for (n = 0; n < SIZE; n++) {
            fprintf(fformula, "%d ", -((81 * loc[i][index++]) + (9 * loc[i][index--]) + n + 1));
            fprintf(fformula, "%d ", -((81 * loc[i + j][index++]) + (9 * loc[i + j][index--]) + n + 1));
            fprintf(fformula, "0\n ");
         }
      }
   }

   fclose(finput);
   fclose(fformula);

   //run z3 and get answer to answer.txt file
   system("z3 -dimacs formula.txt > answer.txt");

   FILE *fanswer, *foutput;

   int temp = 0;

   fanswer = fopen("answer.txt", "r");
   if (fanswer == NULL) {
      printf("input file open is not successful\n");
      return-1;
   }

   foutput = fopen("output.txt", "w");

   char str[5];
   fscanf(fanswer, "%s\n", str);
   for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
         for (n = 0; n < SIZE; n++) {
            fscanf(fanswer, "%d ", &temp);
            if (temp > 0) {
               fprintf(foutput, "%d ", temp % 9 == 0 ? 9 : temp % 9);
            }
         }
      }
      fprintf(foutput, "\n");
   }

   fclose(foutput);

   FILE *showOutput = fopen("output.txt", "r");
   printf("\n==========Solution==========\n");
     if(strncmp(str,"unsat",5)==0){
    printf("*************");
    printf("\nNo Solution\n");
    printf("*************");
     }
   while((ch = fgetc(showOutput)) != EOF){
      printf("%c", ch);
   }
   printf("\n\n");

   fclose(showOutput);
   fclose(fanswer);
   return 0;
}
