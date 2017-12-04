#pragma once

const int MAX_ARRAY_ELEMENT_LENGTH = 100;
typedef int ElementType;
typedef struct _Sequence_
{
    ElementType data[MAX_ARRAY_ELEMENT_LENGTH];
    int elem_num;
}SequenceList;



typedef struct _SequenceWithSentinel_
{
    ElementType data[MAX_ARRAY_ELEMENT_LENGTH + 1];
    int elem_num;
}SequenceWithSentinel;


int helper_swap(ElementType *ele1, ElementType *ele2);

int init_sequence(SequenceList *pList);
int input_sequence(SequenceList *pList);
int print_sequence(SequenceList *pList);

int init_sequence(SequenceWithSentinel *seq_array);
int input_sequence(SequenceWithSentinel *seq_array);
int print_sequence(SequenceWithSentinel *seq_array);



int swap_sort(SequenceWithSentinel *seq_array);
int bubble_sort(SequenceWithSentinel *seq_array);
int bubble_sort_with_optimization(SequenceWithSentinel *seq_array);

int simple_selection_sort(SequenceWithSentinel *seq_array);
int heap_sort(SequenceWithSentinel *seq_array);
int heap_adjust(ElementType data[], int low, int high); 

int straight_insertion_sort(SequenceWithSentinel *seq_array);
int shell_sort(SequenceWithSentinel *seq_array);










int quick_sort(SequenceList *pSqList);
int quick_sort_subseq(ElementType data[], int low, int high);
int quick_sort_partition(ElementType data[], int low, int high);

int merge_sort_recursive(SequenceList *seq_list);
int merge_sort_recursive_subseq(ElementType data_from[], ElementType data_to[], int low, int high);
int merge_sort_iterative(SequenceList *seq_list);
int merge_sort_iterative_step(ElementType data_in[], ElementType data_out[], int step, int length);
int merge_sort_basic(ElementType data_in[], ElementType data_out[], int low, int mid, int high);

