/*
    MAX SUBARRAY
    ============
    We are given an array.
    We need to find all subarrays.
    We need to find the subarray with the highest sum.

    We cannot just go with the biggest subarray because
    Our set also includes negative numbers. 

    So no greedy approach here.

    The sum of elements from i to j is an O(n) problem.
    Therefore, we need to make a prefix sum array.
    So that this operation is reduced to O(1).

    So first we create the prefix sum and the rest is explained in the functions.

    NOTE: We assume that the lowest possible value is -9999.
          In reality, this is not the case.
          But we definitely can work this out from the problem statement.
    

    RESULT:
    -------
    Wrong Answer, but both the approaches gave the same wrong answer.
    So that means, we were successful in creating the same solution
    both recursively and iteratively. That is an acheivement.

    However, the solution was wrong.

    SOLUTION:
    ---------
    We will look at Prateek Narang's solution.
*/
#include<iostream>
#include<climits>
#define lower_limit -10000

using namespace std;

int get_prefix_sum(int prefix_sum[], int i, int j) {
    if(i=0) {
        // this means the entire sum upto that point.
        return prefix_sum[j];
    }
    return prefix_sum[j] - prefix_sum[i-1];
}

int max_subarray_memoization(int arr[], int prefix_sum[],
                             int cache_memoization[][100],
                             int start, int end) {
    /*
        So the goal here is as follows:
        1. The biggest subarray wins.
        2. We first get the prefix sum of the array.
        3. Then compare it to the result of the subarrays.
        4. Whichever wins is the max subarray.

        For dividing the problem, our recurrence relation follows:
        The wines problem.
        Left subtree: f(i, j-1)
        Right subtree: f(i+1, j)

        So the comparison would be:
        max(
            current_prefix_sum,
            left subtree,
            right subtree
        )
    */
    // base case
    if(start == end) {
        return arr[start];
    }
    if(cache_memoization[start][end] != lower_limit) {
        return cache_memoization[start][end];
    }

    // first get the prefix sum
    int ps = get_prefix_sum(prefix_sum, start, end);
    int psl = max_subarray_memoization(arr, prefix_sum, cache_memoization, start, end-1); // left subtree
    int psr = max_subarray_memoization(arr, prefix_sum, cache_memoization, start+1, end); // right subtree
    int result = max(ps, max(psl, psr));
    cache_memoization[start][end] = result;
    return result;
}

int max_subarray_tabulation(int arr[], int size, int cache_tabulation[][100], int prefix_sum[]) {
    /*
        The goal is to get all the results inside the cache.
        Then get the maximum value of the cache.
    */
    // fill all the diagonal base cases:
    for(int i=0; i<size; i++) {
        // these are diagonal base cases: [0][0], [1][1], and so on.
        // [0][0] = [0], [1][1] = [1]
        cache_tabulation[i][i] = arr[i];
    }
    /*
        fill diagonally.
        ----------------
        (0,1) -> (1,2) -> (2,3)
        (0,2) -> (1,3)
        (0,3)

        The difference increases by 1 then 2 then 3.

        Also, in this case: [i][j] == [j][i]
        The i,j variables just give the range.
        Doesnt matter which one comes first. We only need the range.

        So if we do have to fill the cache, then the values in the cache
        would have the same values on either side of the diagonal.
        Because they mean the same thing.
    */
    int diff = 1;
    while(diff != size) {
        for(int p=0; p<size-1; p++) {
            int q = p+diff;
            int ps = get_prefix_sum(prefix_sum, p, q);
            int psl = cache_tabulation[p-1][q];
            int psr = cache_tabulation[p][q-1];
            int result = max(ps, max(psl, psr));
            cache_tabulation[p][q] = cache_tabulation[q][p] = result;
        }
        diff++;
    }

    // Now that the cache is filled, get the maximum.
    // NOTE: This step can be ommitted if we maintain the maxm 
    //        while calculating the values themselves. 
    int maxm = INT_MIN;
    for(int x=0; x<size; x++) {
        for(int y=0; y<size; y++) {
            if(cache_tabulation[x][y] > maxm) {
                maxm = cache_tabulation[x][y];
            }
        }
    }
    return maxm;
}

bool check_for_positivity(int arr[], int size) {
    // Returns true as soon as a positive integer or 0 is found in the array.
    for(int i=0; i<size; i++) {
        if(arr[i] >= 0) {
            return true;
        }
    }
    return false;
}

bool check_for_negativity(int arr[], int size) {
    // Returns true as soon as a negative integer is found in the array.
    for(int i=0; i<size; i++) {
        if(arr[i] < 0) {
            return true;
        }
    }
    return false;
}

