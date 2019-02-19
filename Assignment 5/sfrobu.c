//Adam Cole
//UID: 004912373
//Lab 6

//sfrobu.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

//global variable for -f option
int fOp = 0;

//convert characters from frob
//info from memfrob hyperlink in spec
//if character is lowercase and the -f
//option is toggled, use toupper to convert
//the character as well
int f(char c) {
  c = c ^ 42;
  if (islower(c) && fOp == 1){
    c = toupper((unsigned char)c);
  }
  return c;
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
void checkSTD(ssize_t s_in){
  if (s_in == -1){
    fprintf(stderr, "Error: Bad Input");
    exit(1);
  }
}



int main(int argc, char **argv) {

  //test if the -f option is there or not
  if (argc >= 2){
    if (!strncmp(argv[1], "-f", 2)){
      fOp = 1;
    }
  }

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
  char* currp = &curr;

  //continually take the next character until the
  //end of file is reached
  int inp = 1;
  while(inp != 0) {
    //get next character and check the input
    inp = read(STDIN_FILENO, currp, 1);
    checkSTD(inp);
    //end of the input
    if(numc1 > 0 && (curr == ' ' || inp == 0)) {
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
      inp = write(STDOUT_FILENO, &c2[i][j], 1);
      checkSTD(inp);
      if (c2[i][j] == ' '){
	break;
      }
    }
  }

  //free the entries
  for (i = 0; i < numc2; i++){
    free(c2[i]);
  }
  //and then the c strings
  free(c2);
  free(c1);
  //exit code sucessfully
  exit(0);
}
