#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "PowerStats.h"

using namespace std;

int kadane(vector<int> &nums) {
    if (nums.size() == 0) return 0;

    int max;
    vector<int> &arr = *(new vector<int>);

    for (int i = 0; i < nums.size(); i++) arr.push_back(0);    

    arr[0] = nums[0];
    for (int i = 1; i < nums.size(); i++)
        arr[i] = arr[i - 1] + nums[i] > nums[i] ? arr[i - 1] + nums[i]: nums[i];
    
    max = arr[0];
    for (int i = 1; i < nums.size(); i++) max = max > arr[i] ? max: arr[i];

    delete &arr;
    return max;
}

int brute(vector<int> &nums) {
    int n = nums.size();
    int ma = INT_MIN;
    
    for(int i = 0; i < n; i++) {
        int s = 0;
        
        for(int j = i ; j < n; j++) {
            s += nums[j];
            ma = max(ma, s);
        }    
    }
    
    return ma;
}

vector<int> *generateArray(int n) {
    vector<int> *vec = new vector<int>;

    for (int i = 0; i < n; i++) {
        vec->push_back(rand() % 20000 - 10000);
    }

    return vec;
}

int main() {
    srand(time(0));
    PowerStats *powerstats = new PowerStats();
    powerstats->Start();
    vector<int> *vec = generateArray(500000);
    cout << brute(*vec) << endl;
    cout << powerstats->Measure() << endl;
    cout << kadane(*vec) << endl;
    cout << powerstats->Measure() << endl;
}