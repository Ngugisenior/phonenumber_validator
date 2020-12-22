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
    //printf("\n%d",count);
    if(count == strlen(symbols)){
        return 1;
    } else{
        return 0;
    }
}

int get_country_code(char * parsed_elem){
    char  ptr_code [4];
    char  * ptr_ = malloc(4);
    char * ptr__ = malloc(4);
    char *  ptr_r = malloc(4);
    // country code can never be greater than 4 characters
    memcpy(ptr_code, parsed_elem, strlen(parsed_elem)-9);


    ptr_ = strchr(ptr_code,'+'); //first occurrence
    memcpy(ptr_r,ptr_+1,strlen(ptr_)+1-1);

    ptr__ = strrchr(ptr_code,'+'); //last occurrence

    if(
            (ptr_ == NULL && strlen(ptr_r) <4) ||
            (ptr_ != NULL && strlen(ptr_code) <=4 && strlen(ptr_) == strlen(ptr__) ) ){
        return 1;
    }
    else{
        return 0;
    }
}

int get_phone_number(char * number){
    char * ptr_num = malloc(20);
    memcpy(ptr_num,number+(strlen(number)-9),strlen(number)-(strlen(number)+1-10));

    if(strlen(ptr_num) <= 9){
        free(ptr_num);
        return 1;
    }
    else{
        free(ptr_num);
        return 0;
    }

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
        printf("\nThe phone number's country code is invalid ==> %s",ptr_code);
        exit(EXIT_FAILURE);
    }
    else if(number != 1){
        memcpy(ptr_num,num+(strlen(num)-9), strlen(num)-(strlen(num)+1-8));
        printf("\nThe phone number's country code is invalid ==> %s",ptr_num);

        free(ptr_num);
        free(ptr_code);
        exit(EXIT_FAILURE);
    }
    else{
        printf("\nThe  Number ==> %s is a valid phone number! ",num);

        free(ptr_num);
        free(ptr_code);
        exit(EXIT_SUCCESS);
    }
}

void val_check(char * num){

    int symbol = eliminate_symbols(num);

    int code = get_country_code(num);

    int number = get_phone_number(num);

    validate_phone_number(symbol,code,number, num);
}
