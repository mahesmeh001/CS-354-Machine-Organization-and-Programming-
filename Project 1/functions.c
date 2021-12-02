/******************************************************************************
 * @file: functions.c
 *
 * NET ID: MMAHESHWARI2
 * CANVAS USERNAME; MEHUL MAHESHWARI
 * WISCID: 9082250664
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: YOUR PREFERED NAME (YOUR WISC EMAIL)
 * @modified: SUBMISSION DATE
 *****************************************************************************/
#include <stdio.h>
#include "functions.h"

// Some macros that may be useful to you 
#define MAX_USERNAME_LEN    32
#define MAX_EMAIL_LEN       32
#define MAX_DOMAIN_LEN      64
#define MIN_PASSWORD_LEN    8
#define MAX_PASSWORD_LEN    16
#define NEW_LINE_CHAR       10

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
// Examples: IsLetter, IsDigit, Length, Find...

/**
 * @param e: the character that we check whether is a letter
 * @returns a 1 if it is a letter, 0 otherwise
 */
int IsLetter(char e){
    //use ASCII values of the character to check whether it falls in the alphabet
    if( (e>= 60 && e<= 90) || (e>= 97 && e<= 122))
        return 1;
    return 0;
}

/**
 * finds the length, not size, of the array
 * @param user: the array input
 * @param MAX: the array size given on initialization
 * @returns the length of the array
 */
int Length(const char user[],int MAX){
    int len=0;
    for(int i =0; i<MAX;i++){
        if(user[i]!='\0')
            len++;
        else
            break;
    }
    //subtract one to account for newline character
    return len;
}

/**
 * checks whether the characters in the array are valid (for the username)
 * @param user: the array
 * @param length: the length of the array
 * @returns a 0 if not valid, 1 if valid
 */
int userValidity(char user[], int length){
    for (int i = 0; i<length; i++){
        //if not a letter, underscore, or digit than return 0
        if (!(IsLetter(user[i])==1||user[i]==95||(user[i] >= 48 && user[i] <= 57)))
            return 0;
    }
    //otherwise valid, and return 1
    return 1;
}

/**
 * checks to make sure no spaces
 * @param user is the array
 * @param length is the length of the array
 * @return 1 if there are spaces, 0 if not
 */
int checkSpaces(const char user[], int length){
    for (int i = 0; i<length; i++){
        //check for spaces
        if(user[i]==' ')
            return 1;
    }
    return 0;
}

/**
 * checks for capital letter
 * @param array
 * @param length
 * @returns a 1 if a capital is found, and a 0 if not
 */
int checkCaps(const char array[], int length){
    for (int i = 0; i<length;i++){
        //if there is a single capital, return 1
        if (array[i]>= 60 && array[i] <= 90)
            return 1;
    }
    return 0;
}

/**
 * checks for lowercase letter
 * @param array
 * @param length : length of array
 * @returns a 1 if a lowercase is found, and a 0 if not
 */
int checkLowers(const char array[], int length){
    for (int i = 0; i<length;i++){
        //if there is a single capital, return 1
        if (array[i]>= 97 && array[i] <= 122)
            return 1;
    }
    return 0;
}

/**
 * Checks for the @ symbol
 * @param array
 * @param length
 * @returns index of symbol if found, 0 if not
 */
int symbolChecker(const char array[], int length){
    for(int i = 0; i<length; i++){
        if (array[i]==64)
            return i;
    }
    return 0;
}


/******************************************************************************
 * Verification functions
 *****************************************************************************/

/*
 * A username must begin with a letter [A-Z, a-z], contain 32 characters
 * or less, and  may only consist of letters, underscores, or 
 * digits [A-Z, a-z, _, 0-9]. An error message is displayed if any of 
 * these conditions are not met. Only print the first applicable error 
 * message. 
 *
 * @param user : The username string
 * @param len : Size of the username input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Username(char user[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    int length = Length(user,(int)len);

    //dbgprintf("%d\n", Length(user,(int)len))



    if(IsLetter(user[0])==0){
        printf(ERROR_01_USER_START_INVALID);
        return 0;
    }

    else if(length>32){
        printf(ERROR_02_USER_LEN_INVALID);
        return 0;
    }

    else if (userValidity(user, length)==0){
        printf(ERROR_03_USER_CHARS_INVALID);
        return 0;
    }

    else
        printf(SUCCESS_1_USER);
    return 1;

/* END MODIFYING CODE HERE */

}


