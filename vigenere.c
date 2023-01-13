// Include relevant headers.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Pre-define functions to ensure identifiability as well as avoid errors.
int iskeyvalid(char*);
char* encrypt(char*, char*);
char* decrypt(char*, char*);
int ischaralpha(char, char*, size_t, size_t*);

/*
 *  The purpose of this function is to ensure that the key only conists 
 *  of alphabetical characters. If the key does contain non-alphabetical
 *  characters, a flag will be set and returned denoting invalidity.
 *  Otherwise, if the key is valid, true (1) will be returned. Note that,
 *  if the key contains any whitespace after, it will be marked as invalid.
 *
 *  This function takes a string as its argument (Key).
 */
int
iskeyvalid(char* key) {
    // Create a flag which will denote the key's validity.
    int invalid_flag = 0;

    // Iterate through each character in the string.
    for (size_t i = 0; i < strlen(key); i++) {
	// Get the current character.
        const char CURRENT_CHARACTER = *(key + i);

	// Check to see if the current character is regaraded is invalid.
  	if (ispunct(CURRENT_CHARACTER) || isspace(CURRENT_CHARACTER) || !isalpha(CURRENT_CHARACTER)) {
	    // If the current character is invalid, set the flag.
            invalid_flag = 1;
	}

	// Once the character has been inspected, if it is invalid, stop iteration and return false (0).
	if (invalid_flag) {
            return 0;
	}
    }

    // Signifies that the key is valid.
    return 1;
}

/*
 *  The purpose of this function is to encrypt plaintext by using the
 *  Vigenere Cipher. This function ensures that, by using the key, that
 *  each character within the plaintext is encrypted. If the plaintext
 *  contains punctuation, spaces, or numbers, those are left
 *  in place and are not encrypted. Once each character has been
 *  encrypted, the ciphertext will be returned.
 *
 *  This function takes two strings as its arguments (Plaintext and Key).
 */
char*
encrypt(char* plaintext, char* key) {
    // Calculate the length of both plaintext and key to be used in iteration.
    const size_t PLAINTEXT_LENGTH = strlen(plaintext);
    const size_t KEY_LENGTH = strlen(key);

    // Create counters for iteration - kept outside of for loop initialisation as they need to be used out of loop scope. 
    size_t i;
    size_t j;

    // Create a variable to store ciphertext - size will be determined by length of plaintext, and +1 to account for null byte.
    char* ciphertext = (char*) malloc((sizeof(char) * PLAINTEXT_LENGTH) + 1);

    for (i = 0, j = 0; i < PLAINTEXT_LENGTH && j < KEY_LENGTH + 1; i++, j++) { 
        // Check to see if j is equal to length of key, if so, set back to 0 to re-iterate through key until all letters are encrypted.	
	if (j == KEY_LENGTH) {
	    // Set j back to 0 to re-iterate through key.
	    j = 0;
	}

	// Ensure that user input is capitalised.
	const char CURRENT_PLAINTEXT_CHARACTER = toupper(*(plaintext + i));
        const char CURRENT_KEY_CHARACTER = toupper(*(key + j));

        // Check to see if the current plaintext character is alphanumeric.	
	if (!ischaralpha(CURRENT_PLAINTEXT_CHARACTER, ciphertext, i, &j)) {
	    // If the plaintext character is not alphanumeric, jump to the loop's next iteration.
	    continue;
        }

	// Add the ciphertext to the output.
	*(ciphertext + i) = 'A' + (((CURRENT_PLAINTEXT_CHARACTER - 'A') + (CURRENT_KEY_CHARACTER - 'A')) % 26);
    }
    
    // Add null byte to end of ciphertext string.
    *(ciphertext + i) = '\0'; 
    
    // Return ciphertext.  
    return ciphertext; 
}

/*  The purpose of this function is to decrypt the ciphertext by using the
 *  Vigenere Cipher. This function ensures that, by using the key, that 
 *  each character within the ciphertext is decrypted. If the ciphertext
 *  contains any punctuation, spaces, or nunbers, those are left in place.
 *  Once each character has been decrypted, the plaintext will be returned.
 *
 *  This function takes two strings as its arguments (Ciphertext, Key)
 */
