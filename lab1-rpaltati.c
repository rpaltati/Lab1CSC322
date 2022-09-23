#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encrypt(char* token) {
    int i = 0;
    int value;
    int new;
    while(token[i] != '\0' && strlen(token) > i) {
        value = ((int)token[i] - 97 + 3) + 97;
        new = (char)(value);
        printf("%c", new);
        i++;
    }
    printf("\n");
}

void decrypt(char* token) {
    int i = 0;
    int value;
    int new;
    while(token[i] != '\0' && strlen(token) > i) {
        value = ((int)token[i] + 97 - 3) - 97;
        new = (char)(value);
        printf("%c", new);
        i++;
    }
    printf("\n");
}

char* helper(char* plainText) {
    printf("rpaltati $ ");
    return fgets(plainText, 126, stdin);
}

int main() {

    char *userString;
    char plainText[127];
    char encryption[8] = "encrypt";
    char decryption[8] = "decrypt";
    char encode1[7] = "encode";
    char decode1[7] = "decode";
    char begParent[] = "(";
    char endParent[] = ")";
    char subUserString[16];
    char extraSubUserString[16];
    char end[2];
    char beg[2];
    char *beginning;
    char *ending;
    char exitCode[8] = "exit\n";
    int length = 7;
    int extraLength = 6;
    char inside[127];
    char extraInside[127];
    int index;

    while(userString = helper(plainText)) {

        //check if user types exit
        if(strcmp(userString, exitCode) == 0) {
            exit(0);
        }

        if(strlen(userString) < 7) {
            printf("ERROR\n");
            continue;
        }

        //Copies either encrypt or decrypt to subUserString by getting the first 7 chars in userString
        strncpy(subUserString, userString, length);
        //UserString: %s \n", subUserString);

        //Copies either encode or decode to extraSubUserString by getting the first 6 char in userString
        strncpy(extraSubUserString, userString, extraLength);
        //printf("extra: %s \n", extraSubUserString);

        //Get ( and check if user inputted it
        beginning = strchr(userString, '(');

        if (beginning == NULL) {
            printf("ERROR 1\n");
            continue;
        }

        //Get ) and check if user inputted it
        ending = strchr(userString, ')');

        if (ending == NULL) {
            printf("ERROR 2\n");
            continue;
        }

        if(beginning > ending) {
            printf("ERROR 3\n");
            continue;
        }

        index = (int)((beginning - 1) - userString);

        //Only get (
        strncpy(beg, beginning, 1);
        beg[sizeof beg - 1] = '\0';

        //Only get )
        strncpy(end, userString + (strlen(userString) - 2), 1);
        end[sizeof end - 1] = '\0';

        //Getting the plain text that is inside
        strncpy(inside, userString + 8, ((strchr(userString, ')') - (strchr(userString, '(')) - 1)));
        //printf("Inside: %s \n", inside);
        end[sizeof inside - 2] = '\0';

        //Extra Credit: Getting the plain text that is inside
        //Fill it with nulls extraInside
        for(int i=0;i <= 127; i++) {
            extraInside[i] = '\0';
        }

        strncpy(extraInside, userString + 7, ((strchr(userString, ')') - (strchr(userString, '(')) - 1)));
        //printf("Extra Inside: %s \n", extraInside);

        // Check if there is () at the end and if user typed in encrypt
        if(strcmp(encryption, subUserString) == 0 && strcmp(endParent, end) == 0 && strcmp(begParent, beginning)) {

            //tokenization
            char *token = strtok(userString, "(\n");
            while( token != NULL) {
                if (strcmp(token, subUserString) != 0) {
                    encrypt(token);
                }
                token = strtok(NULL, "()");
            }
        }

        else if(strcmp(decryption, subUserString) == 0 && strcmp(endParent, end) == 0 && strcmp(begParent, beginning)) {

            //tokenization
            char *token = strtok(userString, "(\n");
            while( token != NULL) {
                if (strcmp(token, subUserString) != 0) {
                    decrypt(token);
                }
                token = strtok(NULL, "()");
            }
        }

            // Extra Credit: See for encode
        else if(strcmp(encode1, extraSubUserString) == 0 && strcmp(endParent, end) == 0 && strcmp(begParent, beginning)) {

            //Get the length of extraInside
            int value = strlen(extraInside);

            //printf("%d\n", value);
            int num = value * 8;
            //printf("%d\n", num);

            //Create a char array using the num as the size. Create position to start at the end of the array
            int size = num;
            //printf("%d\n", size);

            int encodeInside[8];

            for(int i=0;i<8;i++){
                encodeInside[i]=0;
            }

            int position = (sizeof(encodeInside) / sizeof(encodeInside[0])) - 1;
            //printf("%d\n", position);


            //tokenization
            int i = 0;
            char *token = strtok(userString, "(\n");
            //printf("This is inside the token: %s\n", token);
            while (token != NULL) {

                if (strcmp(token, extraSubUserString) != 0) {
                    while(token[i] != '\0' && strlen(token) > i) {
                        int asciiValue;

                        asciiValue = (int) token[i];
                        //printf("VALUE: %d\n", asciiValue);

                        //Loop to get the 1s or 0s
                        int c = 7;
                        int x = 7;
                        while (c >= 0) {

                            if((asciiValue % 2) & 1) {
                                encodeInside[x] = 1;
                                //printf("1");
                            }
                            else {
                                encodeInside[x] = 0;
                                //printf("0");
                            }
                            asciiValue = asciiValue >> 1;
                            x--;
                            c--;
                            //printf("New Position: %d\n", position);
                            //asciiValue = asciiValue >> 1;
                        }
                        for(int i=0; i < 8; i++) {
                            printf("%d" , encodeInside[i]);
                        }

                        for(int i=0;i<8;i++){
                            encodeInside[i]=0;
                        }
                        i++;
                    }
                }
                token = strtok(NULL, "()");
            }

            printf("\n");
        }

        else {
            printf("ERROR 4\n");
        }

    }
    return 0;
}

