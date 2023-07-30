#include <stdio.h>
#include <iostream>
#include <exception>
#include <map>

//This implementation uses a map to keep track of character count
bool isUniqueWithMap(const std::string& str){

    std::map<char, int> charmap;

    for (char letter: str){

        charmap[letter]++; //Adds one to the specific letter

        if (charmap[letter] > 1){
            return false; //Returns false if letter appears more than once
        } 

    }

    return true;
}

//This implementation allows for data structures but not map
bool isUniqueWithoutMap(const std::string& str){

    if (str.length() > 128) { //A string cannot have no repeating characters with a length of >128
        return false;
    }

    bool letterUsed[128] = {false};

    for (char letter: str){
        int charValue = static_cast<int>(letter);
        
        if (letterUsed[charValue]){
            return false;
        } else {
            letterUsed[charValue] = true;
        }
    }

    return true;
}

int main() {

    std::string testString = "Hello";

    if (isUniqueWithoutMap(testString)){
        printf("No repeating characters");
    } else {
        printf("Repeating characters.");
    }
    
}