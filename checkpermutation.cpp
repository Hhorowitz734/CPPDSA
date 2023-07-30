#include <stdio.h>
#include <iostream>
#include <algorithm>

bool checkPermuation(std::string& stringA, std::string& stringB){

    if (stringA.length() != stringB.length()){ //Two strings of unequal length cannot be permutations of each other
        return false;
    }

    int stringLength = stringA.length();
    int charsA[stringLength];
    int charsB[stringLength];

    std::fill(charsA, charsA + stringLength, 0); //Fills the arrays with 0, as no characters are there yet
    std::fill(charsB, charsB + stringLength, 0);

    for (int i = 0; i < stringLength; i++){ //Creates two arrays with counts of letters in a string
        int charAValue = static_cast<int>(stringA[i]);
        int charBValue = static_cast<int>(stringB[i]);

        charsA[charAValue]++;
        charsB[charBValue]++;
    }

    for (int i = 0; i < stringLength; i++){ //Compares the two arrays
        if (charsA[i] != charsB[i]){
            return false;
        }
    }

    return true;
}

int main(){

    std::string testStringA = "Hello";
    std::string testStringB = "elloHa";

    if (checkPermuation(testStringA, testStringB)){
        printf("The strings are permutations.");
    } else {
        printf("The strings are not permutations.");
    }

    return 0;
}