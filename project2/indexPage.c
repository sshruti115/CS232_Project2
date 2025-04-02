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

struct TrieNode* getNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

//Shruti Completed
/* TODO: change this return type */
int indexPage(const char* url, struct TrieNode* root) {
    if (!root) {
        fprintf(stderr, "Error: Trie root is NULL.\n");
        return -1;
    }

    char buffer[10000];
    int bytesRead = getText(url, buffer, sizeof(buffer));

    if (bytesRead <= 0) {
        fprintf(stderr, "Failed to retrieve text from URL: %s\n", url);
        return -1;
    }

    // Process the retrieved text and add words to Trie
    char* word = strtok(buffer, " \t\n\r.,!?;:()[]{}");
    while (word) {
        addWordOccurrence(word, strlen(word), root);
        word = strtok(NULL, " \t\n\r.,!?;:()[]{}");
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

char word[100];

// Function to traverse the Trie and print its contents
void traverse(struct TrieNode* node, int depth) {
    if (!node) return;

    if (node->isEndOfWord) {
        word[depth] = '\0';
        printf("%s: %d\n", word, node->count);
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            word[depth] = 'a' + i;
            traverse(node->children[i], depth + 1);
        }
    }
}

// Function to print Trie contents
void printTrieContents(struct TrieNode* root) {
    traverse(root, 0);
}

//Sabene added parameters
int freeTrieMemory(struct TrieNode* root);
int getText(const char* srcAddr, char* buffer, const int bufSize);

//Sabene's work in progress
int main(int argc, char** argv){
  /* TODO: write the (simple) main function

  /* argv[1] will be the URL to index, if argc > 1 */
  //If less than two arguments passed, return
  if (argc <2){
    return;
  }

 while (){

 }

  return 0;
}

//Shruti Completed 
/* TODO: define the functions corresponding to the above prototypes */
/* TODO: change this return type */
int indexPage(const char* url, struct TrieNode* root) {
    if (!root) {
        fprintf(stderr, "Error: Trie root is NULL.\n");
        return -1;
    }

    char buffer[10000];
    int bytesRead = getText(url, buffer, sizeof(buffer));

    if (bytesRead <= 0) {
        fprintf(stderr, "Failed to retrieve text from URL: %s\n", url);
        return -1;
    }

    // Process the retrieved text and add words to Trie
    char* word = strtok(buffer, " \t\n\r.,!?;:()[]{}");
    while (word) {
        addWordOccurrence(word, strlen(word), root);
        word = strtok(NULL, " \t\n\r.,!?;:()[]{}");
    }

    return 0;
}

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

// Helper function to traverse and print Trie contents
void traverse(struct TrieNode* node, char word[], int depth) {
    if (!node) return;

    if (node->isEndOfWord) {
        word[depth] = '\0';
        printf("%s: %d\n", word, node->count);
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            word[depth] = 'a' + i;
            traverse(node->children[i], word, depth + 1);
        }
    }
}

void printTrieContents(struct TrieNode* root) {
    char word[100];
    traverse(root, word, 0);
}

//Sabene completed
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

    snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

    pipe = popen(buffer, "r");
    if (pipe == NULL) {
        fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
                buffer);
        return 0;
    }

    bytesRead = fread(buffer, sizeof(char), bufSize - 1, pipe);
    buffer[bytesRead] = '\0';

    pclose(pipe);

    return bytesRead;
}




