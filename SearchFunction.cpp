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


