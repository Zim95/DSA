/*
    MIN COIN EXCHANGE:
    ==================
    You are given an array of coin values. You have infinite number of these coins.
        coins = [1, 2, 10, 20, 100, 200, 500, 1000]
    And a value N = 137 Rs.

    You need to generate the number using the least number of coins.

    Solution Approach:
    ------------------
    Usually, one would go for a greedy approach.
    i.e. Use the biggest coin until you can't anymore.
         Then use the smaller one.
    
    Consider the case above,
    Greedily,
        - We would first pick 100
        - Then, 20 x 1
        - Then 10 x 1
        - Then 2 x 3
        - Then 1 x 1
        So a total of -> 3 + 1 + 1 + 1 = 6 coins.
    This case, the greedy output is actually correct.

    But consider this case,
    coins = [1, 7, 10]
    N = 15

    The greedy approach would give us,
    10 + 1 + 1 + 1 + 1 = 15
    So total of 5 coins.

    Whereas, the optimum approach would be,
    7 + 7 + 1 = 15
    Only 3 coins

    So we need to use Dynamic Programming.

    Algorithm:
    ----------
    if(n==0) {
        // no more path to add
        return 0;
    }
    int minsteps_memoization = INT_MAX;
    for(int i=0; i<size; i++) {
        // if the value of the coin is greater than remaining n, skip the loop.
        if(n < coins[i]) {
            continue;
        }
        int res = min_coins_memoization(coins, cache_memoization, size, n-coins[i]) + 1;
        if(res < minsteps_memoization) {
            minsteps_memoization = res;
        }
    }
    return minsteps_memoization;

    This would be the recursive algorithm.
    But this takes a lot of time.
    Therefore, we need to apply a cache to the mix.

    But cache is applied on path.
    What path do we take here?

    Cache what exactly?

    So the problem definition is
    f(n) = min(
        f(n-coins[0]) + 1,
        f(n-coins[1]) + 1,
        and so on,....
        f(n-coins[size]) + 1
    )
    So the value we need to cache is: n-coins[i]
    This value is passed recursively as n.
    So we need to cache n.
*/
#include<iostream>
#include<climits>

using namespace std;

int min_coins_memoization(int coins[], int cache_memoization[], int size, int n) {
    // base case: n is 0
    if(n==0) {
        // no more path to add
        return 0;
    }
    if(cache_memoization[n] != -1) {
        return cache_memoization[n];
    }
    int minsteps_memoization = INT_MAX;
    int res;
    for(int i=0; i<size; i++) {
        // if the value of the coin is greater than remaining n, skip the loop.
        if(n < coins[i]) {
            continue;
        }
        res = min_coins_memoization(coins, cache_memoization, size, n-coins[i]) + 1;
        if(res < minsteps_memoization) {
            minsteps_memoization = res;
        }
    }
    cache_memoization[n] = res;
    return minsteps_memoization;
}


