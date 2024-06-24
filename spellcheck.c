#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"
#include "spellcheck.h"

// Given a string "word", it checks the spelling against the list of words in 
// "wordlist". If the "word" is found in "wordlist", the function returns the 
// "word". Otherwise, the function returns the first word in "wordlist" with
// the smallest edit distance.
// * No new memory is malloced.
// * The sturct WordList is defined in helper.h
char* CheckSpelling(char* word, WordList* wordlist) {
    int lowestDistance = 100;
    int lowestIndex = -1;
    for (int i = 0; i < wordlist->count; i++) {
        int distance = ComputeDistance(word, wordlist->words[i]);
        if (!distance) {
            return word;
        }
        if (distance < lowestDistance) {
            lowestDistance = distance;
            lowestIndex = i;
        }
    }
    
    
    return wordlist->words[lowestIndex];
}

// Compute Damerau-levenshtein distance between "myword" and "compword"
int ComputeDistance(char* myword, char* compword) {
    int mywordlen = strlen(myword);
    int compwordlen = strlen(compword);

    int** D = CreateMatrix(mywordlen + 1, compwordlen + 1);

    // Damerau-Levenshtein Algorithm
    for (int i = 0; i <= mywordlen; i++) D[i][0] = i;
    for (int j = 0; j <= compwordlen; j++) D[0][j] = j;

    for (int i = 1; i <= mywordlen; i++) {
        for (int j = 1; j <= compwordlen; j++) {
            int cost = 0;
            if (myword[i - 1] != compword[j-1] ) cost = 1;

            D[i][j] = D[i - 1][j - 1] + cost;
            int del = D[i - 1][j] + 1;
            if (del < D[i][j]) D[i][j] = del;
            int ins = D[i][j - 1] + 1;
            if (ins < D[i][j]) D[i][j] = ins;

            if (i > 1 && j > 1 && 
                myword[i - 1] == compword[j - 2] && 
                myword[i - 2] == compword[j - 1]) {
                    int trans = D[i - 2][j - 2] + 1;
                    if (trans < D[i][j]) D[i][j] = trans;
                }
        }
    }

    int distance = D[mywordlen][compwordlen];

    FreeMatrix(D, mywordlen + 1);
    return distance;
}