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

// helper to return an 'action' given an operation code
int perform_operation(const int &num1, const int &num2, const int &opCode) {
    if (opCode==0) {
        return num1 + num2;
    }
    else if (opCode==1) {
        if (num1==num2)
            return -1;
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
void replace_once(vector<int> & vec, int el) {
    auto oc = find(vec.begin(), vec.end(), el);
    if (oc != vec.end()) {
        iter_swap(oc, vec.end() - 1);
        vec.erase(vec.end() - 1);
    }
}

// main solving method
void solve(vector<int> numbers, const int goal, const int nsols) {

    // initialise the deques for the numbers and the path (used in tandem)
    // deque will be used as FIFO
    deque<vector<int>> numQ; 
    deque<string> pthQ;
    numQ.push_front(numbers);
    string path = {""};
    pthQ.push_front(path);

    // to make printing the path taken easier
    unordered_map<int, string> opCodetoOp = {{0, "Add"}, {1, "Subtract"}, {2, "Multiply"}, {3, "Divide"}};

    // count the nodes expanded
    int nodes = 0;
    int sols = 1;
    // while the queue has elements
    while (!numQ.empty()) {
        vector<int> nums = numQ.front();
        string path = pthQ.front();
        numQ.pop_front();
        pthQ.pop_front();

        // if the target number is in the numbers then return the path as we have achieved a solution
        if (nums.back() == goal) {
            cout << "Solution " << sols << " found after expanding " << nodes << " nodes!\n";
            cout << path;
            ++sols;
            if (sols>nsols)
                return;
            cout << "\n";
        } else {
            for (int i = 0; i < nums.size()-1; i++) {
                // the trick is that you never need more that 1 intermediate result
                // as such our second number only has to be one of the last 2 calculated but not yet used
                int start;
                if (i<nums.size()-2)
                    start = nums.size()-2;
                else 
                    start = nums.size()-1;
                for (int j = start; j < nums.size(); j++) {
                    int num1 = max(nums[i], nums[j]);
                    int num2 = min(nums[i], nums[j]);

                    for (int x=0; x<4; x++) {
                        int result = perform_operation(num1, num2, x);
                        if (result <= 0 || result == num1 || result == num2) 
                            continue;

                        vector<int> new_nums = nums;
                        replace_once(new_nums, num1);
                        replace_once(new_nums, num2);
                        new_nums.push_back(result);
                        
                        string new_path = path + opCodetoOp[x] + " " + to_string(num1) + " and " + to_string(num2) + " to get " + to_string(result) + "\n";
                        
                        // increment the nodes expanded
                        ++nodes;
                        numQ.push_front(new_nums);
                        pthQ.push_front(new_path);
                    }
                }
            }
        }
    }
    cout << "No more solutions exist :( - " << nodes << " nodes were expanded\n";
}


int main(int argc, char *argv[]) {

    string numberStr = argv[1];


    // get these numbers into a vector
    replace( numberStr.begin(), numberStr.end(), '-', ' ');
    stringstream numberStrStream(numberStr);
    int number;
    vector<int> numbers;
    while (numberStrStream >> number)
        numbers.push_back(number);

    int goal = atoi(argv[2]);

    int nsols = 1;
    if (argc>3)
        nsols= atoi(argv[3]);

    // solve the problem
    solve(numbers, goal, nsols);

    return 0;
}