//Author: Will Nguyen
//Date: 03/31/2025

#include "bdc.h" //including necessary functions from the header file
#include <iostream>  // Add this line for debugging
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Function to convert a vector of integers into a string 
string vec_to_string(vector<int> v) {
    string result = "["; //declare a beginning of the vector
    for (size_t i = 0; i < v.size(); i++) {
        result += to_string(v[i]); //adding each component to the string
        if (i < v.size() - 1) {
            result += ", "; //-1 to not go over the index range 0 -> end
        }
    }
    result += "]";
    return result;
}


//This is a helper function that helps finds the longest vector in a list of vectors
vector<int> find_longest_vector(const std::vector<std::vector<int>>& candidates) {
    vector<int> longest; //Create a placeholder for the longest vector
    for (const auto& vec : candidates) {
        if (vec.size() > longest.size()) { //iterates through 
            longest = vec; //if the code sees a longer vector, it puts it in the place holder
        }
    }
    return longest;
}

//This is the main function that sorts the input and calls the recursive function
vector<int> biggest_divisible_conglomerate(vector<int> input) {
    if (input.size() <= 1) return input; //Base case: Empty list and lists of one element

    //We are sorting the integers in the input so that smaller numbers 
    //appear first and can be checked for divisibility with higher numbers in the list
    sort(input.begin(), input.end());
    int size = input.size();

    // Initialize a DP table where each element is a vector of integers
    // It will store the largest divisible conglomerate that ends it element input[i]
    vector<vector<int>> dp(size);

    // Each element starts with itself as a conglomerate so 
    // dp[i] is just a vector containing the element input[i] itself. 
    for (int i = 0; i < size; i++) {
        dp[i] = {input[i]};
    }

    // Fill the DP table by finding valid conglomerates
    for (int i = 1; i < size; i++) { 
        // For each element input[i], the code checks all previous elements input[j]
        for (int j = 0; j < i; j++) {
            // Check if input[i] is divisible by input[j]
            if (input[i] % input[j] == 0) {
                // If adding input[i] to dp[j] gives a longer conglomerate, update dp[i]
                if (dp[i].size() < dp[j].size() + 1) {
                    dp[i] = dp[j]; // Copy the conglomerate from dp[j], this was already calculated 
                    if (find(dp[i].begin(), dp[i].end(), input[i]) == dp[i].end()) { // Ensure each new element is unique
                        // Add input[i] to the conglomerate. This finishes the update
                        dp[i].push_back(input[i]); 
                    }
                }
            }
        }
    }

    // Find and return the longest conglomerate in the dp table
    return find_longest_vector(dp);
}

// Time Complexity Analysis:
// - Sorting the array: O(N log N)
// - DP table construction: O(N^2) (Each element checks all previous elements)
// - Reconstructing the subset: O(N)
// Overall complexity: O(N^2) (Efficient compared to recursive approach O(2^N))