#include "SortFunction.h"
#include <iostream>



int init_sequence(SequenceList *pList)
{
    if (!pList)
    {
        return 1;
    }
    for (int i = 0; i < MAX_ARRAY_ELEMENT_LENGTH; i++)
    {
        pList->data[i] = 0;
    }
    pList->elem_num = 0;
    return 0;
}


int input_sequence(SequenceList *pList)
{
    if (!pList)
    {
        return 1;
    }
    int ch = 0;

    while (std::cin >> ch && pList->elem_num < MAX_ARRAY_ELEMENT_LENGTH)
    {
        pList->data[pList->elem_num++] = ch;
    }
    std::cin.clear();

    return 0;
}

int print_sequence(SequenceList *pList)
{
    if (!pList)
    {
        return 1;
    }

    std::cout << "The amount of element in Sequence List is : " << pList->elem_num << std::endl;
    for (int i = 0; i < pList->elem_num; i++)
    {
        std::cout << "Element " << i << " is " << pList->data[i] << std::endl;
    }
    return 0;
}


int init_sequence(SequenceWithSentinel *seq_array)
{
    if (!seq_array)
    {
        return 1;
    }
    for (int i = 1; i <= MAX_ARRAY_ELEMENT_LENGTH; i++)
    {
        seq_array->data[i] = 0;
    }
    seq_array->elem_num = 0;
    return 0;
}
int input_sequence(SequenceWithSentinel *seq_array)
{
    if (!seq_array)
    {
        return 1;
    }
    seq_array->elem_num = 10;
    seq_array->data[1] = 25;
    seq_array->data[2] = 13;
    seq_array->data[3] = 7;
    seq_array->data[4] = 42;
    seq_array->data[5] = 152;
    seq_array->data[6] = 16;
    seq_array->data[7] = 98;
    seq_array->data[8] = 71;
    seq_array->data[9] = 57;
    seq_array->data[10] = 33;
    return 0;
}
int print_sequence(SequenceWithSentinel *seq_array)
{
    if (!seq_array)
    {
        return 1;
    }

    std::cout << "The amount of element in Sequence List is : " << seq_array->elem_num << std::endl;
    for (int i = 1; i <= seq_array->elem_num; i++)
    {
        std::cout << "Element " << i << " is " << seq_array->data[i] << std::endl;
    }
    return 0;
}


int helper_swap(ElementType *ele1, ElementType *ele2)
{
    if (!ele1 || !ele2)
    {
        return 1;
    }

    ElementType temp = *ele2;
    *ele2 = *ele1;
    *ele1 = temp;
    return 0;
}





int swap_sort(SequenceWithSentinel *seq_array)
{
    if (!seq_array || seq_array->elem_num <= 0)
    {
        return 1;
    }

    int handling_index = 0;   
    int comp_index = 0;

    // element begin with index 1, 0 used for temp value
    for (handling_index = 1; handling_index < seq_array->elem_num; handling_index++)
    {
        for (comp_index = handling_index + 1; comp_index <= seq_array->elem_num; comp_index ++)
        {
            // < means stable sort, <= means un-stable sort
            if (seq_array->data[comp_index] < seq_array->data[handling_index])
            {
                helper_swap(&seq_array->data[comp_index], &seq_array->data[handling_index]);
            }
        }
    }
    return 0;
}



int bubble_sort(SequenceWithSentinel *seq_array)
{
    if (!seq_array || seq_array->elem_num <= 0)
    {
        return 1;
    }

    int low_boundary_index = 0;
    int comp_index = 0;

    // element begin with index 1, 0 used for temp value
    for (low_boundary_index = 1; low_boundary_index < seq_array->elem_num; low_boundary_index++)
    {
        for (comp_index = seq_array->elem_num - 1; comp_index >= low_boundary_index; comp_index--)
        {
            // > means stable sort, >= means un-stable sort
            if (seq_array->data[comp_index] > seq_array->data[comp_index + 1])
            {
                helper_swap(&seq_array->data[comp_index], &seq_array->data[comp_index + 1]);
            }
        }
    }
    return 0;
}

