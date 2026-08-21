#include <iostream>
#include <vector>
using namespace std;

/*
===========================================================
                    PROBLEM STATEMENT
===========================================================

You are given a sorted array of integers where every element
appears exactly twice, except for one element which appears
exactly once.

Find and return the element that appears only once.

Your solution must run in O(log n) time and use O(1)
extra space.

-----------------------------------------------------------
Example:

Input:
nums = [1,1,2,3,3,4,4,8,8]

Output:
2

Explanation:
Every element appears twice except 2, which appears once.

-----------------------------------------------------------
CONSTRAINTS:

- 1 <= nums.length <= 10^5
- nums.length is odd
- nums is sorted in non-decreasing order
- Every element appears exactly twice except one element
- The single element appears exactly once

-----------------------------------------------------------
IMPORTANT:

You should solve this using Binary Search.

DO NOT use:
- Hash Map
- Frequency Array
- Sorting again
- Linear scan

Expected:
Time  -> O(log n)
Space -> O(1)

===========================================================
                     TEST CASES
===========================================================

Test Case 1:

Input:
9
1 1 2 3 3 4 4 8 8

Expected Output:
2


Test Case 2:

Input:
7
3 3 7 7 10 11 11

Expected Output:
10


Test Case 3:

Input:
5
1 1 2 2 3

Expected Output:
3


Test Case 4:

Input:
3
1 2 2

Expected Output:
1


Test Case 5:

Input:
7
1 1 2 2 3 3 4

Expected Output:
4


===========================================================
                  YOUR APPROACH
===========================================================

Hint:

Before the single element, pairs follow this pattern:

index:  0 1 2 3 4 5
        ─────────────
array:  1 1 2 2 3 3

So:

even index -> first element of pair
odd index  -> second element of pair

After the single element, this pattern gets disturbed.

Use Binary Search to find where this pattern breaks.

===========================================================
*/


class Solution {
public:

    int singleNonDuplicate(vector<int>& nums) {

        // Write your solution here
        int n = nums.size();
        int left = 1;
        int right = n -2;

        if(nums[0] != nums[1]) return nums[0];
        if(nums[n-1] != nums[n-2]) return nums[n-1];

        while(left <= right){
            int mid = left +(right - left)  /2;
            if(nums[mid] != nums[mid +1] && nums[mid] != nums[mid -1]) return nums[mid];
            
            if((mid % 2 == 0 &&  nums[mid ] == nums[mid +1]) ||  (mid % 2 == 1 && nums[mid] == nums[mid-1])){
                left = mid+1;
            }
            else{
                right = mid -1;
            }
        }
        return -1;



    }
};


int main() {

    /*
    ========================================================
                     MULTIPLE TEST CASES
    ========================================================

    Input format:

    T
    n
    array elements

    Example:

    5

    9
    1 1 2 3 3 4 4 8 8

    7
    3 3 7 7 10 11 11

    ...
    ========================================================
    */

    int T;
    cin >> T;

    while (T--) {

        int n;
        cin >> n;

        vector<int> nums(n);

        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }

        Solution sol;

        cout << sol.singleNonDuplicate(nums) << endl;
    }

    return 0;
}


/*
===========================================================
                     SAMPLE INPUT
===========================================================

5

9
1 1 2 3 3 4 4 8 8

7
3 3 7 7 10 11 11

5
1 1 2 2 3

3
1 2 2

7
1 1 2 2 3 3 4


===========================================================
                    EXPECTED OUTPUT
===========================================================

2
10
3
1
4

===========================================================
*/