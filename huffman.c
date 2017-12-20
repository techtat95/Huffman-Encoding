#ifndef PA15_H
#define PA15_H
#define ASCII_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Tree{
  long counter;
  int number;
  struct Tree * left;
  struct Tree * right;
}Tree;

typedef struct pathNode{
  Tree * tree;
  struct pathNode * next;
}pathNode;

typedef * nodeH{
  pathNode * head;
}nodeH;

nodeH * buildList(long * ascii);
void nodeAdder(nodeH * path, pathNode * path)
void listFree(nodeH * path);

Tree * popNode(Tree * path);
void treeJoiner(nodeH * path, Tree * tree1, Tree * tree2);
void treeFree(Tree * tree);

#endif
