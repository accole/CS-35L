//Adam Cole


//sfrob.c

#include <stdio.h>
#include <stdlib.h>


//convert characters from frob
//info from memfrob hyperlink in spec
int f(char c) {
  return c ^ 42;
}


//compare the c strings
int frobcmp(char const *a, char const *b) {
  while(*a == *b ){
    if (*a == ' '){
      return 0;
    }
    a++; b++;
  }
  if (*b == ' ' || f(*a) > f(*b)){
    return 1;
  }
  else if (*a == ' ' || f(*a) < f(*b)){
    return -1;
  }
}


//using frobcmp in qsort
int q(const void *a, const void *b){
  return frobcmp(*(const char**) a, *(const char**) b);
}


//error handling for invalid inputs
void checkSTR(){
  if (ferror(stdin)){
    fprintf(stderr, "Error: Bad Input");
    exit(1);
  }
}



int main(void) {
  //get the first character and its double pointer
  //to serve as the current character, and a two dimensional
  //array of characters
  char *c1 = (char*)malloc(sizeof(char));
  char **c2 = (char**)malloc(sizeof(char*));

  //check if they are valid before accessing their memory
  if (c1 == NULL || c2 == NULL){
    fprintf(stderr, "Error: Bad Memory");
    exit(1);
  }

  //create temp variables to hold the length of the
  //c string "arrays" and the current char
  int numc1 = 0;
  int numc2 = 0;
  char curr;

  //continually take the next character until the
  //end of file is reached
  while(!feof(stdin)) {
    //get next character and check the input
    curr = getchar();
    checkSTR();
    //end of the input
    if(numc1 > 0 && (curr == ' ' || feof(stdin) || curr == EOF)) {
      //allocate space for the ' ' at the end of each word
      c1 = (char*)realloc(c1, (numc1 + 1) * sizeof(char));
      //since the end of the word should always act as if there
      //is a corresponding space
      c1[numc1] = ' ';
      //now start the next word input by copying the contents of c2
      //over and re-allocating all the filled memory in c2 to one char
      char *rest = (char*)malloc(sizeof(char));
      c2 = (char**)realloc(c2, (numc2 + 1) * sizeof(char*));
      //and test if either the next word or current ending word have errors
      if(rest != NULL && c2 != NULL) {
	c2[numc2] = c1;
	numc2++;
	c1 = rest;
	numc1 = 0;
      }
      //if it is not the end of the string, or is the first character
      else {
	fprintf(stderr, "Error: Bad memory allocation");
	free(c1);
	exit(1);
      }  
    }
    //not the end of the input
    else {
      //attach the letter to output array
      //by allocating more space in the pointer
      c1 = (char*)realloc(c1, (numc1 + 1) * sizeof(char));
      if(c1 != NULL) {
        //NULL character
	c1[numc1] = curr;
	numc1++;
      }
      else {
	fprintf(stderr, "Error: Bad memory allocation");
	exit(1);
      }
    }
  }


  //index variables
  int i = 0;
  int j = 0;
  //sort the array of output characters
  qsort(c2, numc2, sizeof(char*), q);
  //and print them out
  for (i = 0; i < numc2; i++){
    for (j = 0; c2[i][j] != '\0'; j++){
      if (c2[i][j] == '\0'){
	break;
      }
      putchar(c2[i][j]);
      if (c2[i][j] == ' '){
	break;
      }
    }
  }

  //free the entries
  for (i = 0; i < numc2; i++){
    free(c2[i]);
  }
  //and then the c string
  free(c2);
  //exit code sucessfully
  exit(0);
}
