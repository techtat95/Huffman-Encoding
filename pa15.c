#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/* count the occurrences in a file */

long *countLetters(FILE *fp)
{
   long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
   if (asciiCount == NULL) {
      return NULL;
   }
   int ch;
   for (ch = 0; ch < ASCII_SIZE; ch++) {
      asciiCount[ch] = 0;
   }
   fseek(fp, 0, SEEK_SET);
   while ((ch = fgetc(fp)) != EOF) {
      asciiCount[ch] += 1;
   }
   return asciiCount;
}

int main(int argc, char **argv)
{
   if (argc != 5) {
    printf("Not enough arguments");
    return EXIT_FAILURE;
   }
   FILE * inFile = fopen(argv[1], "r");
   if (inFile == NULL) {
      fprintf(stderr, "can't open the input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   /* read and count the occurrences of characters */
   long *asciiCount = countLetters(inFile);
   fclose(inFile);

   if (asciiCount == NULL) {
      fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
      return EXIT_FAILURE;
   }
 
   nodeH * head = listGen(asciiCount);
   free(asciiCount);

   FILE * pointer = fopen(argv[2], "w");
   printerFunc(head, pointer);
   fclose(pointer);

   TreeNode * htree = makeHuff(head);
   listfree(head);

   pointer = fopen(argv[3], "w");
   char * route = malloc(sizeof(char) * 9);
   huffDisplay(htree, pointer, route, 0);
   fclose(pointer);
   free(route);
 
   pointer = fopen(argv[4], "w");
   uint8_t * data = malloc(sizeof(uint8_t));
   int * val = malloc(sizeof(int));
   *data = 0;
   *val = 7;
   Inputter(htree, pointer, data, val);
   if(*val != 7)
   {
    while(*val >= 0){
	*val -= 1;
	}
   }
   fwrite(data, 1, 1, pointer);

  fclose(pointer);
  free(data);
  free(val);
  treeFree(htree);

  return EXIT_SUCCESS;
 }

  nodeH * listGen(long * ascii){
	nodeH * path = malloc(sizeof(nodeH));
	path -> head = NULL;
	ListNode * n1;
	for(int j = 0; j < ASCII_SIZE; ++j){
	if(ascii[j] != 0){
	n1 = malloc(sizeof(ListNode));
	n1 -> tree = malloc(sizeof(TreeNode));
	n1 -> tree -> label = j;
	n1 -> tree -> count = ascii[j];
	n1 -> tree -> left = n1 -> tree -> right = NULL;
	nodeAdd(path, n1);
     }
   }
	return path;
  }

  void listfree(nodeH * path){
 	ListNode * curr = path -> head;
	ListNode * next;

	while(curr != NULL){
	next = curr -> next;
	treeFree(curr -> tree);
	free(curr);
	curr = next;
	}
	free(path);
	return;
  }

 void nodeAdd(nodeH * path, ListNode * n1){
	if(path -> head == NULL){
	path -> head = n1;
	n1 -> next = NULL;
	return;
	}
  ListNode * curr = path -> head;
  ListNode * prev = NULL;

 	while(curr != NULL){
	if(curr -> tree -> count > (n1 -> tree -> count)){
	if(prev == NULL)
	path -> head = n1;
	else
	prev -> next = n1;
	n1 -> next = curr;
	
	return ;
	}

	if(curr -> tree -> count < (n1 -> tree -> count)){
	prev = curr;
	curr = curr -> next;
	}
	else if(((curr -> tree -> label) != -1) && (curr -> tree -> label < (n1 -> tree -> label))){
	prev = curr;
	curr = curr -> next;
	}
	else if(n1 -> tree -> label == -1){
	if(curr -> tree -> count == n1 -> tree -> count){
	prev = curr;
	curr = curr -> next;
	}
     }
	else break;
   }
  
	prev -> next = n1;
	n1 -> next = curr;

	return;
   }

	TreeNode * popNode(nodeH * path){
	if(path -> head == NULL)
	{
	return NULL;
	}

	ListNode * n1 = path -> head;
	path -> head = n1 -> next;

	TreeNode * tree = n1 -> tree;
	free(n1);
	return tree;
    }

	void treeFree(TreeNode * tree){
	if(tree == NULL) return;
	treeFree(tree -> left);
	treeFree(tree -> right);
	free(tree);
	}
	
	void treeBuild(nodeH * path, TreeNode * tree1, TreeNode * tree2){
	ListNode * n1 = malloc(sizeof(ListNode));
	n1 -> tree = malloc(sizeof(TreeNode));

	n1 -> tree -> label = -1;
	n1 -> tree -> count = tree1 -> count + tree2 -> count;
	n1 -> tree -> left = tree1;
	n1 -> tree -> right = tree2;

	nodeAdd(path, n1);

	return;
   }


  TreeNode * makeHuff(nodeH * path)
	{
	TreeNode * tree2;
	TreeNode * tree1;

	while(path -> head -> next != NULL)
	{
	tree1 = popNode(path);
	tree2 = popNode(path);
	treeBuild(path, tree1, tree2);
	}
	tree1 = popNode(path);
	return tree1;
	}
  void printerFunc(nodeH * path, FILE * pointer){
	ListNode * n1 = path -> head;

	while(n1 != NULL){
	fprintf(pointer, "%c:%ld\n", n1 -> tree -> label, n1 -> tree -> count);
	n1 = n1 -> next;
	}
	return;
    }

  void huffDisplay(TreeNode * tree, FILE * pointer, char * route, int counter){
	if(tree == NULL)
	return;

	route[counter] = '0';
	huffDisplay(tree -> left, pointer, route, counter + 1);
	route[counter] = '1';
	huffDisplay(tree -> right, pointer, route, counter + 1);

	if(tree -> left == NULL){
	route[counter] = '\0';
	fprintf(pointer, "%c:%s\n", tree -> label, route);
	return;
	}

	return;
  }

  void Inputter(TreeNode * tree, FILE * pointer, uint8_t * data, int * val){
	if(tree == NULL) 
	return;

	printer(tree, pointer, data, val);

	Inputter(tree -> left, pointer, data, val);
	Inputter(tree -> right, pointer, data, val);

	return;
	}
  void printer(TreeNode * tree, FILE * pointer, uint8_t * data, int * val){
	if(tree -> left != NULL)
	{
	*val = *val - 1;
	}
	else{
	*data = *data + (int)pow(2, *val);
	*val = *val -1;
	if(*val < 0){
	fwrite(data, 1, 1, pointer);
	*val = 7;
	*data = 0;
	}
	char let = tree -> label;
	for(int i = 0; i < 8; i++){
	if((let & 128) == 128)
	{
	*data = *data + (int)pow(2,*val);
	}
	let <<= 1;
	*val = *val - 1;

	if(*val < 0)
	{
	fwrite(data, 1, 1, pointer);
	*val = 7;
	*data = 0;
	}
    }
  }
	if(*val < 0){
	fwrite(data, 1, 1, pointer);
	*val = 7;
	*data = 0;
	}
	return;	
}


