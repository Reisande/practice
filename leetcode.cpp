

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> returnVec;
		for(int i = 0; i < nums.length() - 1; i++) {
			for(int j = 1; j < nums.length(); j++) {
				if(nums[i] + nums[j] == target) {
				  returnVec.push_back(i);
					returnVec.push_back(j);

					break;
				}
			}
		}

		return returnVec;
	}
};
