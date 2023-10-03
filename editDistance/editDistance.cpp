/* 
 * Conner Sommerfield
 * RedId: 824769654
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#define TWO_DIGIT_NUMBER 10
#define EMPTY_STRING 0
#define INIT_LOOP_COUNTER 0
#define ONE_EDIT 1
#define EMPTY_CASE_PADDING 1

/* 
    Question 3 (20 pts) Let 2 std::strings A and B be
    – “The quick brown fox jumps over the lazy dog.”
    – “The sun rises in the east and sets in the west.”
    Let ED[i, j] be the edit distance of the first i characters of A and the first j characters
    of B as defined in class. Provide the dynamic programming table ED (for i = 0, 1, 2, . . . ,
    and j = 0, 1, 2, . . .).
    You can do this by hand or implement the algorithm and copy the table from your program
*/
typedef std::vector<std::vector<int>> matrix_t;

// Generic minimum function of 3 elements
int min(int a, int b, int c) 
{
    return std::min(std::min(a, b), c);
}

// Operator overload to print out matrix
std::ostream& operator<<(std::ostream& stream, matrix_t matrix)
{
    for (const std::vector<int>& row : matrix)
    {
        for (const int& element : row)
        {
            if (element<TWO_DIGIT_NUMBER) 
                stream << " "; // Add padding to one-digit numbers
            stream << element << " ";
        }
        stream << std::endl;
    }
    return stream;
}

/* 
 * Three cases
 * Transform A-1 to B, then add last letter of A
 * Transform A to B-1, then remove last letter of A 
 * Transform A to B, replace last letter if necessary
 */

matrix_t editTable(const std::string& stringOne, const std::string& stringTwo) {
    const int stringOneSize = stringOne.length();
    const int stringTwoSize = stringTwo.length();
    
    // Allocate space for table with padding for empty cases
    matrix_t ED(
        stringOneSize + EMPTY_CASE_PADDING,                  // Number of rows to allocate
        std::vector<int>(stringTwoSize + EMPTY_CASE_PADDING) // Actual row
    ); 

    for (int i = INIT_LOOP_COUNTER; i <= stringOneSize; ++i) {
        for (int j = INIT_LOOP_COUNTER; j <= stringTwoSize; ++j) {
            if (i == EMPTY_STRING)
                ED[i][j] = j;                   // Base case 1: i is empty string, to make j equal to i when need j edits
            else if (j == EMPTY_STRING)         // Base case 2: j is empty string, to make i equal to j when need i edits
                ED[i][j] = i;
            else if (stringOne[i - 1] == stringTwo[j - 1]) 
                ED[i][j] = ED[i - 1][j - 1]; // Replacing last letter not necessary so simply set equal without incrementing
            else
                ED[i][j] = ONE_EDIT + min(ED[i - 1][j], ED[i][j - 1], ED[i - 1][j - 1]); // Find minimum of above three cases and add 1 for the necessary edit
        }
    }
    return ED;
}

int main(int argc, char* argv[]) {
    const std::string A = "The quick brown fox jumps over the lazy dog.";
    const std::string B = "The sun rises in the east and sets in the west.";
    const matrix_t dp_table = editTable(A,B);
    std::cout << dp_table << std::endl << "Edit Distance Is: " <<  
    dp_table[A.size()-1][B.size()-1] << std::endl; // Answer is last element of our table
    exit(EXIT_SUCCESS);
}

