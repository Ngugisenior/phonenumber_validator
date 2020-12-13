#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char  symbols[10] = {'/','*','-','~','!','#','.'};

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
    char * ptr_code = malloc(strlen(parsed_elem) -9);
    char * first_plus = malloc(4);
    char * last_plus = malloc(4);
    int len = strlen(parsed_elem)-9;
    // country code can never be greater than 4 characters
    memcpy(ptr_code, parsed_elem, len);
    len = strnlen(ptr_code,4);

    first_plus = strchr(ptr_code,'+');
    last_plus = strrchr(ptr_code,'+');

    if(len <= 4){
            if(strchr(ptr_code,'+') != NULL){
                if(strnlen(ptr_code,4)<=4){
                    if(strnlen(first_plus,4) == strnlen(last_plus,4)){
                        val = 1;
                    }
                }
            }
            else{
                if(strnlen(ptr_code,4) < 4){
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
    int val = 0 //return code
    char * ptr_num = malloc(20);
    memcpy(ptr_num,number+(strlen(number)-9),strlen(number)-(strlen(number)+1-10));

    if(strnlen(ptr_num,9) <= 9){
        free(ptr_num);
        val = 1;
    }
    else{
        free(ptr_num);
        val = 0;
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
    if(strnlen(num,9)>=9){
        int symbol = eliminate_symbols(num);

        int code = get_country_code(num);

        int number = get_phone_number(num);

        validate_phone_number(symbol,code,number, num);
    }
    else{
        printf("The phone number is too small to be a valid phone number! ===> %s", num);
        exit(EXIT_FAILURE);
    }

}