/*
 * An email address has four parts:
 *      name
 *          exists
 *          must start with letter
 *          max 32 characters
 *          may contain only letters and digits
 *      @ symbol
 *          exists
 *      domain name
 *          exists
 *          max of 64 characters
 *          composed of one or more subdomains separated by .
 *          subdomain must begin with a letter
 *          subdomains may contain only letters and digits
 *      top-level domain 
 *          must be [.edu, .com, .net]
 *
 * If the email address contains one or more errors print only the first
 * applicable error from the list.
 *
 * Note this task is based on a real world problem and may not be the best 
 * order to approach writing the code.
 *
 * @param email : The email string
 * @param len : Size of the email input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Email(char email[], size_t len) {
    //length of email
    int length = Length(email, (int)len);

    /* BEGIN MODIFYING CODE HERE */
    if(email[0]=='@'||length==0){
        printf(ERROR_04_EMAIL_MISSING_NAME);  // example @domain.com
        return 0;
    }

    if(IsLetter(email[0])==0){
        printf(ERROR_05_EMAIL_START_INVALID);
        return 0;
    }

    //index of the @ symbol (further explained/demonstrated in the method description)
    int symbol = symbolChecker(email,length);
    if(symbol!=0){
        if (symbol>32){
            printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
            return 0;
        }

        for (int i = 0; i < symbol; i ++){
            //if there is not a letter or digit in the name, print error
            if (!( IsLetter(email[i])==1 || (email[i] >= 48 && email[i] <= 57) )){
                printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
                return 0;
            }
        }
    }
    else if(symbol==0){

        if (email[0]!='@'){
            printf(ERROR_08_EMAIL_MISSING_SYMBOL); // example mike.wisc.edu
            return 0;
        }

        if (length>32){
            printf(ERROR_06_EMAIL_NAME_LEN_INVALID);
            return 0;
        }
        for (int i = 0; i<length; i++){
            if (!( IsLetter(email[i])==1 || (email[i] >= 48 && email[i] <= 57) )){
                printf(ERROR_07_EMAIL_NAME_CHARS_INVALID);
                return 0;
            }
        }
    }



    if(symbol==(length-5)){
        printf(ERROR_09_EMAIL_MISSING_DOMAIN); // example mike@.edu
        return 0;
    }

    if ((length-symbol-5)>64){
        printf(ERROR_10_EMAIL_DOMAIN_LEN_INVALID);
        return 0;
    }

    //subdomains and domain have to start w a letter

    //checks domain starts w a letter
    if (IsLetter(email[symbol+1])==0){
        printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
        return 0;
    }

    for(int i = symbol; i<(length-4);i++) {
        //check subdomains begin w a letter
        if(email[i-1]==46){
            if(IsLetter(email[i])==0){
                printf(ERROR_11_EMAIL_DOMAIN_START_INVALID);
                return 0;
            }
        }
    }

    for(int i = symbol; i<(length-4);i++) {
        //if not a letter or digit (or period) than print error
        if(!(IsLetter(email[i])||email[i]=='.'||(email[i]>=48&&email[i]<=57))){
            printf(ERROR_12_EMAIL_DOMAIN_CHARS_INVALID);
            return 0;
        }
    }

    int checker = 0;
    if (email[length-4]=='.'&&email[length-3]=='c'&&email[length-2]=='o'&&email[length-1]=='m')
        checker = 1;
    else if(email[length-4]=='.'&&email[length-3]=='n'&&email[length-2]=='e'&&email[length-1]=='t')
        checker = 1;
    else if(email[length-4]=='.'&&email[length-3]=='e'&&email[length-2]=='d'&&email[length-1]=='u')
        checker = 1;

    if(checker!=1){
        printf(ERROR_13_TOP_LEVEL_DOMAIN_INVALID);
        return 0;
    }
    /* END MODIFYING CODE HERE */
    
    printf(SUCCESS_2_EMAIL);
    return 1;
}

/*
 * The following password requirements must be verified:
 *  - May use any character except spaces (i.e., "my password" is invalid)
 *  - Must contain at least 8 characters (i.e., "Password" has 8 characters 
 *    and is valid)
 *  - May have at most 16 characters (i.e., "1234567890Abcdef" has 16 
 *    characters and is valid)
 *  - Must contain at least one upper case character [A-Z]
 *  - Must contain at least one lower case character [a-z]
 *
 * @param pwd : The original password string
 * @param len : Size of the original password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Password(char pwd[], size_t len) {

    /* BEGIN MODIFYING CODE HERE */
    int length = Length(pwd,(int) len);


    if(checkSpaces(pwd,length)==1){
        printf(ERROR_14_PWD_SPACES_INVALID);
        return 0;
    }

    else if(length<8){
        printf(ERROR_15_PWD_MIN_LEN_INVALID);
        return 0;
    }
    else if (length>16){
        printf(ERROR_16_PWD_MAX_LEN_INVALID);
        return 0;
    }

    else if (checkCaps(pwd, length)==0){
        printf(ERROR_17_PWD_MIN_UPPER_INVALID);
        return 0;
    }
    else if (checkLowers(pwd,length)==0){
        printf(ERROR_18_PWD_MIN_LOWER_INVALID);
        return 0;
    }

    /* END MODIFYING CODE HERE */

    return 1;
}
/*
 * Original Password and the Reentered Password must match
 *
 * @param pwd1 : The original password string
 * @param len1 : Size of the original password input buffer
 * @param pwd2 : The reentered password string
 * @param len2 : Size of the renetered password input buffer
 * @return 1 if valid, 0 if not
 */
int Verify_Passwords_Match(char pwd1[], size_t len1, char pwd2[], size_t len2) {
    /* BEGIN MODIFYING CODE HERE */


    int length1 = Length(pwd1, (int)len1);
    int length2 = Length(pwd2, (int)len2);

    if (length1!=length2){
        printf(ERROR_19_PWD_MATCH_INVALID);
        return 1;
    }

    //CHANGE
    for (int i = 0; i<length1;i++){
        int e=i;
        if (pwd1[i]!=pwd2[e]){
            printf(ERROR_19_PWD_MATCH_INVALID);
            return 0;
        }
    }
    /* END MODIFYING CODE HERE */

    printf(SUCCESS_3_PASSWORDS);
    return 1;
}

/******************************************************************************
 * I/O functions
 *****************************************************************************/

/*
 * Prompts user with an input and reads response from stdin
 *
 * @param message : Prompt displayed to the user
 * @param data : char array to hold user repsonse
 * @param MAX_LENGTH : Size of user response input buffer
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    /* BEGIN MODIFYING CODE HERE */

    //search for \n, replace w \0
    int i;
    for(i=0; data[i]; i++);
    data[i-1]='\0';

    //everything after that becomes \0
    for(; i<MAX_LENGTH; i++){
    data[i]='\0';
    }

    //clear out the damn stuff afterwards
    /* END MODIFYING CODE HERE */
}
