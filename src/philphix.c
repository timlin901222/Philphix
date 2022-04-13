
/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philphix.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in 
 * the grading process.
 */
#ifndef _PHILPHIX_UNITTEST
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 1;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(0x61C, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */
  return 0;
}
#endif /* _PHILPHIX_UNITTEST */

/* Task 3 */
void readDictionary(char *dictName) {
  // -- TODO --
  char * buffer = 0;
  long length;
  FILE * f;
  if(!(f = fopen (dictName, "rb"))){
      exit(61);
  }
  if (f){
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc(length+1);
    if (buffer){
      fread (buffer, 1, length, f);
    }
    fclose (f);
    buffer[length] = '\0';
  }
  while(buffer){
    while(isspace((char) *buffer)) buffer++;
    char * nextLine = strchr(buffer, '\n');
    int strLineLen = nextLine ? (nextLine-buffer) : strlen(buffer);
    char * tempStr = (char *) malloc(strLineLen+1);
    if (tempStr){
         memcpy(tempStr, buffer, strLineLen);
         tempStr[strLineLen] = '\0';  // NUL-terminate!
    }
    writeInDict(tempStr);
    buffer = nextLine ? (nextLine+1) : NULL;
  }
}

void writeInDict(char *strLine) {
    if(strlen(strLine) == 0) {
      return;
    }
    char *rest = strpbrk(strLine, "\t ");
    int strLineLen = rest ? (rest-strLine) : strlen(strLine);
    char * tempStr = (char *) malloc(strLineLen+1);
    if (tempStr){
         memcpy(tempStr, strLine, strLineLen);
         tempStr[strLineLen] = '\0';  
    }
    while(isspace((char) *rest)) rest++;
    insertData(dictionary, tempStr, rest);
}

/* Task 4 */
void processInput() {
  // -- TODO --
  fprintf(stderr, "You need to implement processInput\n");
  char c;
  char *tempStr;
  int size;

  
  
  fprintf(stderr, "runs here\n");
  size = 0;
 
  while ((c = fgetc(stdin)) != EOF) {
      if (isalnum(c)) {
        size = size + 1;
        if (size == 1) tempStr = malloc(size+1);
        else tempStr = realloc(tempStr, size+1);
        tempStr[size-1] = c;
        tempStr[size] = '\0';
      }
      else {
        //output tempStr
        if (tempStr != NULL) {
          if (findData (dictionary, tempStr)){
            fprintf(stdout, "%s", findData(dictionary, tempStr));
          }
          else {
            char *copyStr = malloc(strlen(tempStr)+1);
            memcpy(copyStr, tempStr, strlen(tempStr));
            copyStr[strlen(tempStr)] = '\0';
            int i;
            for (i = 1; i < strlen(tempStr); i++){
              copyStr[i] = tolower(copyStr[i]);
            }
            if (findData(dictionary, copyStr)) {
              fprintf(stdout, "%s", findData(dictionary, copyStr));
            }
            else {
              copyStr[0] = tolower(copyStr[0]);
              if (findData(dictionary,copyStr)) {
                fprintf(stdout, "%s", findData(dictionary, copyStr));
              }
              else{
                fprintf(stdout, "%s", tempStr);
              }
            }
            free(copyStr);
          }
        //clear tempStr
        }
        
        free(tempStr);
        tempStr = NULL;
        size = 0;
        // output character
        fprintf(stdout , "%c", c);





      }

  }
  if (tempStr != NULL) {
    if (findData (dictionary, tempStr)){
            fprintf(stdout, "%s", findData(dictionary, tempStr));
          }
          else {
            char *copyStr = malloc(strlen(tempStr)+1);
            memcpy(copyStr, tempStr, strlen(tempStr));
            copyStr[strlen(tempStr)] = '\0';
            int i;
            for (i = 1; i < strlen(tempStr); i++){
              copyStr[i] = tolower(copyStr[i]);
            }
            if (findData(dictionary, copyStr)) {
              fprintf(stdout, "%s", findData(dictionary, copyStr));
            }
            else {
              copyStr[0] = tolower(copyStr[0]);
              if (findData(dictionary,copyStr)) {
                fprintf(stdout, "%s", findData(dictionary, copyStr));
              }
              else{
                fprintf(stdout, "%s", tempStr);
              }
            }
            free(copyStr);
          }
        //clear tempStr
        }
  

}
