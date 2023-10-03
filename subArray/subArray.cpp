#include <iostream>
#define FIRST_ELEMENT(array) array[0]

/* 
    Question 1 (30 pts) Design an algorithm that finds the maximum sum of a subarray.
    The input is the array A. The output is the maximum sum of a subarray. For example, if
    A = [1, −2, 3, 10, −4, 7, 2, −5], then the maximum sum of a subarray is 18 = 3+10−4+7+2.
    Briefly justify the correctness and the running time in terms of the number of elements n
    in the array. 
*/

/* 
 * Here we are basically keeping track of a "window" of where the greatest sum is
 * This window will start simply at the first element. This is the greatest sum and
 * the sum of the window. We can then have the window incrementally include the next
 * element. If we find that element by itself is better than the possible window we
 * will restart our window at the new element and try to find a new max_sum.
 * However, our previous max_sum will be recorded in case that ended up being the best option.
 */

int maximumSubArray(int* array, int arraySize)
{
    int max_sum     = FIRST_ELEMENT(array);      // Initialize the maximum sum as the first element
    int window_sum  = FIRST_ELEMENT(array);      // Initialize the current sum as the first element

    for (int i = 1; i < arraySize; ++i) {
        window_sum = std::max(array[i], window_sum + array[i]); // Include element in window or reset window
        max_sum =    std::max(max_sum, window_sum);             // Always record what has been the greatest sum
    }

    return max_sum;
}

int main(int argc, char* argv[])
{
    int array[] = {1, -2, 3, 10, -4, 7, 2, -5};
    std::cout << maximumSubArray(array, 8);
    exit(EXIT_SUCCESS);
}

/* This algorithm will run in O(n) time since we only ever visit every element once */