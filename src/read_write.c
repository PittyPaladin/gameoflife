#include <stdio.h>
#include <stdlib.h>

void write_to_disk (const char* filename)
{
    // Overwrites file if filename already exists
    
    FILE* fileptr = fopen(filename, "w");
    if (fileptr == NULL)
    {
        printf("Error");
        exit(EXIT_FAILURE); // exit(EXIT_FAILURE)==exit(1), but is more portable
    }

    // To print text
    const char* content = "Sample content";
    fprintf(fileptr, "Some text: %s\n", content);

    // To print integers and floats
    int i = 1;
    float pi = 3.1415927;
    fprintf(fileptr, "Integer: %d, float: %f\n", i, pi);

    // Printing chars
    char c = 'A';
    fprintf(fileptr, "A character: %c\n", c);

    // Close file stream
    fclose(fileptr);


}

int main () 
{
    write_to_disk("info.txt");



    return 1;
}