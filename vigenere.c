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
        const char CURRENT_CHARACTER = *(key + i);

  	if (ispunct(CURRENT_CHARACTER) || isspace(CURRENT_CHARACTER)) {
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

	*(ciphertext + i) = 'A' + (((CURRENT_PLAINTEXT_CHARACTER - 'A') + (CURRENT_KEY_CHARACTER - 'A')) % 26);
    }
    
    // Add null byte to end of ciphertext string.
    *(ciphertext + i) = '\0'; 
    
    // Return ciphertext.  
    return ciphertext; 
}

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

	*(plaintext + i) = 'A' + (((CURRENT_CIPHERTEXT_CHARACTER - 'A') - (CURRENT_KEY_CHARACTER - 'A') + 26) % 26);
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
    const unsigned int MAX_BUFFER = 1024; 

    printf("Welcome to the non-technical, user-friendly Vigenere Cipher!\n");
    printf("Please enter one of the following options (via their numerical ordering):\n");
    printf("\t1. Encrypt\n");
    printf("\t2. Decrypt\n");
    printf("\t3. Exit\n");

    int* numerical_choice = malloc(sizeof(int));

    while (scanf("%d", numerical_choice) == 1 && *numerical_choice != 3) {
        switch (*numerical_choice) {
            case 1: {
                char* plaintext = malloc(MAX_BUFFER);
	        char* key = malloc(MAX_BUFFER);
                char* ciphertext;

	        printf("\nEnter the plaintext - Note that it has a limit of 1023 characters!: ");
	        scanf(" %1023[^\n]", plaintext);

	        printf("Enter the key - Note that it has a limit of 1023 characters!: ");
	        scanf(" %1023[^\n]", key);

                if (!iskeyvalid(key)) {
                    printf("\nThe key you have entered is not valid!\n");
		    break;
                }

	        ciphertext = encrypt(plaintext, key);

		printf("\nThe encrypted form is of the following:\n");
	        printf("%s\n", ciphertext);

		free(plaintext);
		free(key);
		free(ciphertext);
	        
		break;
	    } 
	    case 2: {
	        char* ciphertext = malloc(MAX_BUFFER);
	        char* key = malloc(MAX_BUFFER);
	        char* plaintext;

	        printf("\nEnter the ciphertext - Note that it has a limit of 1023 characters!: ");
	        scanf(" %1023[^\n]", ciphertext);

	        printf("Enter the key - Note that it has a limit of 1023 characters!: ");
	        scanf(" %1023[^\n]", key);

                if (!iskeyvalid(key)) {
                    printf("\nThe key you have entered is not valid!\n");
		    break;
		}

	        plaintext = decrypt(ciphertext, key);

		printf("\nThe decrypted form is of the following:\n");
	        printf("%s\n", plaintext);

		free(ciphertext);
		free(key);
		free(plaintext);
	        
		break;
	    }
	    default:
                printf("\nUnknown value entered!\n"); 
		break;
	}   
        
	printf("\nPlease enter one of the following options (via their numerical ordering):\n");
        printf("\t1. Encrypt\n");
	printf("\t2. Decrypt\n");
	printf("\t3. Exit\n");
    }

    free(numerical_choice); 

    return 0;
}
