#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

/*int sockMerchant(int n, std::vector<int> arr) {
    std::unordered_map<int, int> *pairs = new std::unordered_map<int, int>();

    for(int i = 0; i < n; i++) {
        auto sock = pairs->find(arr[i]);
        if(sock == pairs->end()) {
            pairs->insert({arr[i], 1});
        }
        else {
            sock->second++;
        }
    }

    int pairs_counter = 0;
    for(auto iter = pairs->begin(); iter != pairs->end(); iter++) {
        pairs_counter += (iter->second / 2);
    }

    return pairs_counter;
}

int countingValleys(int n, std::string s) {
    int above = 0, below = 0, height = 0;

    for(int i = 0; i < n; i++) {
        int startingHeight = height;
        char step = s[i];
        if(step == 'U') {
            height++;
        }
        else {
            height--;
        }

        if(startingHeight == -1 && height == 0) {
            above++;
        }
        else if(startingHeight == 0 && height == -1) {
            below++;
        }
    }

    return std::min(above, below);
}*/

int jumpingOnClouds(std::vector<int> c) {
    std::vector<int> path;
    int current_position = 0;
    for(int i = 0; i < c.size(); i++) {
        path.push_back(current_position);
        if(c[current_position + 1] == 1) {
            current_position += 2;
        }
        else {
            current_position++;
        }
    }

    int min_length = 2;
    for(int i = 0; i < path.size() - 2; i++) {
        if(path.at(i) + 1 == path.at(i + 1) && path.at(i) + 2 == path.at(i + 2)) {
            min_length--;
        }
    }

    return min_length;
}

int main(int argc, char **argv) {
}
