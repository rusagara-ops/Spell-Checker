# Spell-Checker
Advanced Interactive Spell Checker

## Introduction
The Advanced Interactive Spell Checker is a sophisticated tool designed to analyze and correct spelling in real-time. It provides a user-friendly interface for direct text input or file-based input, offering corrective suggestions for each potentially misspelled word.

## Features
- **Interactive Spelling Suggestions:** Upon detecting a misspelling, users are prompted with suggestions and can choose to:
  - Replace the misspelled word.
  - Add the word to the dictionary.
  - Ignore the suggestion.
- **Flexible Input Options:** Input text can be provided through standard input or by specifying a file path.
- **Dynamic Dictionary Management:** The dictionary can be updated dynamically, allowing newly added words to be recognized instantly in subsequent checks.

## Dictionary and Functionality
- **Initial Dictionary Setup:** The dictionary starts with a comprehensive list of over 30,000 words, ensuring wide coverage of common and some uncommon terms.
- **Dynamic Updates:** Users have the ability to add new words to the dictionary during spell check sessions, which enhances the adaptability of the spell checker to new words and terminologies.
- **Spell Checking Mechanism:** Each word input by the user is checked against the dictionary. Words not found are flagged as potential misspellings, with suggestions based on closest matches computed using the Damerau-Levenshtein distance algorithm.

### Handling Misspellings
When a word is identified as potentially misspelled:
1. **Context and Suggestion:** The user is shown the misspelled word within its context and a suggested correction based on the closest dictionary match.
2. **User Options:** The user can then choose to:
   - `[r]eplace` the misspelled word with the suggested correction.
   - `[a]dd` the word to the dictionary if it is correct but not presently recognized.
   - `[i]gnore` the suggestion, leaving the text as is.
3. **Action Execution:** Depending on the user's choice:
   - **Replace:** The word is corrected within the text.
   - **Add:** The word is added to the dictionary and treated as correctly spelled in the future.
   - **Ignore:** The word is left unchanged, and the spell checker moves to the next word.

## Tools and Technologies
- **Programming Language:** The spell checker is implemented in C, known for its efficiency and control over system resources.
- **Data Structures:** Utilizes advanced data structures for managing the dictionary and handling user inputs efficiently.
- **Algorithm:** Employs the Damerau-Levenshtein algorithm to find the closest possible spelling corrections.

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/rusagara-ops/Spell-Checker.git

**Compile the program using:**

make

**Usage**

**To run the spell checker, use one of the following methods:**

**For file-based input:**

./speller input.txt

**For interactive text entry:**

./speller

Type QUIT to end the input process and output the final corrected text.