int max_subarray(int arr[], int size) {
    /*
        PRATEEK NARANG'S SOLUTION:
        ==========================
        So, the solution in this case completely ignores negative sums.
        Even arr[0] is initialized with 0, if it is a negative number.

        Now, one question:
        ------------------
        What if all the arr elements are negative?
        Do we just return 0?

        Assuming we do, here is the solution:
        - Initialize the cache with 0
        - Set the first value, i.e. cache[0] to 0 if it is less than 0,
            else the value will be arr[0]
        - Now, just have a loop and keep accumulating the values keeping track of the max sum.
            - If the sum becomes less than 0, just set the value to 0.
        - How is this not O(n2)? Because we have precalculated values in the cache. Duh!

        The logic is:
        -------------
        If there is atleast one positive number in the array.
        It is guaranteed that the max sum will be a positive number as well.
        Even if it means just using that one positive element as a subarray.

        But, what if there isn't.

        Now you might think,
        - Well dude, we could just take a smaller lower limit like INT_MIN.
        - We can assume, none of the values go below INT_MIN.
        - Then, we just use the same algorithm and it works right?

        NO, IT DOESNT. IT DEFINITELY DOESNT.
        We got wrong answer when we kept the minimum value to INT_MIN.
        So, this algorithm only works, when there is atleast one positive value in the array.

        If every element in the array is a negative number, then we will return 0.
        Which is wrong answer but it is what it is.

        Solution:
        ---------
        - Have a check for the edge case:
        - If all values are negative,
        - The maximum sum will be a single element.
        - The one with the largest value.

        Conversely,
        - If all values are positive, then return the sum of the entire array.
        - Because that would undoubtedly be the largest sum.
    */
    // edge case 1: all values in the array are negative. Not part of Prateek's solution.
    if(!check_for_positivity(arr, size)) {
        int maxm = arr[0];
        for(int i=1; i<size; i++) {
            if(arr[i] > maxm) {
                maxm = arr[i];
            }
        }
        return maxm;
    }
    // edge case 2: all values in the array are positive. Not part of Prateek's solution.
    if(!check_for_negativity(arr, size)) {
        // return the sum of all the elements.
        int sum = arr[0];
        for(int i=1; i<size; i++) {
            sum += arr[i];
        }
        return sum;
    }

    // otherwise keep track of the max so far and go on.
    int cache[100] = {0};
    cache[0] = arr[0] > 0? arr[0]: 0; // If less than 0, then 0 else whatever value.
    int max_so_far = cache[0];
    for(int i=1; i<size; i++) {
        cache[i] = cache[i-1] + arr[i]; // Kind of like caclulating prefix sum. Its the same idea, just that we do it live.
        if(cache[i] < 0) {
            cache[i] = 0;
        }
        max_so_far = max(cache[i], max_so_far);
    }
    return max_so_far;
}

int max_subarray_space_optimized(int arr[], int size) {
    /*
        LADIES AND GENTLEMEN: THIS IS KADANE'S ALGORITHM:
        --------------------------------------------------
        Probably one of the most important algorithms you'll ever learn.

        So, this algorithm builds up from the previous logic.
        
        If you look at Prateek's solution,
        You see that the only purpose of the cache is to give us
        the prefix sum result of the previous element.
        Which is basically, the cumulative sum upto that point.

        We could pretty much use a variable for that right.
        We dont really need a cache to do it.
        So let's do it.
    */
    // edge case 1: all values in the array are negative. Not part of Prateek's solution.
    if(!check_for_positivity(arr, size)) {
        int maxm = arr[0];
        for(int i=1; i<size; i++) {
            if(arr[i] > maxm) {
                maxm = arr[i];
            }
        }
        return maxm;
    }
    // edge case 2: all values in the array are positive. Not part of Prateek's solution.
    if(!check_for_negativity(arr, size)) {
        // return the sum of all the elements.
        int sum = arr[0];
        for(int i=1; i<size; i++) {
            sum += arr[i];
        }
        return sum;
    }
    int max_so_far = arr[0] > 0? arr[0]: 0;
    int count_so_far = max_so_far;
    for(int i=1; i<size; i++) {
        count_so_far = count_so_far + arr[i]; // Kind of like caclulating prefix sum. Its the same idea, just that we do it live.
        if(count_so_far < 0) {
            count_so_far = 0;
        }
        max_so_far = max(count_so_far, max_so_far);
    }
    return max_so_far;
}

int main() {
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int size = sizeof(arr)/sizeof(int);

    int prefix_sum[10] = {0};
    prefix_sum[0] = arr[0];
    for(int i=1; i<size; i++) {
        prefix_sum[i] = arr[i] + prefix_sum[i-1];
    }

    int cache_memoization[100][100];
    int cache_tabulation[100][100];
    for(int p=0; p<100; p++) {
        for(int q=0; q<100; q++) {
            cache_memoization[p][q] = lower_limit;
            cache_tabulation[p][q] = lower_limit;
        }
    }
    cout << "This is the result of our own solution: " << endl;
    int rmem = max_subarray_memoization(arr, prefix_sum, cache_memoization, 0, size-1);
    int rtab = max_subarray_tabulation(arr, size, cache_tabulation, prefix_sum);
    cout << rmem << "," << rtab << endl << "---------------------------------------" << endl;

    cout << "This is Prateek Narang's solution: " << endl;
    int r = max_subarray(arr, size);
    cout << r << endl << "-----------------------------" << endl;

    cout << "This is the Space optimized solution: (KADANE'S ALGORITHM)" << endl;
    int rs = max_subarray_space_optimized(arr, size);
    cout << rs << endl << "----------------------------" << endl;
    return 0;
}