char*
decrypt(char* ciphertext, char* key) {
    // Calculate the length of both ciphertext and key to be used in iteration.
    const size_t CIPHERTEXT_LENGTH = strlen(ciphertext);
    const size_t KEY_LENGTH = strlen(key);

    // Create counters for iteration - kept outside of for loop initialisation as they need to be used out of loop scope.
    size_t i;
    size_t j;

    // Create a variable to store plaintext - size will be determined by length of ciphertext, and +1 to account for null byte.
    char* plaintext = (char*) malloc((sizeof(char) * CIPHERTEXT_LENGTH) + 1);

    for (i = 0, j = 0; i < CIPHERTEXT_LENGTH && j < KEY_LENGTH + 1; i++, j++) {
        // Check to see if j is equal to length of key, if so, set back to 0 to re-iterate through key until all letters are decrypted. 
	if (j == KEY_LENGTH) {
	    j = 0;
	}

        // Ensure that user input is capitalised.
	const char CURRENT_CIPHERTEXT_CHARACTER = toupper(*(ciphertext + i));
	const char CURRENT_KEY_CHARACTER = toupper(*(key + j));

        // Check to see if the current ciphertext character is alphanumeric.	
	if (!ischaralpha(CURRENT_CIPHERTEXT_CHARACTER, plaintext, i, &j)) {
	    // If the ciphertext character is not alphanumeric, jump to the loop's next iteration.
	    continue;
	}

	// Add the plaintext to the outout.
	*(plaintext + i) = 'A' + (((CURRENT_CIPHERTEXT_CHARACTER - 'A') - (CURRENT_KEY_CHARACTER - 'A') + 26) % 26);
    }

    // Add null byte to end of plaintext string.
    *(plaintext + i) = '\0';

    // Return plaintext.
    return plaintext;
}

/*  The purpose of the function is to check whether or not a character is 
 *  alphabetical. If the character is not alphabetical, the current loops
 *  iteration is deducted to ensure that the key does not move forward by one.
 *  This ensures that each key is encrypted or decrypted correctly. If a key is
 *  alpabetical, true (1) will be returned, if not, false (0).
 *
 *  This function takes a character, string, int (size_t), and int* (size_t*) as its arugments.
 */ 
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
    // In order to avoid buffer (heap) overflow, the user will only be able to enter a max character length of 1023 bytes (last byte is null byte).
    const unsigned int MAX_BUFFER = 1024; 

    printf("Welcome to the non-technical, user-friendly Vigenere Cipher!\n");
    printf("Please enter one of the following options (via their numerical ordering):\n");
    printf("\t1. Encrypt\n");
    printf("\t2. Decrypt\n");
    printf("\t3. Exit\n");

    // Obtain the user's choice.
    int* numerical_choice = malloc(sizeof(int));

    // Keep looping until either the input does not contain an integer, or the input is equal to 3.
    // Note that, if the user enters any value other than an integer, the program will close.
    while (scanf("%d", numerical_choice) == 1 && *numerical_choice != 3) {
	// Use a switch to run the correct functions.
        switch (*numerical_choice) {
	    // Encryption case.
            case 1: {
	        // Create and allocate memory for plaintext and key. Also create variable for ciphertext.
                char* plaintext = malloc(MAX_BUFFER);
	        char* key = malloc(MAX_BUFFER);
                char* ciphertext;

		// Ask the user for the plaintext, but only allow the first 1023 characters to avoid buffer overflow.
	        printf("\nEnter the plaintext - Note that it has a limit of 1023 characters!: ");
	        scanf(" %1023[^\n]", plaintext);

		// Ask the user for the key, but only allow the first 1023 characters to avoid buffer overflow.
	        printf("Enter the key - Note that it has a limit of 1023 characters!: ");
	        scanf(" %1023[^\n]", key);

		// Check to see if the key is valid.
                if (!iskeyvalid(key)) {
                    printf("\nThe key you have entered is not valid!\n");
		    break;
                }

		// Assign the outout of the encrypt method.
	        ciphertext = encrypt(plaintext, key);

		// Print the ciphertext to stdout.
		printf("\nThe encrypted form is of the following:\n");
	        printf("%s\n", ciphertext);

		// Free the memory allocations.
		free(plaintext);
		free(key);
		free(ciphertext);
	        
		break;
	    } 
            // Decryption case.
	    case 2: {
	        // Create and allocate memory for ciphertext and key. Also create variable for plaintext.
	        char* ciphertext = malloc(MAX_BUFFER);
	        char* key = malloc(MAX_BUFFER);
	        char* plaintext;

		// Ask the user for the ciphertext, but only allow the first 1023 characters to avoid buffer overflow.
	        printf("\nEnter the ciphertext - Note that it has a limit of 1023 characters!: ");
	        scanf(" %1023[^\n]", ciphertext);

		// Ask the user for the key, but only allow the first 1023 characters to avoid buffer overflow.
	        printf("Enter the key - Note that it has a limit of 1023 characters!: ");
	        scanf(" %1023[^\n]", key);

		// Check to see if the key is valid.
                if (!iskeyvalid(key)) {
                    printf("\nThe key you have entered is not valid!\n");
		    break;
		}

		// Assign the outout of the decrypt method.
	        plaintext = decrypt(ciphertext, key);

		// Print the plaintext to stdout.
		printf("\nThe decrypted form is of the following:\n");
	        printf("%s\n", plaintext);

		// Free the memory allocations.
		free(ciphertext);
		free(key);
		free(plaintext);
	        
		break;
	    }
	    // Default Case.
	    default:
                printf("\nUnknown value entered!\n"); 
		break;
	}   
        
	printf("\nPlease enter one of the following options (via their numerical ordering):\n");
        printf("\t1. Encrypt\n");
	printf("\t2. Decrypt\n");
	printf("\t3. Exit\n");
    }
    
    // Free the memory allocation.
    free(numerical_choice); 

    return 0;
}
