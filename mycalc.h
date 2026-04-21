#ifndef UNTITLED1_MYCALC_H
#define UNTITLED1_MYCALC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stdint.h"


// ARR
typedef struct Node {
    uint32_t timestamp_ms;
    float lat_rad;
    float lon_rad;
    float alt_m;
    struct Node *next;
} Node;

Node *createNodeArr(uint32_t timestamp_ms, float lat_rad, float lon_rad, float alt_m);

void appendArr(Node **head, uint32_t timestamp_ms, float lat_rad, float lon_rad, float alt_m);

void printingArr(Node *head);

void freeArr(Node *head);

int countPoints(Node *head);

uint32_t durationFlight(Node *head);

// TREE
typedef struct TreeNode {
    float timestamp_ms;
    float lat_rad;
    float lon_rad;
    float alt_m;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode *createNodeTree(uint32_t timestamp_ms, float lat_rad, float lon_rad, float alt_m);

TreeNode *appendTree(TreeNode *head, uint32_t timestamp_ms, float lat_rad, float lon_rad, float alt_m);

void NLR(TreeNode *root);

void LNR(TreeNode *root);

void RNL(TreeNode *root);

void freeTree(TreeNode *root);

float findMax(TreeNode *root);

float findMin(TreeNode *root);


// OTHER
int read_file(char *filename, Node **head);

void printStatistics(Node *head, TreeNode *root);

void writeStatistics(char *filename,Node *head, TreeNode *root);

#endif