// ToDo:
// Make sure that there is a certain amount which the user can enter - perhaps 1mb (at least 1024 characters)?
// Check to see if the key contains any punctuation or spaces:
//     If so, notify the user, and stop all operations!

// Include relevant headers.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int iskeyvalid(char*);
char* encrypt(char*, char*);
char* decrypt(char*, char*);
int ischaralpha(char, char*, size_t, size_t*);

int
iskeyvalid(char* key) {
    int invalid_flag = 0;

    for (size_t i = 0; i < strlen(key); i++) {
        const char current_character = *(key + i);

  	if (ispunct(current_character) || isspace(current_character)) {
            invalid_flag = 1;
	}

	if (invalid_flag) {
            return 0;
	}
    }

    return 1;
}

char*
encrypt(char* plaintext, char* key) {
    // Calculate the length of both plaintext and key to be used in iteration.
    const size_t plaintext_length = strlen(plaintext);
    const size_t key_length = strlen(key);

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
	const char current_plaintext_character = toupper(*(plaintext + i));
        const char current_key_character = toupper(*(key + j));

        // Check to see if the current plaintext character is alphanumeric.	
	if (!ischaralpha(current_plaintext_character, ciphertext, i, &j)) {
	    // If the plaintext character is not alphanumeric, jump to the loop's next iteration.
	    continue;
        }

	*(ciphertext + i) = 'A' + (((current_plaintext_character - 'A') + (current_key_character - 'A')) % 26);
    }

    // Add null byte to end of ciphertext string.
    *(ciphertext + i) = '\0';

    // Return ciphertext.
    return ciphertext; 
}

char*
decrypt(char* ciphertext, char* key) {
    // Calculate the length of both ciphertext and key to be used in iteration.
    const size_t ciphertext_length = strlen(ciphertext);
    const size_t key_length = strlen(key);

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
	const char current_ciphertext_character = toupper(*(ciphertext + i));
	const char current_key_character = toupper(*(key + j));

        // Check to see if the current ciphertext character is alphanumeric.	
	if (!ischaralpha(current_ciphertext_character, plaintext, i, &j)) {
	    // If the ciphertext character is not alphanumeric, jump to the loop's next iteration.
	    continue;
	}

	*(plaintext + i) = 'A' + (((current_ciphertext_character - 'A') - (current_key_character - 'A') + 26) % 26);
    }

    // Add null byte to end of plaintext string.
    *(plaintext + i) = '\0';

    // Return plaintext.
    return plaintext;
}

int
ischaralpha(char character, char* text, size_t current_i, size_t* current_j) {
    // Check to see if the current character is a valid alphabetical letter. 
    if (!isalpha(character)) {
	// Add the character to the text.
        *(text + current_i) = character;

	// Decrement the value of j so that the key's current position is not forwarded.
	*current_j -= 1;

	// Signify that the character in question does contain whitespace or punctuation.
	return 0;
    } else {
	// Signify that the character in question is alphanumeric.
        return 1;
    }
}

int
main() {
    char* ciphertext = encrypt("my name is max!", "ball"); 
    printf("%s with key %s is, %s\n", "MY NAME IS MAX!", "BALL", ciphertext);
    free(ciphertext);

    char* plaintext = decrypt("NYYLNETDNAI", "BALL");
    printf("%s with key %s is, %s\n", "NYYLNETDNAI", "BALL", plaintext);
    free(plaintext);

    ciphertext = encrypt("MYNAMEISMAX", "BALL");
    printf("%s with key %s is, %s\n", "MYNAMEISMAX", "BALL", ciphertext);
    free(ciphertext);

    plaintext = decrypt("NY YLNE TD NAI!", "BALL");
    printf("%s with key %s is, %s\n", "NY YLNE TD NAI!", "BALL", plaintext);
    free(plaintext);

    char* key = "test ";
    printf("Is key valid? %d\n", iskeyvalid(key));

    return 0;
}
