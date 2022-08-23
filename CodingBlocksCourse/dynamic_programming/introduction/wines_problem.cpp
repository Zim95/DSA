/*
    There are N wines in a row.
    Each year you sell either the leftmost or the rightmost wine.
    I.e. Say you have these wines: [2, 4, 6, 2, 5]
        Year 1: You either sell 2 or 5. So your left with:
                [4, 6, 2, 5] or [2, 4, 6, 2]
    Now the price of the wines is k * wines[i], for every kth year.
                i.e. the first wine of value 2 will have,
                the value 2 * 1 in year 1.
                          2 * 2 in year 2.
                          2 * 3 in year 3.
                          2 * 4 in year 4...
                          and so on....
                This means, that in our example.
                After Year 1, the prices will be 2 * [4, 6, 2, 5] or 2 * [2, 4, 6, 2]
        So in year 2: our wines are either [8, 12, 4, 10] or [4, 8, 12, 4]
*/
#include<iostream>
#include<climits>

using namespace std;

int max_profit_wines_memoization(int arr[], int cache_memoization[][100], int start, int end, int k=1) {
    // base case:
    if(start == end) {
        // all wines have been sold
        return arr[start] * k; // the profit of the last wine
    }
    // cache case:
    if(cache_memoization[start][end] != -1) {
        return cache_memoization[start][end];
    }
    // recursive case: max(pick 1st + f(remaining), pick last + f(remaining))
    int pick_first = arr[start] * k + max_profit_wines_memoization(arr, cache_memoization, start+1, end, k+1);
    int pick_second = arr[end] * k + max_profit_wines_memoization(arr, cache_memoization, start, end-1, k+1);
    int result = max(pick_first, pick_second);
    cache_memoization[start][end] = result;
    return result;
}


int max_profit_wines_tabulation(int arr[], int size, int cache_tabulation[][100]) {
    // filling up the cache base cases.
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            /*
                The base cases are (0,0), (1,1), (2,2), (3,3).... and so on.
                Why? Because, This means start and end are at the same position.
                Means we can get the value directly from arr.
                arr[i] or arr[j] whatever both mean the same. Will give us the value
                for these base cases.

                In all of these cases, the rest of the wines have been sold.
                So, the multiplier is length of the array, i.e. the last year.
                arr[i] * size
            */
            cache_tabulation[i][j] = arr[i] * size;
            /*
                Now consider the case, start>end.
                This is beyond the base case. The base case is start == end.
                However in this case.
                start > end which means it has passed the base case.
                The last wine has been sold.
                You get zero profit.
                So we need to fill all cases where start>end to 0.
            */
            if(i>j) {
                cache_tabulation[i][j] = 0;
            }
        }
    }
    /*
        Say you have 0,1. This means that there are two wines.
        Whichever one you sell will have a multiplier of k-1.

        In case of, 0,2. There are 3 wines. Whichever wine you pick will have a multiplier of k-2.

        ....

        So the cost would be max of : arr[p] * (k - abs(p-q)) + cache_tabulation[p+1][q]
                                        arr[q] * (k-abs(p-q)) + cache_tabulation[p][q-1]
        
        In this case, k is the size of the wines array.

        Consider,
        0, 1 -> arr[0] * (size - 1) + cache[1][1]
                -> arr[1] * (size - 1) + cache[0][0]
        
        0, 2 -> arr[0] * (size - 2) + cache[1][2] -> gives -1 (We dont have this)
                -> arr[2] * (size - 2) + cache[0][1] -> we already have this.
        
        0, 3 -> arr[0] * (size - 3) + cache[1][3] -> gives -1 (We dont have this)
                arr[3] * (size - 3) + cache[0][2] -> we already have this.
        1, 1 -> base case continue
        1, 2 -> arr[1] * (size - 1) + cache[2][2] -> We have this
                -> arr[2] * (size - 1) + cache[1][1] -> We have this.
        
        Since, there are numbers that we do not know, we need to traverse diagonally
        rather than, (0,1) -> (0,2) -> (0,3) ->(1, 1) -> (1, 2) and so on.

        So we rather traverse diagonally.
        (0,1) (1,2) (2, 3) [(3, 4)this will not happen]
        (0,2) (1,3) [(2, 4)this will not happen]
        (0,3) [(1, 4)this will not happen]

        so our path will be: 
        year 0 is already cached by the base case.
        (0, 1) (1, 2) (2, 3) -> year 1
        (0, 2) (1, 3) -> year 2
        (0, 3) -> year 3
        
    */
    // now fill the rest of it diagonally.
    for(int year=1; year<size; year++) {
        for(int p=0; p<size; p++) {
            int q=p+year;
            if(q > size-1) {
                break;
            }  
            cache_tabulation[p][q] = max(
                arr[p] * (size - (q - p)) + cache_tabulation[p+1][q],
                arr[q] * (size - (q - p)) + cache_tabulation[p][q-1]
            );
        }
    }
    // The max value in the cache is the answer for our question.
    // You thought of the result part yourself Namah. Be proud. You did what Narang skipped in his tutorial.
    // Congratulations on your first achievement.
    /*
        Heres what you figured out on your own:
        1. The diagonals are base cases and are the actual array elements.
            Multiplied by the year (This was from video)
        2. All cases where i>j is 0 (This was from video)
        3. We need to traverse diagonally rather than iteratively.
        4. The result is the max of the cached values.
    */
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


int main() {
    int cache_memoization[100][100];
    int cache_tabulation[100][100];
    for(int j=0; j<100; j++) {
        for(int k=0; k<100; k++) {
            cache_memoization[j][k] = -1;
            cache_tabulation[j][k] = -1;
        }
    }
    int arr[] = {2, 4, 6, 2, 5};
    int len = sizeof(arr)/sizeof(int);
    int result = max_profit_wines_memoization(arr, cache_memoization, 0, len-1);
    int res = max_profit_wines_tabulation(arr, len, cache_tabulation);
    cout << result << "," << res;
}