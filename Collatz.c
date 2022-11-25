#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

//basic collatz calc, goes until it hits 1.
int full(int start, int itter, int printstep){ 
  long long int number;
  int j;
  for(int i = 0; i != itter; i += 1){
    number = start + i;
    j = 0;
    while (number != 1){
      if (number%2 == 0){
        number = number / 2;
      } else {
        number = 3 * number + 1;
      }
      j += 1;
    }
    if (i%printstep == printstep-1){
      printf("up to %i, in %i\n", i+start, j);
    }
  }
}

//any number less than the highest previously calculated number is automatically ignored as it is already confimerd to converge to 1.
//only calculates odds because an even numbers imediately go below the current highest calculated number, which we already know is going to converge.
int opt1(int start, int itter, int printstep){ 
  long long int number, startnum;
  int j, p;
  
  //make start into an odd
  if (start % 2 == 0){
    start += 1;
  }
  for(int i = 0; i < itter || itter == -1; i += 2){
    startnum = start + i;
    number = startnum;
    j = 0;
    p = 0;
    while (number != 1){
      if (number < startnum){
        break;
      }
      if (number%2 == 0){
        number = number / 2;
      } else {
        number = 3 * number + 1;
      }
      j += 1;
    }
    if (p%printstep == 1){
      printf("%i done in %i steps till below max calculated\n", i+start, j);
    }
    p += 1;
  }
}

int main(int argc, char *argv[]) {
  int mode = 0;
  int start = 1;
  int itter = -1; 
  int printstep = 1;
  clock_t starttime, endtime;
  double tottime;
  for (int i = 1; i < argc; i += 2) {
    if (argv[i][0] == '-') {
      switch (argv[i][1]) {
      case 'm':
        mode = atoi(argv[i + 1]);
        break;
      case 's':
        start = atoi(argv[i + 1]);
        break;
      case 'i':
        itter = atoi(argv[i + 1]);
        break;
      case 'p':
        printstep = atoi(argv[i + 1]);
        break;
      default:
        printf(" %s\n"
               "Mode:                    -m char \n"
               "Start_Point:             -s int \n"
               "Itterations:             -i int \n",
               argv[0]);
        return -1;
      }
    } else {
      printf(" %s\n"
               "Mode:                    -m char \n"
               "Start_Point:             -s int \n"
               "Itterations:             -i int \n",
               argv[0]);
        return -1;
    }
  }
  starttime = clock();
  switch (mode) {
      case 0:
        full(start, itter, printstep);
        break;
      case 1:
        opt1(start, itter, printstep);
        break;
      default:
        printf("Invalid Mode %c", mode);
        return -1;
      }
  endtime = clock();
  tottime = ((double) (endtime - starttime)) / CLOCKS_PER_SEC;
  printf("done in %f seconds", tottime);
}