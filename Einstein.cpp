#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

static const char kColor[][10] = {"Red", "Green", "White", "Blue", "Yellow"};
static const char kCountry[][10] = {"British", "Swedish", "Danish", "Norwegian", "German"};
static const char kAnimal[][10] = {"Dog", "Bird", "Cat", "Horse", "Fish"};
static const char kDrink[][10] = {"Coffee", "Tea", "Milk", "Beer", "Water"};
static const char kCigar[][20] = {"Pall Mall", "Dunhill", "Blend", "Blue Master", "Prince"};

// Map relation:
// Red 1, Green 2, White 3, Blue 4, Yellow 5
// same as country: British 1, Swedish 2, Danish 3, ....
// same as animal, drink, cigar

// constraint translate:
// 1. vec[0].find(1) == vec[1].find(1), vec[0] store color, vec[1] store country, and they all in same index
// 2. vec[1].find(2) == vec[2].find(1)
// 3. vec[1].find(3) == vec[3].find(2)
// 4. vec[0].find(2) + 1 == vec[0].find(3)
// 5. vec[0].find(2) == vec[3].find(1)
// 6. vec[2].find(2) == vec[4].find(1)
// 7. vec[0].find(5) == vec[4].find(2)
// 8. vec[3].find(3) == 2
// 9. vec[1].find(4) == 0
// 10. vec[2].find(3) - vec[4].find(3) == 1 OR -1
// 11. vec[2].find(4) - vec[4].find(2) == 1 OR -1
// 12. vec[3].find(4) == vec[4].find(4)
// 13. vec[1].find(4) == vec[4].find(5)
// 14. vec[0].find(4) - vec[1].find(4) = 1 OR -1
// 15. vec[3].find(5) - vec[4].find(3) = 1 OR -1

// algorithm:
// five elements are represent as a vector<vector<int>> vec(5, {1,2,3,4,5})
// we exchange order of each row from 1,2,3,4,5 to 5,4,3,2,1
// if it fullfill all constraint then pass and print
// else try next order.

size_t getIndex(const vector<int>& vec, int num) {
    return find(vec.begin(), vec.end(), num) - vec.begin();
}

bool validColor(const vector<vector<int>>& vec) {
    auto green_index = getIndex(vec[0], 2);
    auto white_index = getIndex(vec[0], 3);
    return white_index - green_index == 1; // constraint 4
}

bool validCountry(const vector<vector<int>>& vec) {
    auto red_index = getIndex(vec[0], 1);
    auto british_index = getIndex(vec[1], 1);
    if (red_index != british_index) return false;   // constraint 1

    auto norw_index = getIndex(vec[1], 4);
    if (norw_index != 0) return false;  // constraint 9

    auto blue_index = getIndex(vec[0], 4);
    auto diff = blue_index - norw_index;
    return (diff == -1) || (diff == 1); // constraint 14
}

bool validAnimal(const vector<vector<int>>& vec) {
    auto swe_index = getIndex(vec[1], 2);
    auto dog_index = getIndex(vec[2], 1);
    return swe_index == dog_index;  // constraint 2
}

bool validDrink(const vector<vector<int>>& vec) {
    auto danish_index = getIndex(vec[1], 3);
    auto tea_index = getIndex(vec[3], 2);
    if (danish_index != tea_index) return false; // constraint 3

    auto green_index = getIndex(vec[0], 2);
    auto coffee_index = getIndex(vec[3], 1);
    if (green_index != coffee_index) return false; // constraint 5

    auto milk_index = getIndex(vec[3], 3);
    if (milk_index != 2) return false; // constraint 8

    return true;
}

bool validCigar(const vector<vector<int>>& vec) {
    auto bird_index = getIndex(vec[2], 2);
    auto pall_mall_index = getIndex(vec[4], 1);
    if (bird_index != pall_mall_index) return false;  // constraint 6

    auto yellow_index = getIndex(vec[0], 5);
    auto dunhill_index = getIndex(vec[4], 2);
    if (dunhill_index != yellow_index) return false; // constraint 7

    auto cat_index = getIndex(vec[2], 3);
    auto blend_index = getIndex(vec[4], 3);
    auto diff = cat_index - blend_index;
    if (!((diff == -1) || (diff == 1))) return false; // constraint 10

    auto horse_index = getIndex(vec[2], 4);
    diff = horse_index - dunhill_index;
    if (!((diff == -1) || (diff == 1))) return false; // constraint 11

    auto beer_index = getIndex(vec[3], 4);
    auto blue_master_index = getIndex(vec[4], 4);
    if (beer_index != blue_master_index) return false; // constraint 12

    auto german_index = getIndex(vec[1], 5);
    auto prince_index = getIndex(vec[4], 5);
    if (prince_index != german_index) return false; // constraint 13

    auto water_index = getIndex(vec[3], 5);
    diff = water_index - blend_index;
    return (diff == 1) || (diff == -1); // constraint 15
}

bool valid(const vector<vector<int>>& vec, int row) {
    switch (row) {
    case 0: return validColor(vec);
    case 1: return validCountry(vec);
    case 2: return validAnimal(vec);
    case 3: return validDrink(vec);
    case 4: return validCigar(vec);
    default: return false;
    }
}

void printResult(const vector<vector<int>>& vec) {
    size_t index = getIndex(vec[2], 5);
    cout << "Who keep fish? " << kCountry[(vec[1][index] - 1)] << endl;
}

void printAll(const vector<vector<int>>& vec) {
    printf("| ");
    for (auto it = vec[0].begin(); it != vec[0].end(); ++it) {
        printf("%-12s | ", kColor[*it - 1]);
    }
    printf("\n");

    printf("| ");
    for (auto it = vec[1].begin(); it != vec[1].end(); ++it) {
        printf("%-12s | ", kCountry[*it - 1]);
    }
    printf("\n");

    printf("| ");
    for (auto it = vec[2].begin(); it != vec[2].end(); ++it) {
        printf("%-12s | ", kAnimal[*it - 1]);
    }
    printf("\n");

    printf("| ");
    for (auto it = vec[3].begin(); it != vec[3].end(); ++it) {
        printf("%-12s | ", kDrink[*it - 1]);
    }
    printf("\n");

    printf("| ");
    for (auto it = vec[4].begin(); it != vec[4].end(); ++it) {
        printf("%-12s | ", kCigar[*it - 1]);
    }
    printf("\n");
}

void solve(vector<vector<int>>& vec, int row) {
    if (row == vec.size()) {
        printAll(vec);
        printResult(vec);
        return;
    }

    do {
        if (!valid(vec, row)) continue;
        solve(vec, row+1);
    } while (next_permutation(vec[row].begin(), vec[row].end()));
}

int main() {
    vector<int> vv = {1,2,3,4,5};
    vector<vector<int>> vec(5, vv);
    solve(vec, 0);
    return 0;
}
