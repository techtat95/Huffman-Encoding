#ifndef PA15_H
#define PA15_H		 

#define ASCII_SIZE 256
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "huffman.h"

typedef struct TreeNode {
   int label;
   long count;
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
   TreeNode * tree;
   struct ListNode * next;
} ListNode;

typedef struct nodeH{
   ListNode * head;
}nodeH;

nodeH * listGen(long * ascii);
void nodeAdd(nodeH * path, ListNode * n1);
void listFree(nodeH * path);

TreeNode * popNode(nodeH * path);
void treeFree(TreeNode * tree);
void treeBuild(nodeH * path, TreeNode *tree1, TreeNode * tree2);

void listfree(nodeH * path);
void nodeAdd(nodeH * path, ListNode * n1);
void treeFree(TreeNode * tree);
void treeBuild(nodeH * path, TreeNode * tree1, TreeNode * tree2);
void printerFunc(nodeH * path, FILE * pointer);
void huffDisplay(TreeNode * tree, FILE * pointer, char * route, int counter);
void Inputter(TreeNode * tree, FILE * pointer, uint8_t * data, int * val);
void printer(TreeNode * tree, FILE * pointer, uint8_t * data, int * val);
nodeH * listGen(long * ascii);
TreeNode * makeHuff(nodeH * path);
#endif
