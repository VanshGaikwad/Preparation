/*
============================================================
Problem: 2009. Minimum Number of Operations to Make Array Continuous
============================================================

You are given an integer array nums.

In one operation, you can replace any element in nums with
any integer.

An array is continuous if:
    1. All elements are unique.
    2. The difference between the maximum and minimum
       element is exactly nums.length - 1.

Return the minimum number of operations needed to make nums
continuous.

------------------------------------------------------------
Example 1:
------------------------------------------------------------

Input:
nums = [4,2,5,3]

Output:
0

Explanation:
The array can be rearranged as [2,3,4,5], which is already
continuous. Therefore, 0 operations are required.

------------------------------------------------------------
Example 2:
------------------------------------------------------------

Input:
nums = [1,2,3,5,6]

Output:
1

Explanation:
We can replace 6 with 4.

Array becomes:
[1,2,3,5,4]

Now it contains:
1,2,3,4,5

So only 1 operation is required.

------------------------------------------------------------
Example 3:
------------------------------------------------------------

Input:
nums = [1,10,100,1000]

Output:
3

------------------------------------------------------------
Constraints:
------------------------------------------------------------

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9


============================================================
APPROACH
============================================================

Idea:

We first sort/remove duplicates because we only care about
which unique numbers can already be kept.

Suppose:

    n = nums.size()

If we choose some number nums[i] as the minimum element L,
then a continuous array of size n must contain numbers in:

    [L, L + n - 1]

So:

    L = temp[i]
    R = L + n - 1

Now we need to find how many unique elements already lie
inside this range.

For that, we use:

    upper_bound(temp.begin(), temp.end(), R)

upper_bound gives the first element that is strictly greater
than R.

If its index is j, then all elements from index i to j-1
are inside the range.

Therefore:

    inrange = j - i

The remaining elements are outside the range:

    outrange = n - inrange

These outside elements need to be replaced.

We try every possible starting point i and take the minimum:

    res = min(res, outrange)

------------------------------------------------------------
Why remove duplicates?
------------------------------------------------------------

A continuous array must contain unique elements.

So we first use a set:

    set<int> st(begin(nums), end(nums));

Then convert it into a vector:

    vector<int> temp(begin(st), end(st));

This gives us sorted unique elements.

------------------------------------------------------------
Time Complexity:
------------------------------------------------------------

Creating the set:
    O(n log n)

For every element, upper_bound:
    O(log n)

Total:
    O(n log n)

Space:
    O(n)

============================================================
*/

class Solution {
public:
    int minOperations(vector<int>& nums) {
        // sort the array
        // then calculate range for i (L, R)
        // upper_bound for R gives the first element
        // just greater than R (j)
        // in range = j - i
        // out range = n - inrange
        // find minimum out range


        // sort + remove duplicate
        set<int> st(begin(nums), end(nums));
        vector<int> temp(begin(st), end(st));

        int res = INT_MAX;
        int n = nums.size();

        for(int i = 0; i < temp.size(); i++){

            int L = temp[i];
            int R = L + n - 1;

            // upper_bound gives pointer to the first
            // element greater than R
            // subtract begin() to get its index
            int j = upper_bound(begin(temp), end(temp), R)
                    - begin(temp);

            // Number of unique elements inside [L, R]
            int inrange = j - i;

            // Remaining elements need to be replaced
            int outrange = n - inrange;

            // Take minimum operations
            res = min(outrange, res);
        }

        return res;
    }
};