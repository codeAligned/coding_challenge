#include "SearchFunction.h"



int sequential_search(SequenceList *seq_list, ElementType key)
{
    if (!seq_list || seq_list->elem_num <= 0)
    {
        return -1;
    }

    for (int i = 0; i < seq_list->elem_num; i++)
    {
        if (key == seq_list->data[i])
        {
            return i;
        }
    }
    return -1;
}


// assume that seq_list's element begin from index 1
int sequential_search_sentry(SequenceList *seq_list, ElementType key)
{
    if (!seq_list || seq_list->elem_num <= 0)
    {
        return -1;
    }

    seq_list->data[0] = key;

    for (int i = seq_list->elem_num; i >= 0; i--)
    {
        if (key == seq_list->data[i])
        {
            return i;
        }
    }
    return -1;
}




int binary_search(SequenceList *seq_list, ElementType key)
{
    if (!seq_list || seq_list->elem_num <= 0)
    {
        return -1;
    }

    int low_index = 0;
    int high_index = seq_list->elem_num - 1;
    int mid_index = 0;

    while (low_index <= high_index)
    {
        mid_index = (low_index + high_index) / 2;
        if (key == seq_list->data[mid_index])
        {
            return mid_index;
        }
        else if (key > seq_list->data[mid_index])
        {
            low_index = mid_index + 1;
        }
        else
        {
            high_index = mid_index - 1;
        }
        
    }

    return -1;
}


int insertion_search(SequenceList *seq_list, ElementType key)
{
    return -1;
}


int fibonacci_search(SequenceList *seq_list, ElementType key)
{
    return -1;
}







// if found, return 0 and *pp_result_node pointer to found node; else return 1 and  *pp_result_node point to the last searched node
// if empty tree, *pp_result_node is NULL
// PBinarySearchTreeNode *pp_result_node can be instead of by a ref to pointer
int search_binary_search_tree(PBinarySearchTreeNode root, ElementType key, PBinarySearchTreeNode parent, PBinarySearchTreeNode *pp_result_node)
{
    if (!pp_result_node)
    {
        return 2;
    }

    if (!root)
    {
        *pp_result_node = parent;
        return 1;
    }

    if (key == root->data)
    {
        *pp_result_node = root;
        return 0;
    }
    else if (key < root->data)
    {
        return search_binary_search_tree(root->lchild, key, root, pp_result_node);
    }
    else
    {
        return search_binary_search_tree(root->rchild, key, root, pp_result_node);
    }
    return 1;
}

// pp_root point to a POINTER to root node, the POINTER may be a left or right pointer part of a parent node
int insert_binary_search_tree(PBinarySearchTreeNode *pp_root, ElementType key)
{
    if (!pp_root)
    {
        return 2;
    }
    PBinarySearchTreeNode temp_node = 0, result_node = 0;
    if (search_binary_search_tree(*pp_root, key, 0, &result_node))
    {
        temp_node = new BinarySearchTreeNode;
        temp_node->data = key;
        temp_node->lchild = temp_node->rchild = 0;

        
        if (!result_node) // empty tree
        { 
            *pp_root = temp_node;
        }
        else if (key > result_node->data)
        {
            result_node->rchild = temp_node;
        }
        else
        {
            result_node->lchild = temp_node;
        }
        return 0;
    }
    return 1;
}

// pp_root point to a POINTER to root node, the POINTER may be a left or right pointer part of a parent node
int delete_binary_search_tree(PBinarySearchTreeNode *pp_root, ElementType key)
{
    if (!pp_root)
    {
        return 2;
    }

    if (!*pp_root)
    {
        return 1;
    }
    else if (key == (*pp_root)->data)
    {
        return delete_binary_search_tree_node(pp_root);
    }
    else if (key < (*pp_root)->data)
    {
        return delete_binary_search_tree(&(*pp_root)->lchild, key);
    }
    else
    {
        return delete_binary_search_tree(&(*pp_root)->rchild, key);
    }
    return 0;
}


// pp_root point to a POINTER to root node, the POINTER may be a left or right pointer part of a parent node
int delete_binary_search_tree_node(PBinarySearchTreeNode *pp_root)
{
    if (!pp_root)
    {
        return 2;
    }
    if ((*pp_root) == 0)
    {
        return 1;
    }

    PBinarySearchTreeNode deleted_node = 0, temp_node = 0;

    if ((*pp_root)->lchild == 0)
    {
        deleted_node = *pp_root;
        *pp_root = (*pp_root)->rchild;
        delete deleted_node;
    }
    else if ((*pp_root)->rchild == 0)
    {
        deleted_node = *pp_root;
        *pp_root = (*pp_root)->lchild;
        delete deleted_node;
    }
    else
    {
        temp_node = *pp_root;
        deleted_node = (*pp_root)->lchild;
        while (deleted_node->rchild)
        {
            temp_node = deleted_node;
            deleted_node = deleted_node->rchild;
        }
        (*pp_root)->data = deleted_node->data;
        if (temp_node == (*pp_root))
        {
            temp_node->lchild = deleted_node->lchild;
        }
        else
        {
            temp_node->rchild = deleted_node->lchild;
        }
        delete deleted_node;
    }
    return 0;
}











