// Logan Keig & Cory Nettnin COSC301_Proj01
// 9-28-14
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <ctype.h>
#include "list.h"

//clears the comment lines from input file (any # through \n)
void deleteComments (char* str) {
	int index = 0;
	while(index < strlen(str)) {
		if(str[index] == '#') {
			while(str[index] != '\n') {
				str[index] = ' ';
				index++;
			}
		}
		else {
			index++;
		}
	}
}

/* Tokenify Functions */

//from COSC301_Lab02
char** tokenify(const char *s) {
	char *tempstr = strdup(s);
	char *token = strtok(tempstr," \t\n");
	int count = 0;
	while(token != NULL){ //counts up number of tokens
		count++;
		//printf("%s\n",token);
		token = strtok(NULL," \t\n");
	}
	//printf("Number of Tokens: %d\n",count);
	free(tempstr);

	tempstr = strdup(s); //restarts tempstr
	token = strtok(tempstr," \t\n");
	char** finishArray = malloc(sizeof(char*)*(count+1)); //finishArray on heap
	for(int i = 0; i < count; i++){
		if(token != NULL){
			finishArray[i] = strdup(token);
		}
		token = strtok(NULL," \t\n");
	}
	finishArray[count] = NULL;
	free(tempstr);

	return finishArray;
}

//from COSC301_Lab02
//used for testing purposes
void print_tokens(char *tokens[]) {
    int i = 0;
    while (tokens[i] != NULL) {
        printf("Token %d: %s\n", i+1, tokens[i]);
        i++;
    }
}

//from COSC301_Lab02
void free_tokens(char **tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        free(tokens[i]); // free each string
        i++;
    }
    free(tokens); // then free the array
}

void refineToken(char **tokens) {
	int index = 0;
	int totalTokens = 0;
	while (tokens[totalTokens] != NULL) { //count up number of tokens
        totalTokens++;
    }
	while((index < totalTokens) && tokens[index] != NULL) {
		if(!tokenCheck(tokens[index])) {
			int i = index;
			for (; i < (totalTokens - 1); i++) {
				tokens[i] = tokens[i+1];
			}
			tokens[i] = NULL;
		}
		else {
			index++;
		}
	}
}

//checks if a token is an int (checking for a '-', then using isdigit)
bool tokenCheck (char* token) {
	int index = 0;
	if(token[0] == '-'){
		index = 1;
	}
	while(index < strlen(token)) {
		if(isdigit(token[index])){
			index++;
		}
		else {
			return false;
		}
	}
	return true;
}

/* your list function definitions */

//from list_solution.c
void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

//from list_solution.c
void list_append(const char *num, struct node **head) {
    struct node *new = malloc(sizeof(struct node));
    strcpy(new->num,num);
    new->next = NULL;

    // handle special case of the list being empty
    if (*head == NULL) {
        *head = new;
        return;
    }

    struct node *tmp = *head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new;
}

//from list_solution.c
void list_insert(struct node *new, struct node **head) {
    new->next = *head;    
    *head = new;
}

//from list_solution.c
void list_unlink(struct node *dead, struct node **head) {
    // just unlink the dead node; don't free it
    if (*head == dead) {
        *head = (*head)->next;
        return;
    }
    struct node *tmp = *head;
    while (tmp->next != NULL) {
        if (tmp->next == dead) {
            tmp->next = dead->next;
            return;
        }
        tmp = tmp->next;
    }
}

//modified version (to work with ints) from list_solution.c
struct node *find_largest(struct node *list) {
    struct node *largest = list;
    list = list->next;
    while (list != NULL) {
        if ((atoi(largest->num) < atoi(list->num))) {
            largest = list;
        }
        list = list->next;
    }
    return largest;
}

//from list_solution.c
void list_sort(struct node **head) {
    // approach: construct a separate list by successively finding the 
    // largest items on the original list and 'pushing' them to the
    // front of the new list.  at the end, the new list has everything
    // sorted.
    struct node *sorted = NULL;

    struct node *old = *head;
    while (old != NULL) {
        struct node *largest = find_largest(old);  // find the largest
        list_unlink(largest, &old);                // remove it
        list_insert(largest, &sorted);             // push it on front of new list
    }
    *head = sorted;  // set head to newly sorted list
}

//from list_solution.c
//used for testing purposes
void list_print(const struct node *list) {
    int i = 0;
    while (list != NULL) {
        printf("List item %d: %s\n", i++, list->num);
        list = list->next;
    }
}

/****************************/

//prints finishing results
void printStats(struct node *head, float timeUser, float timeOS) {
	printf("*** List Contents Begin ***\n");
	while (head != NULL) {
		printf("%s\n", head->num);
		head = head->next;
	}
	printf("*** List Contents End ***\n");
	printf("User time: %f\n", timeUser);
	printf("System time: %f\n", timeOS);
}
