///////////////////////////////////////////////////////////////////////////////
//                   ALL STUDENTS COMPLETE THESE SECTIONS
// Title:            EnigmaMachine
// Files:            enigma.c
// Semester:         Summer 2020
//
// Author:           SREENIVAS KRISHNA NAIR
// CS Login:         sreenivas
//////////////////////////// 80 columns wide //////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHA 26

int string_length(char *);
int check_digit(int);

const char *ROTOR_CONSTANTS[] = {
    // Identity Rotor (index 0 - and useful for testing):
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",

    // Standard Rotors 1 through 8:
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
    "ESOVPZJAYQUIRHXLNFTGKDCMWB",
    "VZBRGITYUPSDNHLXAWMJQOFECK",
    "JPGVOUMFYQBENHZRDKASXLICTW",
    "NZJHGRCXMYSWBOUFAIVLPEKQDT",
    "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

/** Start your users off with a welcome message, 
* such as Willkommen auf der Enigma-Maschine 
* (that's "Welcome to the Enigma Machine" in German.)
*/
const char *WELCOME_MSG =
    "Willkommen auf der Enigma-Maschine!";

/**
* Message printed before exit.
*/
const char *EXIT_MESSAGE =
    "Auf Wiedersehen!";

/**
* Prompt the user for the initial options.
*/
const char *MENU_OPTIONS =
    "\nOPTIONS\n2 : encrypt a message\n3 : decrypt a message\n1 : exit the Enigma Machine\n\nENTER YOUR CHOICE: ";

/**
* Error message for invalid option.
*/
const char *WRONG_OPTION =
    "Input is not valid. Try again.";

/**
* Message about start of encryption.
*/
const char *ENCRYPTION_MESSAGE =
    "\nENCRYPTION WITH ENIGMA!\n=======================";

/**
* Message about start of decryption.
*/
const char *DECRYPTION_MESSAGE =
    "\nDECRYPTION WITH ENIGMA!";

/**
* Message to prompt the user for the number of rotations.
*/
const char *NUMROTATIONS_MSG =
    "How many rotations you want to perform on the rotors?: ";

/**
* Message about invalid input for the number of rotations.
*/
const char *INVALID_NUMROTATIONS =
    "Invalid number of rotations. Try again.";

/**  
* Message to prompt the user to enter the list of rotors.
*/
const char *ROTOR_PROMPT =
    "\nROTOR CONFIGURATION\n \
-------------------\n \
This must be a list of numbers in the range \
from 0 to 8, with no spaces or other delimiters.\n \
Maximum number of rotors you can use is 4. \
Note that rotor 0 is the identity rotor.\n \
        \nENTER YOUR ROTOR CONFIGURATION: ";

/**
* Message that rotor configurations are going to 
* be printed before rotations are completed.
*/
const char *ROTOR_BEFORE_ROTATION =
    "\nYOUR ROTOR CONFIGURATION BEFORE ROTATION\n";

/**
* Message that rotor configurations are going to 
* be printed after completing rotation on rotors.
*/
const char *ROTOR_AFTER_ROTATION =
    "\nYOUR ROTOR CONFIGURATION AFTER ROTATION\n";

/**
* Message about invalid input for the rotor
* indices due to duplicate rotor entries.
*/
const char *DUP_ROTORS_MSG =
    "You cannot use the same rotor twice in a row. Try again.";

/**
* Message about invalid input for the rotor
* indices if something other than an integer
* is entered.
*/
const char *INVALID_ROTOR_MSG =
    "Invalid rotor configuration. Try again.";

/**
* Message about invalid input for the rotor
* indices when more than 4 rotor indices are 
* entered.
*/
const char *MORE_THAN_ALLOWED =
    "You cannot use more than 4 rotors. Try again.";

/**
* Message about invalid input for the rotor
* indices since the input is empty.
*/
const char *NO_ROTORS_MSG =
    "You must specify at least one rotor. Try again.";

/**
* Prompt the user to enter the message to be
* encrypted
*/
const char *USER_PROMPT1 =
    "Enter the line(s) of text to be encrypted: ";
/**
* Prompt the user to enter the message to be decrypted
*/
const char *USER_PROMPT2 =
    "Enter the line(s) of text to be decrypted: ";

/**	
* This method takes as a parameter the string entered
* by the user for the option. It should check 
* whether the option entered by the user is an integer.
* If it is an integer, then it checks whether it is 1, 2 or 3. 
* If it is 1, 2 or 3, then return the corresponding number.
* If it is some other integer or string, 
* then return -1 to indicate an error.
* 
* For now it returns only -1. 
* 
* @param options (option entered by user)
* @return -1 for invalid input, otherwise 1, 2 or 3
*/
int validate_options(char *options)
{
        //Code to check if a single digit was inputted
        if (string_length(options) == 1)
        {
                //checking if character in string is digit
                if (check_digit(options[0]))
                {
                        return options[0] - '0'; //subtraction with '0' to convert to digit.
                }
        }
        return -1;
}

/**
* This method accepts as a parameter the String entered 
* by the user for rotor indices. This method checks 
* several things:
* 1) whether the string contains only integers
* 2) whether there are no more than 4 rotor indices
* 3) whether there are no duplicate rotor indices in a row
* 4) whether at least one rotor index is entered
* 5) whether the entered rotor indices are between 0 to 8
* 
* If the user input is correct, method creates a 1D array
* with integer indices in it and returns this 1D array. All 
* unoccupied positions in the array should be left at -1
* 
* For invalid input this method returns NULL.
* 
* For now it returns only NULL.
* 
* @param rotor_indices_line (user input String for rotor indices)
* @return 1D array if user input is correct, null-if not
*/
int *parse_rotor_indices(char *rotor_indices_line)
{
        //checks if the user entered all rotator configs in the 0 - 8 range
        for (int i = 0; i < string_length(rotor_indices_line); i++)
        {
                if (rotor_indices_line[i] <= 47 || rotor_indices_line[i] >= 57)
                {
                        printf("%s", INVALID_ROTOR_MSG);
                        return NULL;
                }
        }

        //Check if the user entered 4 or less integers
        if (string_length(rotor_indices_line) > 4)
        {
                printf("%s", MORE_THAN_ALLOWED);
                return NULL;
        }

        //checks for duplicate rotor configs, 212 ok; 221 not ok
        for (int i = 0; i < (string_length(rotor_indices_line) - 1); i++)
        {
                if (rotor_indices_line[i] == rotor_indices_line[i + 1])
                {
                        printf("%s", DUP_ROTORS_MSG);
                        return NULL;
                }
        }

        //use ret (below) as the array to return
        //initializing to -1 allows us to easily tell how many spots in
        //the array are occupied
        int *ret = calloc(5, sizeof(int));
        for (int i = 0; i < 5; i++)
        {
                ret[i] = -1;
        }
        for (int i = 0; i < string_length(rotor_indices_line); i++)
        {
                ret[i] = rotor_indices_line[i] - '0';
        }
        return ret;
}
/**
 * Helper function to convert char rotar to  int rotar.
 * @param char_rotar (constant character parameter)
 * @return int representation of rotar
*/
int *char_to_int_rotar(const char *char_rotar)
{
        int *ret = calloc(26, sizeof(int));
        for (int i = 0; i < 26; i++)
        {
                ret[i] = char_rotar[i] - 65;
        }
        return ret;
}
/**
 * Helper Function to calculate length of row 
 * @param rotor_indices (rows in 2D table)
 * @return the number of rows
 */
int calc_row(int *rotor_indices)
{
        int i = 0;
        while (rotor_indices[i] != -1)
                i++;
        return i;
}

/**
* This method takes as a parameter a 1D array of
* integers that represent the rotor indices 
* entered by the user. Using these indices
* this method builds a 2D array which is the
* integer representation of the rotors to be used.
* The rotor configurations should be taken from 
* the ROTOR_CONSTANTS.
* 
* If the rotor_indices is [1, 3, 4],
* then this method builds the 2D array of rotors 1, 3, 4 as shown below:
* 
* [4 10 12 5 11 6 3 16 21 25 13 19 14 22 24 7 23 20 18 15 0 8 1 17 2 9]
* [1 3 5 7 9 11 2 15 17 19 23 21 25 13 24 4 8 22 6 0 10 12 20 18 16 14]
* [4 18 14 21 15 25 9 0 24 16 20 8 17 7 23 11 13 5 19 6 10 3 2 12 22 1]
* 
* For now it returns NULL.
* 
* @param rotor_indices (1D array with rotor indices)
* @return 2D array with rotor configurations
*/
int **set_up_rotors(int *rotor_indices)
{
        //Set up dimensions of 2-D array
        int cols = 26;
        int rows = calc_row(rotor_indices);

        //Reserve memory for 2D array
        int **ret = malloc(rows * sizeof(int *)); //Allocate rows
        for (int i = 0; i < rows; i++)
        {
                ret[i] = malloc(cols * sizeof(int)); //Allocate columns
        }

        //Populate 2-D array
        for (int i = 0; i < rows; i++)
        {
                int index = rotor_indices[i];
                ret[i] = char_to_int_rotar(ROTOR_CONSTANTS[index]);
        }

        return ret;
}

/**
* This method prints out the 2D array of rotor
* configurations that is passed to it as a parameter.
* 
* @param rotor_config
* @param num_rows
* @param num_cols
*/
void display_rotor_configuration(int **rotor_config, int num_rows, int num_cols)
{
        printf("====================================================\n");
        printf("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z\n");
        printf("====================================================\n");

        // Print rotor configurations here
        for (int i = 0; i < num_rows; i++)
        {
                for (int j = 0; j < num_cols; j++)
                {
                        printf("%c%s", rotor_config[i][j] + 'A', " ");
                }
                printf("\n");
        }

        printf("----------------------------------------------------\n");
}

/**
* This method accepts as a parameter the String input 
* from the user num_rotations_input and checks whether
* the number is in the range from 0 to 25. 
* If it is, it returns the number of rotations, else it returns -1. 
* 
* For now it returns -1.
* 
* @param num_rotations_input (number of rotations input String)
* @return The number of rotations if input is valid, -1 otherwise.
*/
int validate_num_rotations(char *num_rotations_input)
{
        int temp[3] = {-1, -1, -1}; //used to hold separtae digits of given number
        int ret = 0;                //return value
        int num = 0;                //used to hold the ASCII/int converted from ASCII
        char ch;                    //used to hold the ASCII entered for atoi

        int length = string_length(num_rotations_input); //length of number entered
        if (length > 2)                                  //largest number is 25, two digits
        {
                return -1; //return if longer than two digits
        }

        //goes through the digits, converts from ASCII,
        //store int (from ASCII) in temp
        for (int i = 0; i < length; i++)
        {
                num = (int)num_rotations_input[i];
                ch = (char)num_rotations_input[i];
                if (check_digit(num))
                {
                        num = atoi(&ch);
                        temp[i] = num;
                }
        }

        //single digit, don't have to convert
        if (length == 1)
        {
                ret = temp[0];
                return ret;
        }

        //two digits, have to convert to int
        //currently in array (ex): [2][3] -> 23
        int mult = 10; //10 because the largest the number is two digits (10's place)
        for (int i = 0; i < length; i++)
        {
                ret = ret + mult * temp[i];
                mult = mult / 10; //next is 1's place
        }

        //if ret is a valid number, return it, otherwise -1
        if (ret >= 0 && ret <= 25)
                return ret;
        else
                return -1;
}
/**
 * Helper function to rotate a row of content
 * The helper function breaks array into 3 parts;
*/
int *rotate_helper(int num_of_rotations, int *row_to_rotate)
{
        while (num_of_rotations > 0)
        {
                int temp_last = row_to_rotate[25];
                for (int j = 25; j > 0; j--)
                {
                        row_to_rotate[j] = row_to_rotate[j - 1];
                }
                row_to_rotate[0] = temp_last;
                num_of_rotations--;
        }
        return row_to_rotate;
}

/**
* This method accepts as parameters the number of 
* rotations to be done on the 2D array of integers 
* named rotor_set that represents the rotor configurations.
* It should perform those many rotations on the 2D array
* of rotors.
*  
* For now it returns the original 2D array passed to it.
* 
* @param num_of_rotations (number of rotations to be done)
* @param rotor_set (rotor configurations)
* @param num_rows (number of rows in rotor_set)
* @param num_cols (number of columns in rotor_set)
* @return rotated 2D array of rotor configurations
*/
int **rotate_rotors(int num_of_rotations, int **rotor_set, int num_rows, int num_cols)
{
        // Return the original rotor set if no rotations are needed.
        if (num_of_rotations == 0)
        {
                return rotor_set;
        }

        if (num_of_rotations >= 1 && num_of_rotations <= 25)
        {
                for (int row = 0; row < num_rows; row++)
                {
                        rotor_set[row] = rotate_helper(num_of_rotations, rotor_set[row]);
                }
        }
        return rotor_set;
        display_rotor_configuration(rotor_set, num_rows, num_cols);
}

/**
 * The Helper method is used to convert the char array to an int array with mapping
 * A->0, B->1, ......
 * @param message (contains the char array)
 * @param len (length of message array)
 * @return the int array mapping
*/
int *to_int_message(char *message, int len)
{
        int *ret = calloc(len, sizeof(int));
        for (int j = 0; j < len; j++)
        {
                ret[j] = -1;
        }
        for (int j = 0; j < len; j++)
        {
                if (message[j] >= 65 && message[j] <= 90)
                {
                        ret[j] = message[j] - 65;
                }
        }

        return ret;
}

/**
 * Helper function to get char from integer
 * @param code (index in mapping)
 * @return index of alphabet in mapping
*/
char int_to_char(int code)
{
        char *list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        return list[code];
}

/**
* This method takes as parameters a String message 
* to be encrypted and a 2D array of integers that
* represent the rotor configuration. It does the 
* encryption of the message using rotor configu-
* rations and should return the encrypted message.
*   
* For now it returns the original message. 
* 
* @param message (message to be encrypted)
* @param rotor_set (rotor configurations)
* @param num_rows (number of rows in rotor_set)
* @param num_cols (number of columns in rotor_set)
* @return encrypted message
*/
char *encrypt(char *message, int **rotor_set, int num_rows, int num_cols)
{
        char *encrypted_message = calloc(strlen(message), sizeof(char));

        //Algortihm steps:
        //1. Convert all apllicable characters to upper case
        //2. Convert char* message to int* with all non upper case characters
        // set to -1
        //3. Use int* message to convert required message into encrypted char*
        //4. repeated process for required number of rows.

        //convert message to upper case
        for (int i = 0; message[i] != '\0'; i++)
        {
                message[i] = toupper(message[i]);
        }

        //convert to int message
        int *int_message = to_int_message(message, strlen(message));

        //process through the int message
        for (int i = 0; i < strlen(message); i++)
        {
                if (int_message[i] != -1)
                {
                        //Process of encryption
                        for (int k = 0; k < num_rows; k++)
                        {
                                int num = rotor_set[k][int_message[i]];
                                int_message[i] = num;
                        }
                        encrypted_message[i] = int_to_char(int_message[i]);
                }
                else
                {
                        encrypted_message[i] = message[i];
                }
        }
        free(int_message);
        return encrypted_message;
}
/**
 * Helper function to return position of the alphabets in message on the 
 * rotar
 * @param int_message (array of position codes)
 * @param len (length of int array)
 * @param rotor (array of rotor)
 * @return position on rotar
*/
int *get_pos_on_rotor(int *int_message, int len, int *rotor)
{
        int *positions = calloc(len, sizeof(int));
        for (int j = 0; j < len; j++)
        {

                //Parsing through every member of int_message
                if (int_message[j] != -1)
                {
                        int index = 0;
                        for (int z = 0; z < 26; z++)
                        {
                                if (int_message[j] == rotor[z])
                                {
                                        index = z;
                                }
                        }

                        positions[j] = index;
                }
                else
                {
                        positions[j] = -1;
                }
        }
        return positions;
}

/**
* This method takes as parameters a String message
* to be decrypted and a 2D array of integers that 
* represent the rotor configuration. It completes
* the decryption process of this message using 
* the rotor configuration. This method should return
* the decrypted message as a String.
*    
* For now it returns the original message.
* 
* @param message (message to be decrypted)
* @param rotor_set (rotor configurations)
* @param num_rows (number of rows in rotor_set)
* @param num_cols (number of cols in rotor_set)
* @return decrypted message
*/
char *decrypt(char *message, int **rotor_set, int num_rows, int num_cols)
{
        //Algortihm steps:
        //1. Convert all apllicable characters to upper case
        //2. Convert char* message to int* with all non upper case characters
        // set to -1
        //3. Use int* message to convert required message into encrypted char*
        //4. repeated process for required number of rows.

        char *dencrypted_message = calloc(strlen(message), sizeof(char));

        //convert message to upper case
        for (int i = 0; message[i] != '\0'; i++)
        {
                message[i] = toupper(message[i]);
        }

        //convert to int message
        int *int_message = to_int_message(message, strlen(message));

        /*
        position on rotor
        */

        for (int i = 0; i < strlen(message); i++)
        {
                if (int_message[i] != -1)
                {

                        for (int k = 0; k < num_rows; k++)
                        {
                                //Decryption process
                                int *pos_on_rotor = get_pos_on_rotor(int_message, strlen(message), rotor_set[k]);
                                int_message[i] = pos_on_rotor[i];
                        }
                        dencrypted_message[i] = int_to_char(int_message[i]);
                }
                else
                {
                        dencrypted_message[i] = message[i];
                }
        }
        free(int_message);
        return dencrypted_message;
}

/**
 * returns length of string
 * @param str (string to find length)
 * @return length of string
*/
int string_length(char *str)
{
        //printf("in string length\n");
        int i = 0;
        int length = 0;
        //printf("%c\n",str[i]);
        while (str[i] != '\0' && str[i] != '\n')
        {
                //printf("length: %d\n", length);
                length++;
                i++;
        }
        return length;
}

/**
 * returns if num is a digit
 * @param num (the ASCII of character)
 * @return 1 for digit, 0 otherwise
*/
int check_digit(int num)
{
        if (num >= 48 && num <= 57)
                return 1;
        else
                return 0;
}

/**
* From this main method execution will start. 
* It should contain the main loop for the usage of the
* Enigma machine and should call other methods in 
* this class. There are some comments added to the 
* body of this method that might help you to 
* complete the project. 
* 
* @param args unused
*/
int main(int argc, char *argv[])
{

        // Print out welcome message
        printf("%s\n", WELCOME_MSG);

        // The variable is used to indicate whether the program is over.
        int done = 0;

        // While loop for getting the correct option from user
        while (done != 1)
        {
                // Prompt the user to enter an option
                printf("%s", MENU_OPTIONS);

                // Capture the option entered by user in the form of string in this variable option
                char option[3];
                scanf("%s", option);

                // Validate the input option
                int ret = validate_options(option);

                switch (ret)
                {

                case 1:
                        // If the input option is 1, set done as true (1).
                        done = 1;
                        printf("%s\n", EXIT_MESSAGE);
                        break;

                case 2:

                case 3:
                        if (ret == 2)
                        {
                                // Print the encyrtion message if the input option is 2.
                                printf("%s\n", ENCRYPTION_MESSAGE);
                        }
                        else
                        {
                                // Print the decyrtion message if the input option is 3.
                                printf("%s\n", DECRYPTION_MESSAGE);
                        }

                        // Initialize the indices of rotors as null.
                        int *indices_of_rotor = NULL;
                        while (indices_of_rotor == NULL)
                        {

                                // Prompt the user to enter valid indices of rotors.
                                printf("%s", ROTOR_PROMPT);

                                // Capture the indices entered by the user in the variable rotor_indices_line
                                char rotor_indices_line[6];

                                scanf("%s", rotor_indices_line);

                                // Parse the input for indices of rotors.
                                indices_of_rotor = parse_rotor_indices(rotor_indices_line);
                                
                        }

                        // The input for indices of rotors must be valid here.
                        // Set up the rotors and display them.
                        int **rotor_set = set_up_rotors(indices_of_rotor);
                        printf("%s\n", ROTOR_BEFORE_ROTATION);

                        // Call display_rotor_configuration with
                        // appropriate parameters for num_rows and num_cols
                        //
                        // make sure you initialize the indices_of_rotor array
                        // in parse_rotor_indices with -1's otherwise this will not work
                        int i = 0;
                        int num_rows = 0;
                        while (indices_of_rotor[i] != -1 && i < 4)
                        {
                                num_rows++;
                                i++;
                        }
                        
                        //Free indices_of_rotor
                        free(indices_of_rotor);

                        //display the current rotor configuration
                        display_rotor_configuration(rotor_set, num_rows, ALPHA);

                        // Initialize the number of rotations as -1.
                        int num_of_rotations = -1;
                        while (num_of_rotations == -1)
                        {

                                // Prompt the user to enter the number of rotations.
                                printf("%s", NUMROTATIONS_MSG);

                                // Capture the input entered by the user in the variable num_rotations_input
                                char num_rotations_input[4];
                                scanf("%s", num_rotations_input);

                                // Validate the input for number of rotaions.
                                num_of_rotations = validate_num_rotations(num_rotations_input);
                                if (num_of_rotations == -1)
                                        printf("%s", INVALID_NUMROTATIONS);
                        }

                        // The input for number of rotations must be valid here.
                        // Build the rotated rotors by calling rotate_rotors
                        int **rotated_rotors = NULL;
                        // Assign an approproate value to rotate_rotors by calling rotate_rotors
                        rotated_rotors = rotate_rotors(num_of_rotations,
                                                       rotor_set, num_rows, ALPHA);

                        printf("%s\n", ROTOR_AFTER_ROTATION);

                        //freeing malloc memmory for rotor_set
                        


                        // Display the rotated rotors by calling display_rotor_configuration
                        display_rotor_configuration(rotated_rotors, num_rows, ALPHA);

                        // Prompt the user to input message to encrypt/decrypt and display
                        // the encrypted/decrypted message.
                        if (ret == 2)
                        {
                                printf("%s", USER_PROMPT1);
                                char message[100];

                                // Read the message input by user

                                //get the message
                                fgets(message, 100, stdin);
                                fgets(message, 100, stdin);

                                printf("ENCRYPTED MESSAGE: ");

                                // Encrypt the user message by calling encrypt
                                char *code = encrypt(message, rotated_rotors, num_rows, ALPHA);

                                // Display the encrypted message
                                printf("%s", code);
                                free(code);
                        }
                        else
                        {
                                printf("%s", USER_PROMPT2);
                                char message[100];

                                // Read the message input by user

                                //get the message
                                fgets(message, 100, stdin);
                                fgets(message, 100, stdin);

                                printf("DECRYPTED MESSAGE: ");

                                // Decrypt the user message by calling decrypt
                                char *decode = decrypt(message, rotated_rotors, num_rows, ALPHA);

                                // Display the decrypted message
                                printf("%s", decode);
                                free(decode);
                        }
                        break;

                default:
                        // Otherwise print the wrong option message.
                        printf("%s\n", WRONG_OPTION);
                        break;
                }
        }

        return 0;
}
