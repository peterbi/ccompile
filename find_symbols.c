#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef NULL
#define NULL   ((void *) 0)
#endif
/*
 * These are the global variables that you need to populate in the functions below.
 * Do not change these variables' names or types!
 */
char* function_name;
char* parameter_names[10];
char* variable_names[10];
int varnumber=0;

// declaration for helper function to reset global variables
void reset();


/*
 * This is the function you need to implement for Parts 1 and 3.
 * You must NOT change its signature! 
 */
int parse_function_header(char* header) {
  if (header == NULL) return -1;

  // clean up the global variables - do not remove this line!
  reset();

  // WRITE THE REST OF THIS FUNCTION!
  char linecopy[100];
    strcpy(linecopy, header);

    int toknumber = 0;
    int argnumber = 0;
    char * pch;
    pch = strtok(linecopy, " ");
    //printf("%s\n",pch);
    while(pch!=0){
  	  if(toknumber == 1){
  		  function_name = malloc(sizeof(char)*100);
  		  if(function_name!=NULL){
  			  strcpy(function_name, pch);
  		  }
  	  }
  	  if(toknumber > 3 && toknumber % 3 == 1){
  		  parameter_names[argnumber] = malloc(sizeof(char)*100);
  		  if(parameter_names[argnumber]!=NULL){
  			  strcpy(parameter_names[argnumber], pch);
  			  argnumber++;
  		  }
  	  }
  	  toknumber++;
  	  pch = strtok(NULL, " ");
    }



   // Be sure to return the correct value in Part 3.

  return 1;
}



/*
 * This is the function you need to implement for Parts 2 and 4.
 * You must NOT change its signature! 
 */
int parse_line(char* line) {
  if (line == NULL) return -1;

  // clean up the global variables - do not remove this line!
  //reset();
  char linecopy[100];
  strcpy(linecopy, line);
  // WRITE THE REST OF THIS FUNCTION!
  char *pch;
  pch = strtok(linecopy, " ");

  if (strcmp(pch, "int" )== 0) {
	  pch = strtok(NULL, " "); // check for int;
  }
  while(pch!=NULL){
	  printf("pch is %s\n",pch);
	  variable_names[varnumber]=malloc(sizeof(char)*100);
	  if(variable_names[varnumber]!=NULL){
		  printf("var number is %d\n", varnumber);
		  strcpy(variable_names[varnumber], pch);
		  printf("v[n] is %s\n", variable_names[varnumber]);
		  varnumber++;
		  pch = strtok(NULL, " ");
		  if(strcmp(pch, ";")==0){
		  		  break;
		  	  }else if(strcmp(pch, "=")==0){
		  		  //assignment operator. Check if variable exists. If not, error
		  		  while (strcmp(pch, ";")!=0 && strcmp(pch, ",")!=0){
		  			  pch = strtok(NULL, " "); // strtok until there's a , or ;

		  		  }
		  		  if(strcmp(pch, ";")==0){
		  			  break;
		  		  }else if(strcmp(pch, ",")==0){
		  			  return parse_line(pch+sizeof(char)*2);
		  		  }
		  	  }else if(strcmp(pch, ",")==0){
		  		  //start over
		  		  printf(pch+sizeof(char)*2);
		  		  return parse_line(pch+sizeof(char)*2);
		  	  }
	  }


  }


  // Be sure to return the correct value in Part 4.
  return 1;

}


/*
 * This helper function resets the global variables so we can 
 * check them when grading your assignment.
 * Do not change this function!
 */
void reset() {
  if (function_name != NULL) free(function_name);
  function_name = NULL;
  int i;
  for (i = 0; i < 10; i++) {
    if (parameter_names[i] != NULL) free(parameter_names[i]);
    parameter_names[i] = NULL;
  }
  for (i = 0; i < 10; i++) {
    if (variable_names[i] != NULL) free(variable_names[i]);
    variable_names[i] = NULL;
  }
}

