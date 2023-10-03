#include <iostream>
#include <vector>

/*
    A robot is traveling along a one-dimensional road starting from
    checkpoint D[0] = 1 to check point D[n]. From the input, D[i] represents the distances from
    starting point 0 to checkpoint i. Furthermore D[0] < D[1] < . . . < D[n]. The robot cannot
    move backward. Ideally, the robot travels 200 miles per day. If it travels x miles a day, the
    penalty for that day is (200 − x)2. Design an algorithm that finds the minimum penalty for
    the robot to travel from checkpoint D[0] to checkpoint D[n]. Briefly justify the correctness
    and the running time in terms of the number of checkpoints n.
 */

#define MAX_DAILY_TRAVEL_DISTANCE 200
#define SQUARE(number) number*number
#define PENALTY(miles_traveled) SQUARE((MAX_DAILY_TRAVEL_DISTANCE-miles_traveled))
#define INT_MAX 100000000

typedef std::vector<std::vector<int>> matrix_t;

int minimumPenalty(const std::vector<int>& distances)
{
    matrix_t DP(
        distances.size(),                                       // Number of rows to allocate
        std::vector<int>(distances.size(), INT_MAX)             // Set each penalty to infinity
    );                                      
                                                          
    for (int i = distances.size()-1; i >= 0 ; i--) {
        for (int j = i; j <=distances.size(); j++) {
            if (i == j) {                                         // If equal penalty is 0
                DP[i][j] = 0;
            }                                                     // If adjacent find distance by subtraction
            else if (j == (i+1)) {
                if ((distances[j]-distances[i]) > MAX_DAILY_TRAVEL_DISTANCE) {
                    return INT_MAX; 
                }
                DP[i][j] = PENALTY((distances[j]-distances[i]));
            }
            else {
                if (PENALTY((distances[j]-distances[i])) < MAX_DAILY_TRAVEL_DISTANCE) {
                    DP[i][j] = PENALTY((distances[j]-distances[i]));    // If direct path is possible set as initial value
                }
                for (int k = i+1; k < j; k++) {
                    DP[i][j] = std::min(DP[i][j], DP[i][k] + DP[k][j]); // Keep trying to find a smaller path from already calculated paths
                }
            }
        }
    }

    return DP[0][distances.size()-1];
}

int main(int argc, char* argv[])
{
    std::vector<int> distances {100, 204, 400, 500, 600, 700, 800, 899};
    std::cout << minimumPenalty(distances) << std::endl;
    exit(EXIT_SUCCESS);
}