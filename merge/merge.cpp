
/* 
    Question 2 (30 pts)
    You are given t sorted lists A1, A2, . . . , At each of size n. 
    First, show that the following algorithm runs in O(t^2n) time. Note that the Merge procedure above is the one we used
    1 Initialize C to be an empty list.
    2 for i = 1, 2, . . . , t do
        3 C = Merge(C, Ai).
        4 end
    5 Return C.
    for merge sort in class. Design a better algorithm to merge them into one single sorted list
    that runs in Θ(nt log t) time. Make sure you justify the running time.
 */

/* 
 * If I have 5 sorted lists
 * 
 * A
 * B
 * C
 * D
 * E
 * 
 * Then if I merge these using the merge procedure above I first have A and B like this 
 * 
 * A [1,3,5]
 *    *
 * B [2,4,6]
 *    * 
 * New []
 * 
 * The asterisks represent pointers
 * I will place elements into new list until I reach the end of each list, 
 * incrementing the pointer for the corresponding list where a value is copied from
 * Because I have to traverse every element of each list, this will be 2n operations (n for A, n for B)
 * I have t lists. When I perform this operation, I now have t-1 lists. I still have to merge t-1 lists,
 * starting with the new list and C
 * 
 * This will be 
 * 
 * New [1,2,3,4,5,6]
 * C   [7,8,9]
 * 
 * Our new list will have k*n elements, with k being the iteration we're on
 * We will merge this with an original list of n items
 * So we will have kn + n = (k+1)(n) operations.
 * 
 * So we know our merge procedure takes (k+1)(n) operations.
 * Every time we perform this Merge procedure we reduce our problem size by 1
 * So first we have 2n operations, then 3n operations, then 4n operations, then 5n operations ... tn operations
 * 
 * Which means we have n(2 + 3 + 4 + 5 ... t)
 * This infinite series is equal to (t(t+1)/2) - 1 operations
 * So we have n ((t(t+1)/2) - 1) operations which is proportional to t^2n operations.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#define FIRST_ELEMENT(vector) vector[0]
#define MIDPOINT(vector) vector.size()/2
#define ONE_LIST 1

void printVector(const std::vector<int>& vect)
{
    for (const auto& element : vect)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// This procedure mimics our Merge operation
std::vector<int> mergeLists(const std::vector<int>& firstList, const std::vector<int>& secondList)
{
    std::vector<int> newList;
    size_t leftIndex = 0;
    size_t rightIndex = 0;

    while (leftIndex < firstList.size() && rightIndex < secondList.size())
    {
        if (firstList[leftIndex] < secondList[rightIndex]) 
            newList.push_back(firstList[leftIndex++]);
        else 
            newList.push_back(secondList[rightIndex++]);
    }

    while (leftIndex < firstList.size()) 
        newList.push_back(firstList[leftIndex++]);

    while (rightIndex < secondList.size()) 
        newList.push_back(secondList[rightIndex++]);
    
    return newList;
}

/* 
 * Instead of merging each list in a loop where we only reduce our problem size by t-1, we could reduce our problem size by half 
 * We could do this recursively by merging t/2 lists with the other t/2 list
 * Our base case will be when we are merging one list with one list, then we will simply call our merge procedure
 * Otherwise we will recurse our new merge function
 * 
 * This case will achieve a better run time because we will reduce our problem size in half every time.
 * So before our merge procedure was shown to need k(n+1) operations
 * Before we did this procedure t times because every time we did it, our problem size decreased by 1
 * However, now we have non-recursive work and our recursive work
 * Our non-recursive work will now be the addition of the size of the two lists which will be cut in half for every recursive level
 * So if we start with 4 lists of size 6 we will have 24 operations then 12 operations, then 6 operations ...
 * 
 * If we have t lists of size n we have nt operations then nt/2 operations then nt/4 operations...
 * This will therefore have ntlogt complexity
 */

std::vector<int> mergeSortedLists(const std::vector<std::vector<int>>& sortedLists) {
    // Split our list in two halves of lists
    const std::vector<std::vector<int>> sortedListsFirstHalf (sortedLists.begin(), sortedLists.begin() + MIDPOINT(sortedLists));
    const std::vector<std::vector<int>> sortedListsSecondHalf(sortedLists.begin() + MIDPOINT(sortedLists), sortedLists.end());

    // Base Cases
    if (sortedLists.size() == ONE_LIST) // If there's only one list, we simply return that list
        return sortedLists[0];

    // If there are only two lists, we can merge each list using our above procedure
    if (sortedListsFirstHalf.size() == ONE_LIST && sortedListsSecondHalf.size() == ONE_LIST)
        return mergeLists(sortedListsFirstHalf[0], sortedListsSecondHalf[0]);
    
    // Recursive Case - Merge the two halves
    return mergeSortedLists(std::vector<std::vector<int>>{mergeSortedLists(sortedListsFirstHalf), mergeSortedLists(sortedListsSecondHalf)});
}

int main() {
    std::vector<std::vector<int>> sortedLists 
    {
        {1, 3, 5, 7},
        {2, 4, 6, 8},
        {9, 11,30,52},
        {10,13,16,18},
    };

    printVector(mergeLists(sortedLists[0], sortedLists[1]));
    printVector(mergeSortedLists(sortedLists));
    return 0;
}