int bubble_sort_with_optimization(SequenceWithSentinel *seq_array)
{
    if (!seq_array || seq_array->elem_num <= 0)
    {
        return 1;
    }
    int low_boundary_index = 0;
    int comp_index = 0;
    bool is_remain_elem_not_sorted = true;

    // element begin with index 1, 0 used for temp value
    for (low_boundary_index = 1; low_boundary_index < seq_array->elem_num && is_remain_elem_not_sorted; low_boundary_index++)
    {
        is_remain_elem_not_sorted = false;  // if the var is still false after all compare of this circle, it means all element in sort, we needn't to go through.
        for (comp_index = seq_array->elem_num - 1; comp_index >= low_boundary_index; comp_index--)
        {
            // > means stable sort, >= means un-stable sort
            if (seq_array->data[comp_index] > seq_array->data[comp_index + 1])
            {
                helper_swap(&seq_array->data[comp_index], &seq_array->data[comp_index + 1]);
                is_remain_elem_not_sorted = true;
            }
        }
    }
    return 0;
}

int simple_selection_sort(SequenceWithSentinel *seq_array)
{
    if (!seq_array || seq_array->elem_num <= 0)
    {
        return 1;
    }

    int min_value_index = 0;
    for (int i = 1; i < seq_array->elem_num; i++)
    {
        min_value_index = i; 
        for (int j = i + 1; j <= seq_array->elem_num; j++)
        {
            if (seq_array->data[j] < seq_array->data[min_value_index])
            {
                min_value_index = j;
            }
        }
        if (min_value_index != i)
        {
            helper_swap(&seq_array->data[min_value_index], &seq_array->data[i]);
        }        
    }
    return 0;
}


int straight_insertion_sort(SequenceWithSentinel *seq_array)
{
    if (!seq_array || seq_array->elem_num <= 0)
    {
        return 1;
    }

    int low_boundary_index = 0;
    int sorted_part_index = 0;

    for (low_boundary_index = 2; low_boundary_index <= seq_array->elem_num; low_boundary_index++)
    {
        if (seq_array->data[low_boundary_index] < seq_array->data[low_boundary_index - 1])
        {
            seq_array->data[0] = seq_array->data[low_boundary_index];
            // Not needed to judge if sorted_part_index > 0
            // when all sorted part is higher than value in index 0, then sorted_part_index will go to 0, these code can also work. 
            // Note that it must be "<", can't use "<="(sorted_part_index go to -1)
            for (sorted_part_index = low_boundary_index - 1; seq_array->data[0] < seq_array->data[sorted_part_index]; sorted_part_index--)
            {
                seq_array->data[sorted_part_index + 1] = seq_array->data[sorted_part_index];
            }
            seq_array->data[sorted_part_index + 1] = seq_array->data[0];
        }
    }
    return 0;
}


int shell_sort(SequenceWithSentinel *seq_array)
{
    if (!seq_array || seq_array->elem_num <= 0)
    {
        return 1;
    }


    int low_boundary_index = 0;
    int sorted_part_index = 0;
    int increment = 0;
    do
    {
        increment = increment / 3 + 1;
        for (low_boundary_index = 1 + increment; low_boundary_index <= seq_array->elem_num; low_boundary_index ++)
        {
            if (seq_array->data[low_boundary_index] < seq_array->data[low_boundary_index - increment])
            {
                seq_array->data[0] = seq_array->data[low_boundary_index];
                for (sorted_part_index = low_boundary_index - increment; 
                     (sorted_part_index > 0) && (seq_array->data[0] < seq_array->data[sorted_part_index]);
                     sorted_part_index -= increment)
                {
                    seq_array->data[sorted_part_index + increment] = seq_array->data[sorted_part_index];
                }
                seq_array->data[sorted_part_index + increment] = seq_array->data[0];
            }
        }
    } while (increment > 1);
    return 0;
}






int quick_sort(SequenceList *seq_array)
{
    if (!seq_array)
    {
        return 1;
    }

    if (seq_array->elem_num <= 0)
    {
        return 2;
    }

    quick_sort_subseq(seq_array->data, 0, seq_array->elem_num - 1);

    return 0;
}


int quick_sort_subseq(ElementType data[], int low, int high)
{
    if (!data || low >= high)
    {
        return 1;
    }

    int pivot = quick_sort_partition(data, low, high);
    quick_sort_subseq(data, low, pivot - 1);
    quick_sort_subseq(data, pivot + 1, high);
    return 0;
}