int min_coins_tabulation(int coins[], int cache_tabulation[], int size, int n) {
    /*
        Usually in case of tabulation.
        We have known base cases.
        But here we dont.
        
        The base cases are values in the array.
        We dont have any fixed cases.

        in case, of {1, 7, 10}
        f(n) = min(
            f(n-1),
            f(n-7),
            f(n-10)
        ) + 1
        So if n is 15.
        f(15) = max(f(14), f(8), f(5)) and so on.
        So we need to first get these values.
        
        There might be more values depending
        on the length of the array.
        
    */
    cache_tabulation[0] = 0; // base case.
    for(int f_of=1; f_of<=n; f_of++) {
        // the outer loop will go upto n. If n is 15, this will go from 1,2,3,4,....15
        // for each value of i there will be only some permissible deductions.
        
        // getting the minimum value from the deductions
        /*
            How do you get deductions.
            Consider,
            f_of = 1
                You can subtract 1 from here.
                The computer doesnt know that,
                Therefore, it has to iterate over every element
                Make sure, that the base case has only one element subtractable.
                And build from there.
        */
        int min_coins_tabulation = INT_MAX;
        for(int ci=0; ci<size; ci++) {
            /*
                Heres how this works.
                f_of = 1,
                --> Set min value to INT MAX.
                    --> ci = 0, coins[ci] = 1
                        --> dont continue
                        --> res = cache[f_of - coins[ci]] + 1
                                = cache[1 - 1] + 1
                                = cache[0] + 1
                                = 0 + 1
                                = 1
                    --> ci = 1, coins[ci] = 7
                        --> continue
                    --> ci = 2, coins[ci] = 10
                        --> continue
                --> This case, our min value is 1.
                
                f_of = 2
                --> set min value to INT MAX.
                    --> ci = 0, coins[ci] = 1
                        --> dont continue
                        --> res = cache[f_of - coins[ci]] + 1
                                = cache[2 - 1] + 1
                                = cache[1] + 1
                                = 1 + 1
                                = 2
                    --> ci = 1, coins[ci] = 7
                        --> continue
                    --> ci = 2, coins[ci] = 10
                        --> continue
                --> This case our min value is 2

                consider, f_of = 7
                    --> ci = 0, coins[ci] = 1
                        --> dont continue
                        --> res = cache[f_of - coins[ci]] + 1
                                = cache[7 - 1] + 1
                                = cache[6] + 1
                                = cache of 6 will have been calculated by now and we just add 1.
                    --> ci = 1, coins[ci] = 7
                        --> dont continue
                        --> res = cache[f_of - coins[ci]] + 1
                                = cache[7-7] + 1
                                = cache[0] + 1
                                = 0 + 1
                                = 1
                    --> ci = 2, coins[ci] = 10
                        --> continue
                --> This case our min value will be 1.
            */
            if(f_of < coins[ci]) {
                continue;
            }
            int res = cache_tabulation[f_of - coins[ci]] + 1;
            if(res < min_coins_tabulation) {
                min_coins_tabulation = res;
            }
        }
        cache_tabulation[f_of] = min_coins_tabulation;
    }
    return cache_tabulation[n];
}


int main() {
    int coins_a[] = {1, 7, 10};
    int coins_b[] = {1, 7, 10, 15};
    int coins_c[] = {1, 2, 10, 20, 100, 200, 500, 1000};
    int size_a = sizeof(coins_a)/sizeof(int);
    int size_b = sizeof(coins_b)/sizeof(int);
    int size_c = sizeof(coins_c)/sizeof(int);

    int cache_memoization_a[100];
    int cache_memoization_b[100];
    int cache_memoization_c[100];
    int cache_tabulation_a[100];
    int cache_tabulation_b[100];
    int cache_tabulation_c[100];
    for(int i=0; i<100; i++) {
        cache_tabulation_a[i] = -1;
        cache_memoization_a[i] = -1;
        cache_tabulation_b[i] = -1;
        cache_memoization_b[i] = -1;
        cache_tabulation_c[i] = -1;
        cache_memoization_c[i] = -1;
    }

    int na = 15;
    int nb = 15;
    int nc = 137;
    int rmem_a = min_coins_memoization(coins_a, cache_memoization_a, size_a, na);
    int rmem_b = min_coins_memoization(coins_b, cache_memoization_b, size_b, nb);
    int rmem_c = min_coins_memoization(coins_c, cache_memoization_c, size_c, nc);
    int rtab_a = min_coins_tabulation(coins_a, cache_memoization_a, size_a, na);
    int rtab_b = min_coins_tabulation(coins_b, cache_memoization_b, size_b, nb);
    int rtab_c = min_coins_tabulation(coins_c, cache_memoization_c, size_c, nc);
    cout << "Memoization:" << endl;
    cout << rmem_a << "," << rmem_b << "," << rmem_c << endl;
    cout << "Tabulation:" << endl;
    cout << rtab_a << "," << rtab_b << "," << rtab_c << endl;
    
}