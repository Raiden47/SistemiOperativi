#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 100

int main (){
  char *array [N];
  char *s;


  for (int i = 0 ; i < 4 ; i += 1){
    printf(">> ");
    fgets(s,256,stdin);
    array[i] = s;
    //strcpy(array[i],s);
  }
  for (int i = 0 ; i < 4 ; i += 1)
    printf("%s\n",array[i]);

  return 0;
}


//****** ARRAY DI INTERI ******
// int array[N];
// srand(time(NULL));
//
// for (int i = 0 ; i < N ; i += 1)
//   array[i] = rand() %10 + 1;
//
// for (int i = 0 ; i < N ; i += 1)
//   printf("%d ",array[i]);
