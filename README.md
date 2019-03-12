# Competitive programming solutions

These are my solutions of some competitive programming problems.

* To isolate the main idea of a solution, almost all solutions are split into three stages:
	1. read input data into the operating memory with some preprocessing,
	2. apply the main algorithm,
	3. output the result.
* Similar problems are solved using different algorithms and data structures &mdash; sometimes using those provided by the Standard library, sometimes using my own ones.
* Input data is assumed to be always correct, `assert`s in the code are quite sporadic and not exhaustive.

### *UVa* problems

| ID     | Title 					 	    | Categories  			  										|
|:------:|:---------------------------------|:--------------------------------------------------------------|
| 001 08 | Maximum sum                   	| Maximum subarray, Kadane's algorithm							|
| 001 09 | Scud busters                  	| Convex hulls													|
| 001 12 | Tree summing 					| Binary trees													|
| 001 47 | Dollars 							|																|
| 001 64 | String computer 					| Dynamic programming, edit distance							|
| 002 00 | Rare order 						| Graphs, topological sorting, depth-first search				|
| 002 16 | Getting in line 					|																|
| 002 18 | Moth eradication 				|																|
| 002 22 | Budget travel 					|																|
| 002 40 | Variable radix Huffman encoding 	| Huffman trees, depth-first search								|
| 002 59 | Software allocation				|																|
| 002 64 | Count on cantor 					|																|
| 002 70 | Lining up 						|																|
| 002 94 | Divisors 						|																|
| 003 34 | Identifying concurrent events 	|																|
| 003 48 | Optimal array mult. sequence		| Dynamic programming, matrix-chain multiplication  			|
| 003 50 | Pseudo random numbers 			|																|
| 003 57 | Count the ways 					|																|
| 003 61 | Cops and robbers 				|																|
| 004 29 | Word transformation 				|																|
| 004 37 | Tower of Babylon 				|																|
| 004 39 | Knight moves 					| Breadth-first search											|
| 004 54 | Anagrams 						|																|
| 004 55 | Periodic strings 				|																|
| 004 59 | Graph connectivity 				|																|
| 004 69 | Wetlands of Florida 				|																|
| 004 81 | What goes up 					| Longest increasing subsequence, `std::lower_bound`			|
| 004 82 | Permutations arrays 				|																|
| 005 01 | Black box 						| AVL trees, binary tree iterators								|
| 005 07 | Jill rides again 				| Maximum subarray, Kadane's algorithm							|
| 005 16 | Prime land 						|																|
| 005 26 | String distance 					|																|
| 005 36 | Tree recovery 					|																|
| 005 40 | Team queue 						|																|
| 005 43 | Goldbach conjecture 				|																|
| 005 48 | Tree 							|																|
| 005 51 | Nesting bunch of brackets 		|																|
| 005 58 | Wormholes 						|																|
| 005 62 | Dividing coins 					|																|
| 005 74 | Sum it up 						|																|
| 005 83 | Prime factors 					|																|
| 006 12 | DNA sorting 						| Merge sort, inversions counting								|
| 006 30 | Anagrams 						|																|
| 006 39 | Don't get rooked 				|																|
| 006 74 | Coin change 						|																|
| 006 79 | Dropping balls 					|																|
| 006 84 | Integral determinant 			| Gaussian elimination, Euclid's algorithm						|
| 006 86 | Goldbach conjecture II 			|																|
| 007 01 | The archeologists' dilemma 		|																|
| 007 14 | Copying books 					| Linear partitioning, binary search							|
| 007 29 | The Hamming distance problem 	|																|
| 007 50 | Eight queens chess problem 		|																|
| 007 93 | Network connections 				|																|
| 008 20 | Internet bandwidth 				|																|
| 008 33 | Water falls 						|																|
| 008 68 | Numerical maze 					|																|
| 008 72 | Ordering							|																|
| 009 08 | Reconnecting computer sites 		|																|
| 009 29 | Number maze 						|																|
| 009 42 | Cyclic numbers 					| Rational numbers, decimal fractions, `std::unordered_map`		|
| 009 90 | Diving for gold 					|																|
| 009 91 | Safe salutations 				| Combinatorics, recurrence relations, Catalan numbers			|
| 012 10 | Sum of consecutive prime numbers |																|
| 012 52 | Twenty questions 				|																|
| 012 60 | Sales 							|																|
| 013 72 | Log jumping 						|																|
| 100 03 | Cutting sticks 					|																|
| 100 04 | Bicoloring 						|																|
| 100 61 | How many zeros and digits?		|																|
| 101 07 | What is the median 				| `std::priority_queue`											|
| 101 71 | Meeting prof. Miguel 			|																|
| 102 23 | How many nodes 					| Combinatorics, recurrence relations, Catalan numbers			|
| 102 29 | Modular Fibonacci 				| Fibonacci numbers, modular exponentiation						|
| 102 45 | The closest pair problem 		|																|
| 102 68 | 498-bis 							|																|
| 102 82 | Babelfish 						| Hash tables													|
| 102 98 | Power strings 					|																|
| 103 05 | Ordering tasks 					|																|
| 103 11 | Goldbach and Euler 				|																|
| 103 19 | Manhattan 						|																|
| 103 27 | Flip sort 						| AVL trees														|
| 103 82 | Watering grass 					| Greedy algorithms, interval covering							|
| 104 96 | Collecting beepers 				|																|
| 105 33 | Digit primes 					|																|
| 105 67 | Helping Fill Bates 				|																|
| 105 70 | Meeting with aliens				| Permutations, swaps counting, cycles counting					|
| 105 76 | Y2K accounting bug 				|																|
| 105 86 | Polynomial remains 				|																|
| 106 00 | ACM contest and blackout 		|																|
| 106 04 | Chemical reaction 				|																|
| 106 51 | Pebble solitaire 				|																|
| 106 55 | Contemplation! algebra 			| Recurrence relations, modular exponentiation					|
| 106 64 | Luggage 							|																|
| 106 84 | Jackpot 							|																|
| 106 99 | Count the factors 				|																|
| 107 23 | Cyborg genes 					|																|
| 107 38 | Riemann *vs* Mertens 			|																|
| 108 01 | Lift hopping 					|																|
| 108 10 | Ultra quicksort 					| Merge/insertion sort, inversions counting						|
| 108 70 | Recurrences 						|																|
| 109 31 | Parity 							|																|
| 109 34 | Dropping water balloons 			|																|
| 109 35 | Throwing cards away 				| Queues														|
| 109 38 | Flea circus 						|																|
| 109 54 | Add all 							| Heaps															|
| 109 57 | Su Doku checker 					| Backtracking, bit masks										|
| 110 57 | Exact sum 						|																|
| 110 60 | Beverages 						|																|
| 110 77 | Find the permutations			| Combinatorics, recurrence relations, Stirling numbers			|
| 111 37 | Ingenuous cubrency 				|																|
| 111 71 | SMS 								|																|
| 111 95 | Another `N`-queen problem 		|																|
| 112 27 | The silver bullet 				|																|
| 112 35 | Frequent values 					|																|
| 112 36 | Grocery store 					|																|
| 112 71 | Lattice of resistors 			| Recurrence relations, asymptotic expansions, `<cmath>`		|
| 114 13 | Fill the containers 				|																|
| 114 20 | Chest of drawers					| Combinatorics, recurrence relations 			 				|
| 114 56 | Trainsorting 					|																|
| 114 62 | Age sort 						| Count sort													|
| 114 63 | Commandos 						|																|
| 114 75 | Extend to palindrome 			|																|
| 115 17 | Exact change 					|																|
| 115 84 | Partitioning by palindromes 		|																|
| 116 34 | Generate random numbers 			|																|
| 116 58 | Best coalitions 					|																|
| 116 86 | Pick up sticks 					|																|
| 116 91 | Allergy test 					|																|
| 117 14 | Blind sorting 					| Order statistics (2<sup>nd</sup> largest)						|
| 117 33 | Airports 						|																|
| 119 02 | Dominator 						|																|
| 119 91 | Easy problem from Rujia Liu? 	| `std::sort`, `std::lower_bound`								|
| 119 97 | `K` smallest sums 				|																|
| 120 86 | Potentiometers 					| Fenwick trees													|
| 121 05 | Bigger is better 				|																|
| 121 92 | Grapevine 						|																|
| 122 38 | Ants colony 						|																|
| 123 47 | Binary search tree 				| Binary search trees, pre/post-order traversal					|
| 124 55 | Bars 							|																|
| 124 58 | Oh, my trees! 					|																|
| 125 04 | Updating a dictionary 			| Quick sort													|
| 126 40 | Largest sum game 				| Maximum subarray, Kadane's algorithm							|
| 126 97 | Minimal subarray length 			|																|

<!--| 008 36 | Largest submatrix				| Largest submatrix (dynamic programming)						|-->

### *Geeks for geeks* problems

| Title 				 	       			| Categories  			  										|
|:------------------------------------------|:--------------------------------------------------------------|
| Largest square formed in a matrix			| Dynamic programming, largest square submatrix 				|



