#include <stdio.h>


int concat(char* str1 ,const char* str2){

    int idx = 0;
    while(1){
        if (str1[idx] == '\0'){
            break;
        }
    idx++;
    }
    int point_str2 = 0;
    while(1){
        str1[idx + point_str2] = str2[point_str2];
        if (str2[point_str2] == '\0'){
            break;
        }
        point_str2++;
    }
    printf("The string is: %s",str1);
}

int main()
{
    char str1[100] = "hello";
    char* str2 = "world";
    concat(str1,str2);
    return 0;
}
