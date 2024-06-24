#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "helper.h"
#include "main.h"
#include "spellcheck.h"

void PrintContext(TEXT* inputText, char* word);

int main(int argc, char** argv) {
    if (argc > 2) {
        printf("Usage %s [document file]\n", argv[0]);
        exit(0);
    }
    // Read the words in 30000.txt and store into WordList struct
    WordList* wordlist = ConstructWordList();

    // Read input text from a file or from stdin
        // Turn all letters in the input text to lower case
    TEXT* inputText = ReadInput(argc, argv);
    ToLowerCase(inputText->text);


    // Create another TEXT struct to store the final text
    TEXT* finalText = malloc(sizeof(TEXT));
    finalText-> text = malloc(sizeof(char) * inputText->mallocSize);
    finalText-> textSize = 0;
    finalText-> mallocSize = inputText-> mallocSize;
    finalText-> cursor = inputText-> text;

    char* word;
    while((word = GetNextWord(inputText)) != NULL){


        if (isalpha(word[0])){
            char* correctWord = CheckSpelling(word, wordlist);

            int correctwordLength = strlen(correctWord);
            int requiredSize = finalText->textSize + correctwordLength + 1;

            if(requiredSize >= finalText->mallocSize){
                finalText->mallocSize *=2;

                finalText->text = realloc(finalText->text, finalText->mallocSize * sizeof(char));

                if (finalText->text == NULL) {
                printf("Memory reallocation has failed\n");
                exit(0);
                }
            }

            if (strcmp(word, correctWord) == 0){
                AppendWord(finalText, word);
            }
            else{
                PrintContext(inputText, word);
                printf("Suggestion: %s -> %s\n", word, correctWord);
                printf("[r]eplace, [a]dd to the dictionary, [i]gnore(default)");

                char option;
                scanf(" %c", &option);

                switch(option){
                    case 'r':
                    AppendWord(finalText, correctWord);
                    break;
                    case 'a':
                    AddToWordList(wordlist, word);
                    AppendWord(finalText, correctWord);
                    break;
                    case 'i':
                    AppendWord(finalText, correctWord);
                    break;

                }

            }

            // free(correctWord);
        }
        else{
        AppendWord(finalText, word);
        }

        free(word);
    }

    printf("%s\n", finalText->text);

    free(finalText->text);
    free(finalText);
    free(inputText->text);
    free(inputText);
    FreeWordList(wordlist);

    // Traverse the input text.
    // If you encounter non-letter character, append to the final text.
    // If you encounter a word, then:
    //  Check if the word is spelled correctly
    //      If spelled correct, then append to the final text.
    //      Otherwise, ask if the user would like to:
    //          (1) Replace the word with the suggested word
    //          (2) Add the word to the dictionary
    //          (3) Ignore spell check and continue
    //          Either way, the original word or the suggested word must be
    //          appended to the final text.
    // Once spell check is complete,
    //    print the final text
    //    free all memory that is malloced (whether created by malloc or realloc)

    return 0;
}

/**************************************
    Functions requried to implement
**************************************/

// ReadInput reads the input text provided by the user
// (1) If the user provides a file through command line argument, read the
//     content of the file until EOF
// (2) If the user does not provide a file, read from stdin until either
//     the user types "QUIT", or EOF. When the user intends to stop writing
//     text, the user will type "QUIT" in a new line with nothing else in it.
// The user may input arbitrarily long sentences and text. Make sure you can
// read the whole text provided the user.
// Return the original text in the TEXT struct. Make sure to set all fields
// correctly.
TEXT* ReadInput(int argc, char** argv) {

    TEXT* inputText = malloc(sizeof(TEXT));
    inputText -> text = malloc (sizeof(char) * 1024);
    inputText -> textSize = 0;
    inputText -> mallocSize = 1024;
    inputText -> cursor = inputText -> text;

    if (argc == 2){
        FILE* file = fopen(argv[1], "r");
        if (file == NULL){
            printf("Error: couldn't open the file\n");
            exit (0);
        }
        
        char buffer[1024];

        while (fgets(buffer, 1024, file) != NULL){

            if (strcmp(buffer, "QUIT\n") == 0) {
                break;
            }

            if (inputText -> textSize + strlen(buffer) >= inputText -> mallocSize){
                inputText -> mallocSize = inputText -> mallocSize * 2;
                inputText -> text = realloc(inputText -> text, inputText -> mallocSize);

                if (inputText -> text == NULL){
                    printf("Memory reallocation has failed\n");
                    exit (0);

                }
            }

            strcat(inputText -> text + inputText->textSize, buffer);

            inputText-> textSize = inputText -> textSize + strlen(buffer);
        }
        fclose(file);

    }
    else {

        char buffer[1024];

        while (fgets(buffer, 1024, stdin) != NULL){
            if (strcmp(buffer, "QUIT\n") == 0){
                break;
            }

            if (inputText -> textSize + strlen(buffer) >= inputText -> mallocSize){
                inputText -> mallocSize = inputText -> mallocSize * 2;
                inputText -> text = realloc(inputText -> text, inputText -> mallocSize);

                if (inputText -> text == NULL){
                    printf("Memory reallocation has failed\n");
                    exit(0);

                }
            }

            strcat(inputText -> text + inputText->textSize, buffer);
            inputText -> textSize = inputText -> textSize + strlen(buffer);
        }

    }



    return inputText;
}

