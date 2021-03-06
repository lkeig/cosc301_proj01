// Logan Keig & Cory Nettnin COSC301_Proj01
// 9-28-14

#ifndef __LIST_H__
#define __LIST_H__
#include <stdbool.h> 

/* your list data structure declarations */
struct node {
    char num[128];
    struct node *next;
};

/* your function declarations associated with the list */
void deleteComments (char* str);

char** tokenify(const char *s);
void print_tokens(char *tokens[]);
void free_tokens(char **tokens);
void refineToken(char **tokens);
bool tokenCheck (char* token);

void list_clear(struct node *list);
void list_append(const char *num, struct node **head);
void list_insert(struct node *new, struct node **head);
void list_unlink(struct node *dead, struct node **head);
struct node *find_largest(struct node *list);
void list_sort(struct node **head);
void list_print(const struct node *list);

void printStats(struct node *head, float timeUser, float timeOS);

#endif // __LIST_H__
