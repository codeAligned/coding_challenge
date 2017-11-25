#pragma once

const int MAX_ARRAY_ELEMENT_LENGTH = 100;
typedef int ElementType;
typedef struct _Sequence_
{
    ElementType data[MAX_ARRAY_ELEMENT_LENGTH];
    int elem_num;
}SequenceList;

int sequential_search(SequenceList *seq_list, ElementType key);
int sequential_search_sentry(SequenceList *seq_list, ElementType key);

int binary_search(SequenceList *seq_list, ElementType key);
int insertion_search(SequenceList *seq_list, ElementType key);
int fibonacci_search(SequenceList *seq_list, ElementType key);
