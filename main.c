#include <stdio.h>

void val_check(char * num);
int main(int argc, char * argv[]){
    if(argc>1){
        val_check(argv[1]);
    }
}
