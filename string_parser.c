/*
 * string_parser.c
 *
 *  Created on: Nov 25, 2020
 *      Author: gguan, Monil
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"
#include <ctype.h>
#define _GUN_SOURCE

int count_token (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	Check for NULL string
	*	#2.	iterate through string counting tokens
	*		Cases to watchout for
	*			a.	string start with delimeter
	*			b. 	string end with delimeter
	*			c.	account NULL for the last token
	*	#3. return the number of token (note not number of delimeter)
	*/

	/* We are basically separating a string by a delimiter. and we are counting each piece of text. 
	We don't count strings with delimiters and if we have a null string we return 0 for the count
	*/

	if (buf == NULL){
		return 0;
	}

	char *token; char * ptr;

	int count = 0;

	char *copy_buf = (char*)malloc(sizeof(char) * strlen(buf) + 1);
	strcpy(copy_buf, buf);

	copy_buf[strlen(buf)] = '\0';
	token = strtok_r(copy_buf, delim, &ptr);

	while (token != NULL){
		count ++;
		token = strtok_r(NULL, delim, &ptr);
	}

	return count;
}

void trim(char *str) {
    char *start = str;
    char *end;
    
    // Trim leading whitespace
    while(isspace((unsigned char)*start)) start++;
    
    if(*start == 0) { // All spaces
        *str = 0;
        return;
    }
    
    // Trim trailing whitespace
    end = start + strlen(start) - 1;
    while(end > start && isspace((unsigned char)*end)) end--;
    
    // Write null terminator
    *(end + 1) = 0;
    
    // Move the trimmed string to the beginning if needed
    if(start != str)
        memmove(str, start, strlen(start) + 1);
}

command_line str_filler (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	create command_line variable to be filled and returned
	*	#2.	count the number of tokens with count_token function, set num_token. 
    *           one can use strtok_r to remove the \n at the end of the line.
	*	#3. malloc memory for token array inside command_line variable
	*			based on the number of tokens.
	*	#4.	use function strtok_r to find out the tokens 
    *   #5. malloc each index of the array with the length of tokens,
	*			fill command_list array
	 with tokens, and fill last spot with NULL.
	*	#6. return the variable.
	*/
	command_line cl; //created the command line variable
	cl.num_token = count_token(buf, delim); //counted the number of tokens and stored it in cl.num_token
	char ** arr = (char**)malloc((cl.num_token + 1)* sizeof(char *)); 
	//allocated memory for the token array
	
	char *token; char * ptr; 

	char *copy_buf = (char*)malloc(sizeof(char) * strlen(buf) + 1);
	strcpy(copy_buf, buf);

	copy_buf[strlen(buf)] = '\0';
	token = strtok_r(copy_buf, delim, &ptr);

	for(int i = 0; i < cl.num_token; i++) {
		if(token == NULL){
		break;
		}
		arr[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(arr[i], token);
		trim(arr[i]); // Add this line to trim whitespace
		token = strtok_r(NULL, delim, &ptr);
	}
	arr[cl.num_token] = NULL; //set the last index to NULL
	cl.command_list = arr; 
	
	free(copy_buf);
	return cl;
}


void free_command_line(command_line* command)
{
	//TODO：
	/*
	*	#1.	free the array base num_token
	*/
	for(int i = 0; i < command -> num_token; i ++){
		free(command -> command_list[i]);
	}
	free(command->command_list);
}
