/*
	PPP Exercise 5.11
	7 December 2023
	Find the largest Fibonacci Number that you can represent with an `int`.
*/
#include "../std_lib_facilities.h"


bool int_overflow(int sum, int prev_sum, int curr_val){
	// Check for integer overflow from summing operation
	if ((sum < 0 && prev_sum > 0 && curr_val > 0) ||
		(sum >= 0 && prev_sum < 0 && curr_val < 0)){
		return true;
	}
	else
		return false;
}


int main(){
	bool stop {false};
	int x1 {0};
	int x2 {1}; // our current Fibonacci number (x2 := x1 + x2)
	int prev_sum {0};

	cout << "Fibonacci Sequence:\n";
	while (not stop){
		cout << x2 << '\n';
		stop = int_overflow(x1+x2, x1, x2);
		// The following will eventually overflow, but we stop before printing
		// the associated value.
		x2 = x1 + x2;
		x1 = x2 - x1;
	}
}

/* 
Output
===
Fibonacci Sequence:
1
1
2
3
5
8
13
21
34
55
89
144
233
377
610
987
1597
2584
4181
6765
10946
17711
28657
46368
75025
121393
196418
317811
514229
832040
1346269
2178309
3524578
5702887
9227465
14930352
24157817
39088169
63245986
102334155
165580141
267914296
433494437
701408733
1134903170
1836311903  
===
1836311903 is the largest Fibonacci value represented by an `int`.
*/
