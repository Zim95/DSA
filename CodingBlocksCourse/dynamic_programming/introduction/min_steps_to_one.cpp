/*
MIN STEPS TO ONE:
=================
We have a number and we need to minimize it to 1.
We can either divide by 3. If and only if divisible by 3.
We can either divide by 2. If and only if divisible by 2.
We can either subtract 1. Otherwise.

Since, this is a min max type problem.
Let's try a greedy approach.
We try dividing by 3 until we can no longer.
We try dividing by 2 until we can no longer.
Then we subtract 1 for the remaining part.

Some things to remember:
------------------------
1. A number can be divided by both 3 and 2. Like 6.
   In such cases, there will be multiple paths.

Incase of greedy, we always go for the biggest division.
Then gradually move down towards subtracting by 1.

But that does not always lead to the optimal solution.

Consider,
num1 = 9
Now, if we follow the greedy algorithm,
Step 1: 9/3 = 3
Step 2: 3/3 = 1

Two steps

This really is the fastest solution for this number.

However, Consider,
num2 = 10
Now, if we follow the greedy algorithm,
Step 1: 10/2 = 5 (Because 10 cannot be divided by 3, the next biggest number is 2).
Step 2: 5 - 1 = 4 (Because, 5 cannot be divided by 3 or 2, so we need to subtract 1).
Step 3: 4/2 = 2
Step 4: 2/2 = 1

It took four steps greedily.
But if we would have followed this instead:
Step 1: 10 - 1 = 9
Step 2: 9/3 = 3
Step 3: 3/3 = 1
It would only take 3 steps.
So see, in this case greedy was not the solution.

So this means, we need to add dynamic programming into our solution.

There are always two ways to do this:
1. Memoization (Top down - Recursive).
2. Tabulation (Bottom up - Iterative).

Memoization:
------------
This problem can really be defined as:
f(n) = min(f(n/3), f(n/2), f(n-1))

In recursive approach, we need to save a cache, which will be an array.

cache = []

The function will be as follows:

Consider number 5:
    5 -> 4 (This is n-1 because only option)-> 2 (this is 4/2)-> 1 (this is 2/2)
                                                              -> 1 (this is 2-1)
                                            -> 3 (this is 4-1)-> 1 (this is 3/3)
                                                              -> 2 (this is 3-1) -> 1 (this is 2/2)
                                                                                 -> 1 (this is 2-1)
    
    5 -> 4, n=4, count=1
    4 -> 2, n=2, count=2
    2 -> 1, n=1, count=3
    So n/2 path gives count of 3.

    5 -> 4, n=4, count=1
    4 -> 3, n=3, count=2
    3 -> 1, n=1, count=3
    This n-1, followed by n/3 path also gives us 3

    5 -> 4, n=4, count=1
    4 -> 3, n=3, count=2
    3 -> 2, n=2, count=3
    2 -> 1, n=1, count=4
    This path takes 4.

func min_to_one(int n, int count=0):
    // base case
    if n == 1:
        return count
    if cache[n]:
        return cache[n]
    res = min(
        [
            min_to_one(n/3, count+1) if n%3==0 else INT_MAX,
            min_to_one(n/2, count+1) if n%2==0 else INT_MAX,
            min_to_one(n-1, count+1)
        ]
    )
    cache[n] = res
    return res

As you can see the top is calculated first, technically hehe.

Tabulation:
-------------
This involves iteration.
We will hardcode the initial values known as seed values.
Then, we will build upon the seed values.

We know,
1 already 1. So 0 steps are required.
for 2, we need only 1 step no matter division or subtraction. So 1.
for 3, we know we need only 1 step. 3/3.
for 4, min(f(4/2), f(4-1)) => min(f(2), f(3)) [We already know both values].

See how bottom ip approach works. We build from the bottom.

So the function for this will be.

Say n=10
i will go from 3 to 9:
    val = 3 + 1 = 4, cache[val] = min(cache[2-1=1], cache[1-1=0]) = min([1, 1]) = 1

func min_to_one(int n):
    cache = [1, 1, 1] // fill first 3 values.
    for i in range(3, n):
        val = i+1
        cahce[val] = min(
            [
                cache[val/3 - 1] if val%3==0 else INT_MAX,
                cache[val/2 - 1] if val%2==0 else INT_MAX,
                cache[val-2]
            ]
        )
    return cache[val]

THERE NEED TO BE A FEW CORRECTIONS IN THE ALGORITHM.
The changes are:
Top down approach:
------------------
1. We are adding the path as we go from top to bottom. And in the end we return the path.
2. This approach is wrong.
3. Instead we need to calculate the path of the sub problem first and then store its count.
4. We were storing the count of the entire path. This is wrong.

Bottom up approach:
-------------------
1. Everything is fine, except we need to add +1 at the end.
    Why?
    so, we know,
    1 is already 1 so it needs 0 steps to be 1.
    2 needs only 1 step to be 1, i.e. either 2/2 or 2-1. Either ways, only one step.
    3 needs 1 step to be 1. i.e. 3/3.
    
    Say you have the number 4,
    4 cannot be divided by 3,
    So, we divide it by 2.
    The result of cache[2] is 1. Because, 2/2 is also 1 and 2-1 is also 1.
    It only needs one step. This is a seed value.
    If we return cache[2], then we return 1.
    However, the total cost for the number 4 is 2.
    Because 4 -> 2 - > 1.
    We need to consider the step, 4 -> 2 (1 step)
    Then we have, cache[2] (1 step)
    Total = 4->2 + cache[2] = 1 + 1 = 2
    So we need to add 1.
*/

#include<iostream>
#include<climits>
#include<string>

using namespace std;

int msto_memoization(int n, int cache_memoization[]) {
    // base case
    if(n == 1) {
        return 0;
    }
    // cache case
    if(cache_memoization[n] != -1) {
        return cache_memoization[n];
    }
    int na = n % 3 == 0? msto_memoization(n/3, cache_memoization): INT_MAX;
    int nb = n % 2 == 0? msto_memoization(n/2, cache_memoization): INT_MAX;
    int nc = msto_memoization(n-1, cache_memoization);
    int result = min(na, min(nb, nc)) + 1;
    cache_memoization[n] = result;
    return result;
}

int msto_tabulation(int n, int cache_tabulation[]){
    // seed values
    cache_tabulation[0] = 0;
    cache_tabulation[1] = 0;
    cache_tabulation[2] = 1;
    cache_tabulation[3] = 1;
    // return directly if seed value
    if(n<4) {
        return cache_tabulation[n];
    }
    // loop to build from 4 to n. (Bottom up).
    for(int i=4; i<=n; i++) {
        int na = i % 3 == 0? cache_tabulation[i/3] + 1: INT_MAX;
        int nb = i % 2 == 0? cache_tabulation[i/2] + 1: INT_MAX;
        int nc = cache_tabulation[i-1] + 1;
        int result = min(na, min(nb, nc));
        cache_tabulation[i] = result;
    }
    // return result
    return cache_tabulation[n];
}


int main() {
    int cache_memoization[100];
    int cache_tabulation[100];
    for(int i=0; i<100; i++) {
        cache_memoization[i] = -1;
        cache_memoization[i] = -1;
    }
    int res_memoization = msto_memoization(10, cache_memoization);
    int res_tabulation = msto_tabulation(10, cache_tabulation);
    cout << res_memoization << "," << res_tabulation;
    return 0;
}
