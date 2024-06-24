
// TEXT struct
// text: is where we store a string. text points to a memory region. This memory
// region may be larger than the string we wish to store. In this case, the 
// string starts from where text is pointing to, and ends with '\0'.
// textSize: should keep track of strlen(text)
// mallocSize: is the size of memory region pointed by text.
//
// You can use mallocSize and textSize to determine whether you can add more 
// string to text. EX: If mallocSize = 50 and textSize = 25, we can safely add
// another string as long as 24 characters. The last 1 character is to store '\0'
//
// cursor: is a pointer to somewhere in text. We use cursor to traverse along
// the string.
typedef struct {
    char* text;
    int textSize;
    int mallocSize;
    char* cursor;
} TEXT;

// Required functions. These two functions must be implemented.
TEXT* ReadInput(int, char**);
char* GetNextWord(TEXT*);

// Recommended functions to implement.
void AppendCharacter(TEXT*, char);
void AppendWord(TEXT*, char*);

// These are helper functions I created to make the solution. They may be
// useful to organize your code
FILE* InputMode(int, char**);
void ToLowerCase(char*);
void ReallocTextIfSmall(TEXT*, int);
