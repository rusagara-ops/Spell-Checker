/******************************************************************************
    Helper functions provided for you. No need to write code in this file
    unless you want to add additional functions.
******************************************************************************/

// Number of words in the dictionary
#define NUMWORDS 30000
// Longest word in the dictionary
#define LONGESTWORD "helpsearchmemberscalendar"
// Length of the longest word in the dictionary
#define MAXLENGTH 26

// WordList is a struct containing an array of strings (words) and the number
// of strings in words. We keep track of count since we can now insert into
// words.
typedef struct {
    char** words;
    int count;
} WordList;

int** CreateMatrix(int, int);
void FreeMatrix(int**, int);
void CheckAllocation(void*);

WordList* ConstructWordList();
void AddToWordList(WordList* wordlist, char* word);
void FreeWordList(WordList*);