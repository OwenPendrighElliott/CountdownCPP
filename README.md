# Countdown Numbers C++

I decided that it was time to learn C++, this is a C++ version of [my other countdown solver I made in Python.](https://github.com/OwenPendrighElliott/countdown_solver)

Due to the speed of C++ in comparison to Python this version uses some slightly different optimisations and can search for an arbitrary number of solutions.

## Usage

The code can be compiled with:

`g++ -O3 -o nums countdown_number_solver.cpp`

And then ran with:

`./nums [numbers] [target] [optional number of solutions]`

e.g.

`./nums 100-50-25-2-3-1 949 3`

To get:

<pre>
Solution 1 found after expanding 49861 nodes!
Multiply 3 and 2 to get 6
Subtract 25 and 6 to get 19
Multiply 50 and 19 to get 950
Subtract 950 and 1 to get 949

Solution 2 found after expanding 137230 nodes!
Subtract 50 and 1 to get 49
Add 25 and 2 to get 27
Divide 27 and 3 to get 9
Multiply 100 and 9 to get 900
Add 900 and 49 to get 949

Solution 3 found after expanding 137476 nodes!
Subtract 50 and 1 to get 49
Add 25 and 2 to get 27
Multiply 100 and 27 to get 2700
Divide 2700 and 3 to get 900
Add 900 and 49 to get 949
</pre>
