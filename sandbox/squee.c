#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    // Create a file if we don't have one all ready
    // otherwise, just open that file
    
    printf("file %s \n", argv[1]);    
    open(argv[1], O_RDWR | O_CREAT);
}
