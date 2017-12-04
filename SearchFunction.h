#pragma once

const int MAX_ARRAY_ELEMENT_LENGTH = 100;
typedef int ElementType;
typedef struct _Sequence_
{
    ElementType data[MAX_ARRAY_ELEMENT_LENGTH];
    int elem_num;
}SequenceList;




typedef struct _BinarySearchTreeNode_
{
    ElementType data;
    _BinarySearchTreeNode_ *lchild;
    _BinarySearchTreeNode_ *rchild;
}BinarySearchTreeNode, *PBinarySearchTreeNode;

typedef struct _AVLBinarySearchTreeNode_
{
    ElementType data;
    int balance_factor;
    _AVLBinarySearchTreeNode_ *lchild;
    _AVLBinarySearchTreeNode_ *rchild;
}AVLBinarySearchTreeNode, *PAVLBinarySearchTreeNode;

int sequential_search(SequenceList *seq_list, ElementType key);
int sequential_search_sentry(SequenceList *seq_list, ElementType key);

int binary_search(SequenceList *seq_list, ElementType key);
int insertion_search(SequenceList *seq_list, ElementType key);
int fibonacci_search(SequenceList *seq_list, ElementType key);



int search_binary_search_tree(PBinarySearchTreeNode root, ElementType key, PBinarySearchTreeNode parent, PBinarySearchTreeNode *pp_result_node);
int insert_binary_search_tree(PBinarySearchTreeNode *pp_root, ElementType key);
int delete_binary_search_tree(PBinarySearchTreeNode *pp_root, ElementType key);
int delete_binary_search_tree_node(PBinarySearchTreeNode *pp_root);




