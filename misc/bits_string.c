#include "bits_string.h"


void string_to_lower(char *c) {
    if(c == 0) return;
    while(*c != 0){
        if((*c >= 'A') || (*c <= 'Z')) *c += 'a' - 'A';
        c++;
    }
}

char char_to_lower(char c) {
    if((c >= 'A') || (c <= 'Z')) c += 'a' - 'A';
    else return c;
}