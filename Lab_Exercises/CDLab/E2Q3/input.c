#include <stdio.h>

int main() {
    int x = 5;
    char ch = 'A';
    double pi = 3.14159;
    
    switch (x) {
        case 1:
            printf("One\n");
            break;
        case 2:
            printf("Two\n");
            break;
        default:
            printf("Other\n");
    }
    
    for (int i = 0; i < 5; i++) {
        if (i % 2 == 0) {
            continue;
        }
        printf("Odd number: %d\n", i);
    }
    
    return 0;
}
