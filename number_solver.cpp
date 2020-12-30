#include <iostream>
#include <vector>
#include <tuple>
#include <deque>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// helper to print a vector, used for debugging
void print_vector(vector<int> &input) {
    for (int i = 0; i < input.size(); i++) {
        cout << input.at(i) << " ";
    }
    cout << "\n";
}

// returns all possible pairwise combinations of numbers in a vector (not permutations)
vector<tuple<int, int>> combinations(vector<int> input) {
    vector<tuple<int, int>> output;
    for (int i = 0; i < input.size(); i++) {
        for (int j = i+1; j < input.size(); j++) {
            output.push_back(make_tuple(input[i], input[j]));
        }
    }
    return output;
}

// helper to return an 'action' given an operation code
int perform_operation(int num1, int num2, int opCode) {
    if (opCode==0) {
        return num1 + num2;
    }
    else if (opCode==1) {
        return num1 - num2;
    }
    else if (opCode==2) {
        return num1 * num2;
    }
    else if (opCode==3) {
        if  (num1==0 || num2==0)
            return -1;
        if (num1%num2 != 0) 
            return -1;
        return num1/num2;
    }
    return -1;
}

// helper function to efficiently remove one occurance of an element from a vector - avoids the need for elements
// above the one being replaced to be copied down
vector<int> replace_once(vector<int> vec, int el) {
    auto oc = find(vec.begin(), vec.end(), el);
    if (oc != vec.end()) {
        iter_swap(oc, vec.end() - 1);
        vec.erase(vec.end() - 1);
    }
    return vec;
}

// main solving method
vector<string> solve(vector<int> numbers, int goal) {

    // initialise the deques for the numbers and the path (used in tandem)
    // deque will be used as FIFO
    deque<vector<int>> numQ; 
    deque<vector<string>> pthQ;
    numQ.push_front(numbers);
    vector<string> path = {""};
    pthQ.push_front(path);

    // to make printing the path taken easier
    unordered_map<int, string> opCodetoOp = {{0, "add"}, {1, "subtract"}, {2, "multiply"}, {3,"divide"}};

    // count the nodes expanded
    int nodes = 0;

    // while the queue has elements
    while (!numQ.empty()) {
        vector<int> nums = numQ.back();
        vector<string> path = pthQ.back();
        numQ.pop_back();
        pthQ.pop_back();

        // if the target number is in the numbers then return the path as we have achieved a solution
        if (count(nums.begin(), nums.end(), goal)) {
            cout << "Solution found after expanding " << nodes << " nodes!\n";
            return path;
        } else {
            vector<tuple<int, int>> combs = combinations(nums);
            for(auto const& tup: combs) {
                int num1 = get<0>(tup);
                int num2 = get<1>(tup);

                for (int i=0; i<4; i++) {
                    int result = perform_operation(num1, num2, i);
                    if (result < 0) 
                        continue;
                    ++nodes; // increment the nodes expanded
                    vector<int> new_nums = replace_once(nums, num1);
                    new_nums = replace_once(new_nums, num2);

                    string step = opCodetoOp[i] + " " + to_string(max(num1, num2)) + " and " + to_string(min(num1, num2)) + " to get " + to_string(result);
                    
                    vector<string> new_path = path;
                    new_path.push_back(step);
                    new_nums.push_back(result);

                    numQ.push_front(new_nums);
                    pthQ.push_front(new_path);
                }

            }
        }
    }
    cout << "No solution exists, " << nodes << " nodes were expanded";
    vector<string> fail = {"No Solution :("};
    return fail;
}


int main() {

    // prompt for numbers
    cout << "\nEnter the numbers: \n";
    string numberStr;
    cin >> numberStr;

    // get these numbers into a vector
    replace( numberStr.begin(), numberStr.end(), '-', ' ');
    stringstream numberStrStream(numberStr);
    int number;
    vector<int> numbers;
    while (numberStrStream >> number)
        numbers.push_back(number);

    // get target number
    cout << "Please enter a target number: \n";
    int goal;
    cin >> goal;

    // solve the problem
    vector<string> solution = solve(numbers, goal);

    // print the solution
    for (auto const& step: solution) {
        cout << step << "\n";
    }

    return 0;
}