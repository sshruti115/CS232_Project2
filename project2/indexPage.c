/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Sabene completed
/* TODO: structure definitions */
struct TrieNode{
  int count; //Counts how many times a word appears
  struct TrieNode *children[26]; //26 Child pointers for lowercase alphabets
  int isEndOfWord;
};

struct TrieNode *getNode(){
  struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
  node->isEndOfWord = 0;
  for (int i = 0; i < 26; i++){
      node->children[i] = NULL;
  }
  return node;
}

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

/* TODO: change this return type */
void indexPage(const char* url);

int addWordOccurrence(const char* word, const int wordLength
		       /* TODO: other parameters you need */);

void printTrieContents(root, /*Shruti,Additional parameters are needed here!*/);

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

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
void indexPage(const char* url)
{}

int addWordOccurrence(const char* word, const int wordLength
		       /* TODO: other parameters you need */)
{}

void printTrieContents(root, /*Shruti,Additional parameters are needed here.*/)
{}

//Sabene completed
int freeTrieMemory(struct TrieNode* root) {
  //Base case
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
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}
