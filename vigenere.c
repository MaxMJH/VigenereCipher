// ToDo:
// Make sure that there is a certain amount which the user can enter - perhaps 1mb (at least 1024 characters)?
// Encrypt plaintext using Vigenere Cipher:
//     To treat all input the same, capatalise each word and ignore space and punctuation (can use ctype.h).
//     Go through each letter in both the plaintext and key - to ensure the key loops through, if a count is equal to key length, reset.
//     For each letter in plaintext, turn it to ciphertext using:
//         ciphertext = 'A' + (((plaintext[i] - 'A') + (key[j] - 'A')) % 26); 

// Include relevant headers.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char*
encrypt(char* plaintext, char* key) {
    // Calculate the length of both plaintext and key to be used in iteration.
    size_t plaintext_length = strlen(plaintext);
    size_t key_length = strlen(key);

    // Create counters for iteration - kept outside of for loop initialisation as they need to be used out of loop scope. 
    size_t i;
    size_t j;

    // Create a variable to store ciphertext - size will be determined by length of plaintext, and +1 to account for null byte.
    char* ciphertext = (char*) malloc((sizeof(char) * plaintext_length) + 1);

    for (i = 0, j = 0; i < plaintext_length && j < key_length + 1; i++, j++) {
        // Check to see if j is equal to length of key, if so, set back to 0 to re-iterate through key until all letters are encrypted.	
	if (j == key_length) {
	    // Set j back to 0 to re-iterate through key.
	    j = 0;
	}

	ciphertext[i] = 'A' + (((plaintext[i] - 'A') + (key[j] - 'A')) % 26);
    }

    // Add null byte to end of ciphertext string.
    ciphertext[i] = '\0';

   // Return ciphertext.
   return ciphertext; 
}

int
main() {
    char* ciphertext = encrypt("MYNAMEISMAX", "BALL"); 

    printf("%s with key %s is, %s\n", "MYNAMEISMAX", "BALL", ciphertext);
    free(ciphertext);

    return 0;
}
