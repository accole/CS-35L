#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//error handling for invalid inputs
void checkSTD(){
  if (ferror(stdin)){
    fprintf(stderr, "Error: Bad Input");
    exit(1);
  }
}

int main(int argc, char **argv){
  //test the numer of arguments
  if (argc != 3){
    fprintf(stderr, "Error: Invalid number of args\n");
    exit(1);
  }

  //translation sets from and to
  //use char pointers since we want
  //to only use individual characters, not string
  char *from = argv[1];
  char *to = argv[2];

  //test from and to have same length
  if (strlen(from) != strlen(to)){
    fprintf(stderr, "Error: Invalid arg length\n");
    exit(1);
  }

  //test for duplicates in set1 (from)
  int i = 0;
  int j = 0;
  for (i = 0; i < strlen(from); i++){
    for (j = i + 1; j < strlen(from); j++){
      if (from[i] == from[j]){
	fprintf(stderr, "Error: Duplicate in set1\n");
	exit(1);
      }
    }
  }

  //get each character from stdin and if it's in
  //from, ouput corresponding to value, otherwise
  //return the character (all to stdout)
  char curr = getchar();
  //check the input
  checkSTD();
  //until no more characters left,
  while(!feof(stdin)){
    for (i = 0; i < strlen(from); i++){
      if (curr == from[i]){
        curr = to[i];
	break;
      }
    }
    putchar(curr);
    curr = getchar();
    checkSTD();
  }

  //exit successfully
  return 0;
}
