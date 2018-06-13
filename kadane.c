#include <stdio.h>

int maxSubArray(int* nums, int numsSize) {

    if(numsSize==0)
        return 0;
    
    int arr[numsSize],max; // a[i] represents the max sum of sub-array ending at i
    arr[0] = nums[0];

    for(int i=1;i<numsSize;i++)
        arr[i] = arr[i-1]+nums[i]>nums[i]?arr[i-1]+nums[i]:nums[i];
    
    
    max=arr[0];
    for(int i=1;i<numsSize;i++)
        max=max>arr[i]?max:arr[i];
    
    return max;
}

int main() {
    
}