// AVL tree
int R_Rotate(PAVLBinarySearchTreeNode *tree)
{
    if (!tree || !(*tree)->lchild)
    {
        return 1;
    }
    // PAVLBinarySearchTreeNode root_node = *tree;
    PAVLBinarySearchTreeNode left_node = (*tree)->lchild;    
    (*tree)->lchild = left_node->rchild;
    left_node->rchild = *tree;
    *tree = left_node;
    return 0;
}

int L_Rotate(PAVLBinarySearchTreeNode *tree)
{
    if (!tree || !(*tree)->rchild)
    {
        return 1;
    }
    // PAVLBinarySearchTreeNode root_node = *tree;
    PAVLBinarySearchTreeNode right_node = (*tree)->rchild;
    (*tree)->rchild = right_node->lchild;
    right_node->lchild = *tree;
    *tree = right_node;
    return 0;
}

// After insertion make *tree to unablance, and BF is 2
// (*tree) 's balance factor is 2 or more, which means (*tree)->lchild can't be empty
int left_balance(PAVLBinarySearchTreeNode *tree)
{
    if (!tree)
    {
        return 1;
    }

    PAVLBinarySearchTreeNode left_node = (*tree)->lchild;
    PAVLBinarySearchTreeNode left_right_node = 0;
    switch (left_node->balance_factor)
    {
    case 1:
        // same sign of 2 node's factor
        (*tree)->balance_factor = left_node->balance_factor = 0;
        R_Rotate(tree);
        break;
    case -1:
        // means not same sign, and need 2 rotate.
        // left_node's balance factor is -1, which means left_node->rchild can't be empty
        left_right_node = left_node->rchild;
        switch (left_right_node->balance_factor)
        {
        case 1:
            (*tree)->balance_factor = -1;
            left_node->balance_factor = 0;
            break;
        case 0:
            (*tree)->balance_factor = left_node->balance_factor = 0;
            break;
        case -1:
            (*tree)->balance_factor = 0;
            left_node->balance_factor = 1;
            break;
        default:
            break;
        }
        left_right_node->balance_factor = 0;
        L_Rotate(&(*tree)->lchild); // need use the pointer var in tree, not the pointer var in this function
        R_Rotate(tree);
        break;
    default:
        break;
    }
    return 0;
}

// After insertion make *tree to unablance, and BF is -2
int right_balance(PAVLBinarySearchTreeNode *tree)
{
    if (!tree)
    {
        return 1;
    }

    PAVLBinarySearchTreeNode right_node = (*tree)->rchild;
    PAVLBinarySearchTreeNode right_left_node = 0;
    switch (right_node->balance_factor)
    {
    case -1:
        (*tree)->balance_factor = right_node->balance_factor = 0;
        L_Rotate(tree);
        break;
    // can't be 0, beacuse after insertion make bf to 0, means no height increace for tree
    case 1:
        // means not same sign, and need 2 rotate.
        // right_node's balance factor is 1, which means right_node->lchild can't be empty
        right_left_node = right_node->lchild;
        switch (right_left_node->balance_factor)
        {
        case 1:
            (*tree)->balance_factor = 0;
            right_node->balance_factor = -1;
            break;
        case 0:
            (*tree)->balance_factor = right_node->balance_factor = 0;
            break;
        case -1:
            (*tree)->balance_factor = 1;
            right_node->balance_factor = 0;
            break;
        default:
            break;
        }
        right_left_node->balance_factor = 0;
        R_Rotate(&(*tree)->rchild);
        L_Rotate(tree);
        break;
    default:
        break;
    }
    return 0;
}

// recursive call, so the stop condition is *tree = NULL(insert) or find elem(not insert)
int insert_avl_tree(PAVLBinarySearchTreeNode *tree, ElementType elem, int *is_taller)
{
    if (!tree || !is_taller)
    {
        return 2;
    }
    if (!(*tree))
    {
        *tree = new AVLBinarySearchTreeNode;
        (*tree)->balance_factor = 0;
        (*tree)->data = elem;
        (*tree)->lchild = (*tree)->rchild = 0;
        *is_taller = 1;
    }
    else
    {
        if ((*tree)->data == elem)
        {
            *is_taller = 0;
            return 1;
        }
        else if (elem < (*tree)->data)
        {
            if (insert_avl_tree(&(*tree)->lchild, elem, is_taller))
            {
                return 1;
            }
            if (*is_taller)
            {
                switch ((*tree)->balance_factor)
                {
                case 1:
                    *is_taller = 1;
                    left_balance(tree);
                    break;
                case 0:
                    *is_taller = 1;
                    (*tree)->balance_factor = 1;
                    break;
                case -1:
                    *is_taller = 0;
                    (*tree)->balance_factor = 0;
                    break;
                default:
                    break;
                }

            }
            
        }
        else 
        {
            if (insert_avl_tree(&(*tree)->rchild, elem, is_taller))
            {
                return 1;
            }
            if (*is_taller)
            {
                switch ((*tree)->balance_factor)
                {
                case 1:
                    *is_taller = 0;
                    (*tree)->balance_factor = 0;
                    break;
                case 0:
                    *is_taller = 1;
                    (*tree)->balance_factor = -1;
                    break;
                case -1:
                    *is_taller = 1;
                    right_balance(tree);
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 0;
}


