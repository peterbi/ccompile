#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#ifndef NULL
//#define NULL   ((void *) 0)
//#endif
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
    //count the position of "(" to determine whether there is a return type;
    int parent_left = 0;
    pch = strtok(linecopy, " ");
    while(pch!=0){

    		if(strcmp(pch, "(")==0){
    			break;
    		}
    		parent_left++;
    		pch = strtok(NULL, " ");
    } //now parent_left holds the position of "("
    strcpy(linecopy, header);
    if(parent_left==2){//means there is a return type
    		pch = strtok(linecopy, " "); //now pch holds the first word
    		if(strcmp(pch, "int") && strcmp(pch, "void")){
    			printf("ERROR: Return Type can only be int or void or nothing\n");
    			reset();
    			return -1;
    		}

    }else if(parent_left==1){
    		if(!strcmp(pch, "int") || !strcmp(pch, "void")){
    			printf("ERROR: Check function name\n"); //no function name
    	    		reset();
    	    		return -1;
    	    	}
    }else {
    		printf("ERROR: Check function Name\n"); //could mean there are spaces in the function name
    		reset();
    		return -1;
    }
    //now for the function name
    pch = strtok(NULL, " ");
    //printf("pch is %s", pch);
    //while(pch!=0){
  	  if(toknumber == 0){ //
  		  function_name = malloc(sizeof(char)*100);
  		  if(function_name!=NULL){
  			  strcpy(function_name, pch);
  		  }
  	  }
  	  /*
  	  if(toknumber > 3 && toknumber % 3 == 1){
  		  parameter_names[argnumber] = malloc(sizeof(char)*100);
  		  if(parameter_names[argnumber]!=NULL){
  			  strcpy(parameter_names[argnumber], pch);
  			  argnumber++;
  		  }
  	  }*/
  	  //toknumber++;
  	  pch = strtok(NULL, " ");
    //}
  	  //now pch should point to immediately after the (
  	  toknumber = 0;
  	  pch = strtok(NULL, ",");
  	  //printf("%s\n", pch);
  	  while(pch!=0){
  		  //inner loop to check each word pair separated by comma.
  		  if(pch[0]==')'){
  			  printf("ERROR: Useless comma\n");
  			  reset();
  			  return -1;
  		  }
  		  char pair[100]; // stores the type-variable pair
  		  int toknumbersub;
  		  char * pchsub = NULL;
  		  strncpy(pair, pch, 99);
  		  pchsub = strtok(pair, " ");
  		  if(strcmp(pchsub, "int")){//pchsub has to be int;
  			  printf("ERROR: Check Argument %d: type error\n", toknumber);
  			  reset();
  			  return -1;
  		  }
  		  pchsub = strtok(NULL, " ");
  		  if(pchsub == NULL){
  			  printf("ERROR: Check Argument %d: no name\n", toknumber);
  			  reset();
  			  return -1;
  		  }
  		  //this is the parameter name
  		  //check for keywords
  		  if(!strcmp(pchsub, "int") || !strcmp(pchsub, "void") || !strcmp(pchsub, "return")){
  			  printf("ERROR: Check Argument %d: cannot be named int, void or return\n", toknumber);
  			  reset();
  			  return -1;
  		  }
  		  //check if first char is letter
  		  if(pchsub[0]>122 || pchsub[0]<65 || (pchsub[0]>90 && pchsub[0]<97) ){
  			  printf("ERROR: Check Argument %d: can only begin with letter\n", toknumber);
  			  reset();
  			  return -1;
  		  }
  		  parameter_names[argnumber] = malloc(sizeof(char)*100);
  		  if(parameter_names[argnumber]!=NULL){
  		  	  strcpy(parameter_names[argnumber], pchsub);
  		  	  argnumber++;
  		  }
  		  //if there's more, then most likely there's a space in the name
  		  pchsub = strtok(NULL, " ");
  		  if(pchsub != NULL){
  			  printf("%s\n", pchsub);
  		  	  printf("ERROR: Check Argument %d: space in name\n", toknumber);
  		  	  reset();
  		  	  return -1;
  		  }
  		pch = strtok(pch+(strlen(pch)+2), ",){");
  		//printf("%s\n",pch);
  		toknumber++;
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
  reset();
  char linecopy[100];
  strcpy(linecopy, line);
  // WRITE THE REST OF THIS FUNCTION!
  char *pch;
  pch = strtok(linecopy, " ");
  if (strcmp(pch, "int" )== 0) {
	  //treat as declaration statement
	  pch = strtok(NULL, " ");
	  char last [100]; // stores last token type;
	  strcpy(last, "");
	  while(pch!=NULL){
	  	  //printf("pch is %s\n",pch);
	  	  variable_names[varnumber]=malloc(sizeof(char)*100);
	  	  if(variable_names[varnumber]!=NULL){ //check for malloc
	  		  //printf("var number is %d\n", varnumber);
	  		  if(strcmp(pch, "int")==0 || strcmp(pch, "void")==0){
	  			  //illegal identifier name
	  			  printf("ERROR: illegal identifier name %s\n", pch);
	  			  reset();
	  			  return 0;
	  		  }
	  		if(pch[0]>122 || pch[0]<65 || (pch[0]>90 && pch[0]<97) ){
	  		  	printf("ERROR: Can only begin with letter\n");
	  		  	reset();
	  		  	return -1;
	  		  }
	  		  strncpy(variable_names[varnumber], pch, 99);
	  		  //printf("v[n] is %s\n", variable_names[varnumber]);
	  		  varnumber++;
	  	  	  }
	  	  else {
	  		  		  //no space
	  		  		printf("ERROR: malloc failed for %s\n", pch);
	  		  		reset();
	  		  		return 0;
	  		  }
	  		  strcpy(last, pch);//variable name
	  		  pch = strtok(NULL, " ");
	  		  if(pch==NULL || strcmp(pch, ";")==0){
	  			  break;
	  	      }else if(strcmp(pch, "=")==0){
	  			  //assignment operator. Check if variable exists. If not, error
	  	    	  	  pch = strtok(NULL, " ");
	  	    	  	  if(strcmp(pch, ";")==0 || strcmp(pch, ",")==0){
	  	    	  		  printf("ERROR: Need value for %s\n", last);
	  	    	  		  reset();
	  	    	  		  return -1;
	  	    	  	  }
	  	    	  	  strcpy(last, "operand");
	  	    	  	  int count  = 0;
	  			  while (strcmp(pch, ";")!=0 && strcmp(pch, ",")!=0){
	  				  count++;
	  				  printf("%d\n", count);
	  				  //printf("%s\n",pch);
	  				  //until there's a ; or , do this
	  				  if(count>100){
	  					printf("ERROR: Statement must end with ; (semi colon)\n");
	  					reset();
	  					return 0;
	  				  }
	  				  if(strcmp(last, "operand")==0){
	  					  pch = strtok(NULL, " ");//right after variable
	  					  if(strcmp(pch, ";")==0 || strcmp(pch, ",")==0){
	  						  continue;
	  					  }
	  					  //printf("%s\n", pch);
	  					  if(strcmp(pch, "+")!=0){
	  						  //no operator
	  						  printf("ERROR: no operand\n");
	  						  reset();
	  						  return 0;
	  					  }
	  				  }
	  				  pch = strtok(NULL, " "); // strtok until there's a , or ;

	  			  }
	  			  if(strcmp(pch, ";")==0){
	  				  break;
	  			  }else if(strcmp(pch, ",")==0){
	  				  pch = strtok(NULL, " ");
	  				  continue;//return parse_line(pch+sizeof(char)*2);
	  			  }
	  	      }else if(strcmp(pch, ",")==0){
	  			  //start over
	  			  //printf(pch+sizeof(char)*2);
	  			  pch = strtok(NULL, " ");
	  			  continue;
	  			  //return parse_line(pch+sizeof(char)*2);
	  		  }else {
	  			  //this means something other than , ; and = followed the variable.
	  			printf("ERROR: Space in variable name\n");
	  			reset();
	  			return 0;
	  		  }
	  		  pch = strtok(NULL, " ");
	  }
	  if(pch==NULL){
		  //this means exiting without hitting ;
		  printf("ERROR: Statement must end with ; (semi colon)\n");
		  reset();
		  return 0;
	  }
	  //otherwise works fine
	  return 1;

  } else if (strcmp(pch, "return")==0){
	  //treat as return statement
	  pch = strtok(NULL, " ");
	  if(strcmp(pch, ";")==0){
		  return 1;
	  }else{
		  while(pch!=NULL){
			  if(strcmp(pch, "void")==0 || strcmp(pch, "int")==0){
				  printf("ERROR: Return variable illegal");
				  reset();
				  return 0;
			  }else{
				  //assume valid
				  pch = strtok(NULL, " ");

			  }
		  }
	  }
	  return 1;
  } else {
	  //treat as assignment
	  	  char last [100]; // stores last token type;
	  	  strcpy(last, "");
	  	  while(pch!=NULL){
	  	  	  //printf("pch is %s\n",pch);
	  	  	  //variable_names[varnumber]=malloc(sizeof(char)*100);
	  	  		  //printf("var number is %d\n", varnumber);
	  		  	  //check for variable
	  		  	  if(pch[0]=='='){
	  		  		  printf("ERROR: Missing variable name\n");
	  		  		  reset();
	  		  		  return 0;
	  		  	  }
	  	  		  if(strcmp(pch, "int")==0 || strcmp(pch, "void")==0){
	  	  			  //illegal identifier name
	  	  			  printf("ERROR: illegal identifier name %s\n", pch);
	  	  			  reset();
	  	  			  return 0;
	  	  		  //printf("v[n] is %s\n", variable_names[varnumber]);

	  	  		  strcpy(last, pch);//variable name
	  	  		  pch = strtok(NULL, " ");
	  	  		  if(strcmp(pch, ";")==0){
	  	  			  break;
	  	  	      }else if(strcmp(pch, "=")==0){
	  	  			  //assignment operator. Check if variable exists. If not, error
	  	  	    	  	  pch = strtok(NULL, " ");
	  	  	    	  	  if(strcmp(pch, ";")==0){
	  	  	    	  		  printf("ERROR: Need value for %s\n", last);
	  	  	    	  		  reset();
	  	  	    	  		  return -1;
	  	  	    	  	  }
	  	  	    	  	  strcpy(last, "operand");
	  	  			  while (strcmp(pch, ";")!=0 && strcmp(pch, ",")!=0){
	  	  				  //printf("%s\n",pch);
	  	  				  //until there's a ; or , do this
	  	  				  if(strcmp(last, "operand")==0){
	  	  					  pch = strtok(NULL, " ");//right after variable
	  	  					  if(strcmp(pch, ";")!=0 || strcmp(pch, ",")!=0){
	  	  						  continue;
	  	  					  }
	  	  					  if(strcmp(pch, "+")!=0){
	  	  						  //no opera
	  	  						  printf("ERROR: no operand\n");
	  	  						  reset();
	  	  						  return 0;
	  	  					  }
	  	  				  }
	  	  				  pch = strtok(NULL, " "); // strtok until there's a , or ;

	  	  			  }
	  	  			  if(strcmp(pch, ";")==0){
	  	  				  break;
	  	  			  }else if(strcmp(pch, ",")==0){
	  	  				  pch = strtok(NULL, " ");
	  	  				  continue;//return parse_line(pch+sizeof(char)*2);
	  	  			  }
	  	  	      }else if(strcmp(pch, ",")==0){
	  	  			  //start over
	  	  			  //printf(pch+sizeof(char)*2);
	  	  			  pch = strtok(NULL, " ");
	  	  			  continue;
	  	  			  //return parse_line(pch+sizeof(char)*2);
	  	  		  }else {
	  	  			  //this means something other than , ; and = followed the variable.
	  	  			printf("ERROR: Space in variable name\n");
	  	  			reset();
	  	  			return 0;
	  	  		  }
	  	  		  pch = strtok(NULL, " ");
	  	  }
	  	  if(pch==NULL){
	  		  //this means exiting without hitting ;
	  		  printf("ERROR: Statement must end with ; (semi colon)\n");
	  		  reset();
	  		  return 0;
	  	  }
	  	  //otherwise works fine
	  	  return 1;


	  return 1;
  }/*
  while(pch!=NULL){
	  //printf("pch is %s\n",pch);
	  variable_names[varnumber]=malloc(sizeof(char)*100);
	  if(variable_names[varnumber]!=NULL){ //check for malloc
		  //printf("var number is %d\n", varnumber);
		  strcpy(variable_names[varnumber], pch);
		  //printf("v[n] is %s\n", variable_names[varnumber]);
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
				  pch = strtok(NULL, " ");
				  continue;//return parse_line(pch+sizeof(char)*2);
			  }
		  }else if(strcmp(pch, ",")==0){
			  //start over
			  //printf(pch+sizeof(char)*2);
			  pch = strtok(NULL, " ");
			  continue;
			  //return parse_line(pch+sizeof(char)*2);
		  }
	  }
  }*/




  // Be sure to return the correct value in Part 4.
  return 1;

}
}


/**
 * helper function to determine type valid (1) or not (0)
 */
int validType(char *str) {
	if(strcmp(str, "int")==0 || strcmp(str, "void")==0){
		return 1;
	}
	return 0;
}

/**
 * helper function to determine variable valid (1) or not (0)
 */
int validVar(char *str) {
	if (strcmp(str , "int")==0 || strcmp(str, "void")==0){
		return 0;
	}
	if(*str>122 || *str<65 || (*str>90 && *str<97)) {
		printf("ERROR: Can only begin with letter\n");
		return 0;
	}
	return 1;
}

/**
 * helper function to determine assignment valid (1) or not (0)
 */
int validAssign(char *str){

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