int quick_sort_partition(ElementType data[], int low, int high)
{
    if (!data || low >= high)
    {
        return 1;
    }
    int low_index = low;
    int high_index = high;
    int pivot_key = data[low_index];
    while (low_index < high_index)
    {
        while ((low_index < high_index) && (data[high_index] >= pivot_key))
        {
            high_index--;
        }
        // Swap(data + low_index, data + high_index);
        data[low_index] = data[high_index];

        while ((low_index < high_index) && (data[low_index] <= pivot_key))
        {
            low_index++;
        }
        // Swap(data + low_index, data + high_index);
        data[high_index] = data[low_index];
    }
    data[low_index] = pivot_key;
    return low_index;
}






int merge_sort_recursive(SequenceList *seq_list)
{
    if (!seq_list)
    {
        return 1;
    }
    // ElementType data_rec[MAX_ARRAY_ELEMENT_LENGTH] = { 0 };
    merge_sort_recursive_subseq(seq_list->data, seq_list->data, 0, seq_list->elem_num - 1);
    // memcpy(seq_list->data, data_rec, sizeof(ElementType) * seq_list->elem_num);
    return 0;
}

int merge_sort_recursive_subseq(ElementType data_from[], ElementType data_to[], int low, int high)
{
    if (!data_from || !data_to || low > high)
    {
        return 1;
    }

    ElementType data_rec[MAX_ARRAY_ELEMENT_LENGTH] = { 0 };

    if (low == high)
    {
        data_to[low] = data_from[low];
    }
    else
    {
        int mid = (low + high) / 2;
        merge_sort_recursive_subseq(data_from, data_rec, low, mid);
        merge_sort_recursive_subseq(data_from, data_rec, mid + 1, high);
        merge_sort_basic(data_rec, data_to, low, mid, high);
    }
    return 0;
}


int merge_sort_iterative(SequenceList *seq_list)
{
    if (!seq_list)
    {
        return 1;
    }
    ElementType data_temp[MAX_ARRAY_ELEMENT_LENGTH] = { 0 };
    int step = 1;
    while (step < seq_list->elem_num)
    {
        merge_sort_iterative_step(seq_list->data, data_temp, step, seq_list->elem_num);
        step *= 2;
        merge_sort_iterative_step(data_temp, seq_list->data, step, seq_list->elem_num);
        step *= 2;
    }

    return 0;
}

int merge_sort_iterative_step(ElementType data_in[], ElementType data_out[], int step, int length)
{
    if (!data_in || !data_out || step <= 0 || length <= 0)
    {
        return 1;
    }

    int merge_index = 0;

    while (merge_index <= length - 2 * step)
    {
        merge_sort_basic(data_in, data_out, merge_index, merge_index + step - 1, merge_index + 2 * step - 1);
        merge_index += 2 * step;
    }

    if (length - merge_index > step)
    {
        merge_sort_basic(data_in, data_out, merge_index, merge_index + step - 1, length - 1);
    }
    else
    {
        for (;merge_index < length; merge_index++)
        {
            data_out[merge_index] = data_in[merge_index];
        }
    }
    return 0;
}


int merge_sort_basic(ElementType data_in[], ElementType data_out[], int low, int mid, int high)
{
    if (!data_in || !data_out)
    {
        return 1;
    }
    if (low > mid || mid > high)
    {
        return 2;
    }
    
    int ori_low_index = low;
    int ori_high_index = mid + 1;
    int dest_index = low;

    while ((ori_low_index <= mid) && (ori_high_index <= high))
    {
        if (data_in[ori_low_index] <= data_in[ori_high_index])
        {
            data_out[dest_index++] = data_in[ori_low_index++];
        }
        else
        {
            data_out[dest_index++] = data_in[ori_high_index++];
        }        
    }

    /*
    for (;(ori_low_index <= mid) && (ori_high_index <= high); dest_index ++)
    {
        if (data_in[ori_low_index] <= data_in[ori_high_index])
        {
            data_out[dest_index++] = data_in[ori_low_index++];
        }
        else
        {
            data_out[dest_index++] = data_in[ori_high_index++];
        }
    }
    */

    if (ori_low_index <= mid)
    {
        for (;ori_low_index <= mid;)
        {
            data_out[dest_index++] = data_in[ori_low_index++];
        }
    }

    if (ori_high_index <= high)
    {
        for (; ori_high_index <= high;)
        {
            data_out[dest_index++] = data_in[ori_high_index++];
        }
    }   
    
    return 0;
}










