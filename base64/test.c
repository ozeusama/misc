#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"
#include "util.h"

void base64_test();

int main()
{
    base64_test();
    return 0;
}

void base64_test()
{
    char *string = "Man is distinguished, not only by his reason, but by this singular passion "
                   "from "
                   "other animals, which is a lust of the mind, that by a perseverance of delight "
                   "in "
                   "the continued and indefatigable generation of knowledge, exceeds the short "
                   "vehemence of any carnal pleasure.";
    char *pred =
            "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd"
            "1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIH"
            "RoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0a"
            "WdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2Yg"
            "YW55IGNhcm5hbCBwbGVhc3VyZS4=";
    b8 *a = (u8 *)string;
    size_t a_size = strlen(string);
    char *out = malloc(b8tobase64_malloc_size(a_size) + 1);
    b8tobase64(a, a_size, out);
    out[b8tobase64_malloc_size(a_size)] = '\0';
    size_t back_size = base64tob8_malloc_size(out);
    b8 *back = malloc(back_size);
    base64tob8(out, back);
    // find diff
    for (size_t i = 0; i < strlen(out) / 80 + 1; i++) {
        printf("SRC:  ");
        for (size_t j = 0; j < 60; j++) {
            if (60 * i + j < strlen(string)) {
                if (string[60 * i + j] != '\n') {
                    printf("%c", string[60 * i + j]);
                } else {
                    printf("\\");
                }
                if (j % 3 == 2) {
                    printf("_");
                }
            } else {
                break;
            }
        }
        printf("\nPRED: ");
        for (size_t j = 0; j < 80; j++) {
            if (80 * i + j < strlen(pred)) {
                printf("%c", pred[80 * i + j]);
            } else {
                break;
            }
        }
        printf("\nOUT:  ");
        for (size_t j = 0; j < 80; j++) {
            if (80 * i + j < strlen(out)) {
                printf("%c", out[80 * i + j]);
            } else {
                break;
            }
        }
        printf("\nBACK: ");
        for (size_t j = 0; j < 60; j++) {
            if (60 * i + j < back_size) {
                if (string[60 * i + j] != '\n') {
                    printf("%c", back[60 * i + j]);
                } else {
                    printf("\\");
                }
                if (j % 3 == 2) {
                    printf("_");
                }
            } else {
                break;
            }
        }
        printf("\n");
    }
    if (strcmp(pred, out) == 0) {
        printf("OUT == PRED: binary to base64 conversion successfull.\n");
    } else {
        printf("binary to base64 conversion failed!\n");
    }
    if (strncmp(string, (char *)back, back_size) == 0) {
        printf("BACK == OUT: reconversion from base64 to binary successfull.\n");
    } else {
        printf("reconversion from base64 to binary unsuccessfull!\n");
    }
}
