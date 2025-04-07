/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Sabene completed
/* TODO: structure definitions */
struct TrieNode {
    int count; // Counts how many times a word appears
    struct TrieNode* children[26]; // 26 Child pointers for lowercase alphabets
    int isEndOfWord;
};

//Sabene completed
struct TrieNode* getNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;
    node->count = 0;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

//Sabene added parameters
int freeTrieMemory(struct TrieNode* root);
int getText(const char* srcAddr, char* buffer, const int bufSize);
//Shruti added these 2 parameters 
int addWordOccurrence(const char* word, int wordLength, struct TrieNode* root); 
int isValidWord(const char* word);

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

//Shruti Completed
/* TODO: change this return type */
int indexPage(const char* url, struct TrieNode* root) {
    if (!root) {
        fprintf(stderr, "Error: Trie root is NULL.\n");
        return -1;
    }

    char buffer[300001];  // Updated to hold up to 300,000 characters
    int bytesRead = getText(url, buffer, sizeof(buffer));

    if (bytesRead <= 0) {
        fprintf(stderr, "Failed to retrieve text from URL: %s\n", url);
        return -1;
    }

    printf("%s\n", url); // Print the URL as required

    // Define delimiters for tokenization
    const char* delimiters = " \t\n\r.,!?;:()[]{}\"";

    // Process the retrieved text and add words to Trie
    char* word = strtok(buffer, delimiters);
    while (word) {
        if (isValidWord(word)) {
            // Quick fix: remove leading "b'" if present
            if (word[0] == 'b' && word[1] == '\'') {
                word += 2; 
            }

            printf("\t%s\n", word);
            addWordOccurrence(word, strlen(word), root);
        }

        word = strtok(NULL, delimiters);  
    }

    return 0;
}

//Shruti Completed
// Helper function to check if a word contains at least one alphabetic character
int isValidWord(const char* word) {
    for (int i = 0; word[i]; i++) {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) {
            return 1;
        }
    }
    return 0;
}

//Shruti Completed
int addWordOccurrence(const char* word, int wordLength, struct TrieNode* root) {
    if (!root) return -1; // Return error if root is NULL

    struct TrieNode* current = root;
    for (int i = 0; i < wordLength; i++) {
        char ch = word[i];

        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch + ('a' - 'A');
        }

        if (ch < 'a' || ch > 'z') continue;
        int index = ch - 'a';

        if (!current->children[index]) {
            current->children[index] = getNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
    current->count++;
    return 0;
}

//Shruti Completed
void printTrieContents(struct TrieNode* root);

// Changed from 'word' to avoid conflict
char wordBuffer[256];

//Shruti Completed
// Function to traverse the Trie and print its contents
void traverse(struct TrieNode* node, int depth) {
    if (!node) return;

    if (node->isEndOfWord) {
        wordBuffer[depth] = '\0';
        printf("%s: %d\n", wordBuffer, node->count);
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            wordBuffer[depth] = 'a' + i;
            traverse(node->children[i], depth + 1);
        }
    }
}

//Shruti Completed
// Function to print Trie contents
void printTrieContents(struct TrieNode* root) {
    traverse(root, 0);
}

//Sabene completed
int main(int argc, char** argv){
  /* TODO: write the (simple) main function */

  /* argv[1] will be the URL to index, if argc > 1 */
  //If less than two arguments passed, return
  if (argc < 2){
    fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
    return 1;
  }

  const char* url = argv[1];

  //Initialize root of the Trie
  struct TrieNode* root = getNode();

  //Calls a function that indexes the web page and returns a pointer to your trie
  if (indexPage(url, root) != 0) {
    fprintf(stderr, "Error indexing the page.\n");
    freeTrieMemory(root);  // Free any allocated memory in case of failure
    return -1;
  }

  //Call a function that prints out the counts of all the words in the trie
  printTrieContents(root);

  //Calls a function to destroy the trie (i.e., free any allocated memory) when it is no longer needed
  freeTrieMemory(root);
  return 0;
}

//Shruti completed
int freeTrieMemory(struct TrieNode* root) {
    // Base case
    if (root == NULL) {
        return 0;
    }

    for (int i = 0; i < 26; i++) {
        freeTrieMemory(root->children[i]); // Recursively free children
    }

    free(root); // Free the current node
    return 0;
}

/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize) {
    FILE *pipe;
    int bytesRead;
    char command[1024];

    snprintf(command, sizeof(command), "curl -s \"%s\" | python3 getText.py", srcAddr);

    pipe = popen(command, "r");
    if (pipe == NULL) {
        fprintf(stderr, "ERROR: could not open the pipe for command %s\n", command);
        return 0;
    }

    bytesRead = fread(buffer, sizeof(char), bufSize - 1, pipe);
    buffer[bytesRead] = '\0';

    pclose(pipe);

    return bytesRead;
}






