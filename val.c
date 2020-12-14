#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char  symbols[10] = {'/','*','-','~','!','#','.'}; // symbols that a phone number should not contain

int eliminate_symbols(char * parsed_elem){

    int count = 0;

    for(int i = 0; i< strlen(symbols); i++){
        if(strchr(parsed_elem,symbols[i]) == NULL){
            count = count+1;
        }
        else{
            count = 0;
        }
    }
    if(count == strlen(symbols)){
        return 1;
    } else{
        return 0;
    }
}

int get_country_code(char * parsed_elem){

    int val = 0; //return code

    char * ptr_code = malloc(strlen(parsed_elem) -9);// allocating memory to hold the extracted country code;
    char * first_plus = malloc(4); // allocating the memory to store the string after the first occurrence of the first + symbol
    char * last_plus = malloc(4); // allocating the memory to store the string after the last occurrence of the last + symbol
    int len = strlen(parsed_elem)-9; // initializing the length of the country code
    // country code can never be greater than 4 characters
    memcpy(ptr_code, parsed_elem, len); // extracting the country code from the parsed string using the memcpy function
    len = strnlen(ptr_code,4); // getting the actual length of the parsed string

    first_plus = strchr(ptr_code,'+'); // getting the string after the first occurrence of the first (+) symbol
    last_plus = strrchr(ptr_code,'+');// getting the string after the last occurrence of the last (+) symbol

    if(len <= 4){ // checking if the length of the country code is greater than 4
            if(strchr(ptr_code,'+') != NULL){ // checking that the country code contains a (+) symbol
                if(strnlen(ptr_code,4)<=4){ // checking that the maximum expected length of the country code containing a (+) symbol is 4
                    if(strnlen(first_plus,4) == strnlen(last_plus,4)){ // checking to ensure that the country code contains only a single (+) symbol by comparing the length of the string after the first occurrence of the first (+) symbol and the length of the string after the last occurrence of the last (+) symbol
                        val = 1;
                    }
                }
            }
            else{
                if(strnlen(ptr_code,4) < 4){ // checking if the length of the country code without the (+) symbol is less than 4
                    val =  1;
                }

            }
    }
    else{
        val = 0;
    }
     return val;
}

int get_phone_number(char * number){
    int val = 0 ;//return code

    int len = strlen(number)-9; // length of the maximum expected country code
    char * ptr_code = malloc(strlen(number) -9); // allocating memory for holding the country code;
    memcpy(ptr_code, number, len); // extracting the country code from the parsed string
    len = strnlen(ptr_code,4); // Length of the country code

    char * ptr_num = malloc(20); //allocating memory for holding the phone number
    memcpy(ptr_num,number+(strlen(number)-9),strlen(number)-(strnlen(number,13)-9)); // extracting the last 9 digits of a phonenumber


    if((len+strnlen(ptr_num,9)) == strlen(number)){ // checking that the length of the country code and the length of the phone number add up to the length of the parsed string
        if(strnlen(ptr_num,9) <= 9){ // checking if the length of the extracted phone number is greater than 9
            free(ptr_num);
            val = 1;
        }
        else{
            free(ptr_num);
            val = 0;
        }
    }
    return val;
}

void validate_phone_number(int symbol,int code, int number, char * num){
    char * ptr_code = malloc(10);
    char * ptr_num = malloc(12);
    if(symbol != 1){
        printf("\nThe phone number contains one of the following characters ==> %s",symbols);
        exit(EXIT_FAILURE);
    }
    else if(code != 1){
        memcpy(ptr_code,num,strlen(num)+1-9);
        printf("\nThe phone number's country code is invalid ==> %d",get_country_code(num));
        exit(EXIT_FAILURE);
    }
    else if(number != 1){
        memcpy(ptr_num,num+(strlen(num)-9), strlen(num)-(strnlen(num,9)-9));
        printf("\nThe phone number's country code is invalid ==> %s",ptr_num);

        free(ptr_num);
        free(ptr_code);
        exit(EXIT_FAILURE);
    }
    else{
           if((strlen(num)-9)==0){
            printf("\n\nPhone number is valid but does not contain a country code! ==> %s",num);
           }
           else{
             printf("\nThe  Number ==> %s is a valid phone number! ",num);
           }

        free(ptr_num);
        free(ptr_code);
        exit(EXIT_SUCCESS);
    }
}

void val_check(char * num){
    if(strnlen(num,9)>=9){ // checking that the parsed string is not less than 9
        int symbol = eliminate_symbols(num); // Checking whether the parsed string contains any symbol

        int code = get_country_code(num);// extracting and validating the country code

        int number = get_phone_number(num);// extracting and validating the phone number

        validate_phone_number(symbol,code,number, num); // checking whether the phone number meets all the minimum requirements
    }
    else{
        printf("The phone number is too small to be a valid phone number! ===> %s", num);
        exit(EXIT_FAILURE);
    }

}