// Starting from content->cursor, retrieve the next word in content->text
// A word is defined as a consecutive sequence of lower case and upper case
// alphabet, numbers, and apostrophe ('\'')
//
// Helpful hints:
// After identifying a word in content->text, malloc a new memory region, copy
// the word to the new memory region, and return the malloced memory.
// It is probably best to assume content->cursor is pointing to the beginning
// of a word when implementing GetNextWord. And make sure that content->cursor 
// does indeed point to the beginning of a word before calling GetNextWord.

char* GetNextWord(TEXT* content) {

    char* currentPosition = content->cursor;

    while (*currentPosition != '\0' && !isalnum(*currentPosition) && *currentPosition != '\'') {
        currentPosition++;
        content->cursor++;

    }

    if (*currentPosition == '\0') {
        return NULL;
    }

    char* wordstart= currentPosition;

    while (*currentPosition != '\0' && (isalnum(*currentPosition) || *currentPosition == '\'')) {
        currentPosition++;
    }
    int wordLength = currentPosition - wordstart;

    char* word = malloc((wordLength + 1) * sizeof(char));
    if (word == NULL) {
        printf("Memory allocation failed\n");
        exit(0);
    }

    strncpy(word, wordstart, wordLength);
    word[wordLength] = '\0';

    content->cursor = currentPosition;

    return word;
}

/******************************************
    Functions recommended to implement
******************************************/

// Given a string "word", append "word" to the end of the text. Make sure to
// update all fields in "to" correctly.
void AppendWord(TEXT* to, char* word) {
    int wordLength = strlen(word);
    if(to->textSize + wordLength + 1 >= to->mallocSize){
        to->mallocSize = to->mallocSize * 2;
        to->text = realloc(to->text, to->mallocSize * sizeof(char));
        if (to->text == NULL){
            printf("Memory reallocation failed\n");
            exit(0);
        }
    }
    strcpy(to->text + to->textSize, word); 
    to->textSize += wordLength;

    to->text[to->textSize] = ' '; 
    to->textSize++; 

    to->text[to->textSize] = '\0';
}


// Given a character 'c', append 'c' to the end of the text. Make sure to
// update all fields in "to" correctly.
void AppendCharacter(TEXT* to, char c) {

    if(to->textSize + 1 >= to->mallocSize){

        to->mallocSize = to->mallocSize * 2;

        to->text = realloc(to->text, to->mallocSize * sizeof(char));

        if (to->text == NULL){
            printf("Memory reallocation failed\n");
            exit(0);
        }
    }

    to->text[to->textSize] = c;
    to->textSize++;
    to->text[to->textSize] = '\0';


}


/**********************************************
    Helper functions I thought were useful
***********************************************/

// Turn all letters in "text" string into lower case letters.
void ToLowerCase(char* text) {

    for (int i = 0; text[i] != '\0'; i++){

        if (text[i] >= 'A' && text[i] <= 'Z'){
            text[i] = text[i] + ('a'-'A');
        }
    }
    
}

// This function checks whether the text is large enough to append a string
// that is "insertSize" characters long to the end of the text string.
// If the text area is not large enough to append "isnertSize" number of 
// characters, we realloc the text region and increase the size.
// 
// More specifically,
// to->mallocSize specifies how large the string stored in to->text can be.
// to->textSize specifies the actual size of the string stored in to->text.
// Let's say we want to append a string to the end of the string stored in 
// to->text. Also suppose that the length of the string we wish to append is
// "insertSize" number of bytes.
//
// Using these values, we can check whether to->text is large enough to append
// the new string to the end of the string stored in to->text. If it is not
// large enough, then we realloc to->text to make it large enough.
//
// Hint: When you realloc, you usually want to make it large enough that there
// is room to append additional strings later. Common approach is to double
// the size of to->text. Though make sure that the double-sized memory is 
// sufficiently large enough to append the new string
void ReallocTextIfSmall(TEXT* to, int insertSize) {

    int sizeRequired = to->textSize + insertSize + 1;

    if(sizeRequired > to->mallocSize){
        int newsize = to->mallocSize * 2;
        while (sizeRequired > newsize){
            newsize *= 2;
        }

        to->text = realloc(to->text, newsize * sizeof(char));
        if (to->text == NULL){
            printf("Memory reallocation failed\n");
            exit(0);
        }

        to->mallocSize = newsize;
    }

}

void PrintContext(TEXT* inputText, char* word){
    char* start = inputText->cursor;
    char* end = inputText->cursor;
    int backcount = 0;
    int fowardcount = 0;

    while (start >= inputText->text && backcount < 20) {

        start--;
        backcount++;

        if (*start == ' ' || *start == '\n' || start == inputText->text){
             break;
        }
    }

    while (*end != '\0' && fowardcount < 20){
        end++;
        fowardcount++;
        if (*end == ' ' && *end == '\n' || *end == '\0'){
            break;
        }
    }

    printf("...%.*s %s%.*s...\n", backcount, start - backcount, word, fowardcount, start + strlen(word) + 1);
}
