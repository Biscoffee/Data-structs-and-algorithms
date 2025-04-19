    unordered_set<int> seen;
    int n = nums.size();
    int left = 0, right = 0;
    int maxScore = 0, currentSum = 0;

    while (right < n) {
        while (seen.count(nums[right])) {
            seen.erase(nums[left]);
            currentSum -= nums[left];
            left++;
        }
        seen.insert(nums[right]);
        currentSum += nums[right];
        maxScore = max(maxScore, currentSum);
        right++;
    }

    return maxScore;