// ToDo:
// Make sure that there is a certain amount which the user can enter - perhaps 1mb (at least 1024 characters)?
// Check to see if the key contains any punctuation or spaces:
//     If so, notify the user, and stop all operations!

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

	// Ensure that user input is capitalised.
	const char current_plaintext_character = toupper(plaintext[i]);
        const char current_key_character = toupper(key[j]);

	// Check to see if the current plaintext character is a space or punctuation.
	if (isspace(current_plaintext_character) || ispunct(current_plaintext_character)) {
	    // Add the character to the ciphertext.
	    ciphertext[i] = current_plaintext_character;

	    // Decrement the value of j so that the key's current position is not forwarded.
	    --j;

	    // Jump the current iteration. 
	    continue;
	}

	ciphertext[i] = 'A' + (((current_plaintext_character - 'A') + (current_key_character - 'A')) % 26);
    }

    // Add null byte to end of ciphertext string.
    ciphertext[i] = '\0';

    // Return ciphertext.
    return ciphertext; 
}

char*
decrypt(char* ciphertext, char* key) {
    // Calculate the length of both ciphertext and key to be used in iteration.
    size_t ciphertext_length = strlen(ciphertext);
    size_t key_length = strlen(key);

    // Create counters for iteration - kept outside of for loop initialisation as they need to be used out of loop scope.
    size_t i;
    size_t j;

    // Create a variable to store plaintext - size will be determined by length of ciphertext, and +1 to account for null byte.
    char* plaintext = (char*) malloc((sizeof(char) * ciphertext_length) + 1);

    for (i = 0, j = 0; i < ciphertext_length && j < key_length + 1; i++, j++) {
        // Check to see if j is equal to length of key, if so, set back to 0 to re-iterate through key until all letters are decrypted. 
	if (j == key_length) {
	    j = 0;
	}

        // Ensure that user input is capitalised.
	const char current_plaintext_character = toupper(ciphertext[i]);
	const char current_key_character = toupper(key[j]);

	// Check to see if the current ciphertext character is a space or punctuation.
	if (isspace(current_plaintext_character) || ispunct(current_plaintext_character)) {
	    // Add the character to the plaintext.
	    plaintext[i] = current_plaintext_character;

	    // Decrement the value of j so that the key's current position is not forwarded.
	    --j;

	    // Jump the current iteration.
	    continue;
	}

	plaintext[i] = 'A' + (((current_plaintext_character - 'A') - (current_key_character - 'A') + 26) % 26);
    }

    // Add null byte to end of plaintext string.
    plaintext[i] = '\0';

    // Return plaintext.
    return plaintext;
}

int
main() {
    char* ciphertext = encrypt("MY NAME IS MAX!", "BALL"); 
    printf("%s with key %s is, %s\n", "MY NAME IS MAX!", "BALL", ciphertext);
    free(ciphertext);

    char* plaintext = decrypt("NYYLNETDNAI", "BALL");
    printf("%s with key %s is, %s\n", "NYYLNETDNAI", "BALL", plaintext);
    free(plaintext);

    return 0;
}
