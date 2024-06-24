/******************************************************************************
    Helper functions provided for you. No need to write code in this file
    unless you want to add additional functions.
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"

// Create a 2D integer matrix with "row" rows and "col" columns using malloc
int** CreateMatrix(int row, int col) {
    int** matrix = malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) matrix[i] = malloc(sizeof(int) * col);
    return matrix;
}

// Free the 2D integer matrix created with malloc calls.
void FreeMatrix(int** matrix, int row) {
    for (int i = 0; i < row; i++) free(matrix[i]);
    free(matrix);
}

// Check whether the pointer returned from realloc or malloc is NULL or not.
// If null, then we exit the program.
void CheckAllocation(void* temp) {
    if (temp == NULL) {
        printf("Program ran out of memory\n");
        exit(0);
    }
}

// Constructs a WordList struct containing an array of words found in 30000.txt
// WordList is defined in helper.h
WordList* ConstructWordList() {

    FILE *readfile = fopen("30000.txt", "r");
    if (readfile == NULL){
        return NULL;
    }

    WordList* WordListStruct = malloc(sizeof(WordList));
    if(WordListStruct == NULL){
        fclose(readfile);
        return NULL;
    }

    WordListStruct-> words = malloc(sizeof(char*) * NUMWORDS);
    if (WordListStruct-> words == NULL){
        fclose(readfile);
        free(WordListStruct);
        return NULL;
    }

    char word[MAXLENGTH + 1];
    int wordsread = 0;
    for(int i = 0; i < NUMWORDS; i++){
        int read = fscanf(readfile, "%s", word);

        if (read != 1){
            break;
        }

        WordListStruct->words[i] = malloc(strlen(word) + 1);
        if(WordListStruct->words[i] == NULL){
            for (int j = 0; j < i; j++) {
                free(WordListStruct->words[j]);
            }
        free(WordListStruct->words);
        free(WordListStruct);
        fclose(readfile);
        return NULL;
        }

        strcpy(WordListStruct->words[i], word);

        wordsread++;
    }

    for (int i = wordsread; i < NUMWORDS; i++){
        WordListStruct->words[i] = NULL;
    }
    WordListStruct->count = wordsread; 

     fclose(readfile);
     return WordListStruct;

}

// Add "word" to our array of words (wordlist). Note that we make a copy of word
// and store the copy into wordlist.
void AddToWordList(WordList* wordlist, char* word) {
    
    if (wordlist == NULL || word == NULL || wordlist->count >= NUMWORDS){
        return;
    }

    char* newword = malloc(strlen(word) + 1);

    if (newword == NULL){
        return;
    }
    strcpy(newword, word);
    wordlist->words[wordlist->count] = newword;
    wordlist->count++;

}

// Frees the WordList struct allocated in the heap.
void FreeWordList(WordList* wordlist) {
        if(wordlist == NULL){
        return;
    }

    for (int i = 0; i < wordlist->count; i++) {
        if (wordlist->words[i] != NULL) {
            free(wordlist->words[i]);
        }
    }
    
    free(wordlist->words);
    free(wordlist);
}
