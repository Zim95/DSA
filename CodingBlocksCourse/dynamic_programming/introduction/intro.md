## DYNAMIC PROGRAMMING
The one who doesn't learn from the past is condemned to repeat it.

Counting Problem:
=================
1. Take a problem to count numbers:
    1 + 1 + 1 + 1 + 1 = 5
    1 + 1 + 1 + 1 + 1 + 1 + 1 = 7
    Because we know, 1 + 1 + 1 + 1 + 1 is 5, and 5 + 1 + 1 is 7.

2. If we didnt know, that 1 + 1 + 1 + 1 + 1 is 5, we would again have
    to go through the series of 1s and add them.

3. This is Dynamic Programming, remembering past calculations.

Where do we use DP?
===================
1. Optimal Substructure.
2. Overlapping Subproblems.

1. Optimal Substructure:
------------------------
- In case of optimal substructure:
    You need to get min/max values.
    In this case, you need to identify what is it being reduced or increased by.
    - Sometimes it'll be given that you can either divide by 3 or by 2 or by 1, (Choose the best approach).
    - Sometimes an array of reducers might be given. Like, Subtract one of the following numbers [1, 7, 10, 8] from N. Find the quickest way to get to 1.