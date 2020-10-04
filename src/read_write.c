#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

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

int check_printable(char* str)
{
    /* Return 1 if printable, 0 if not */
    int printable = 1;
    int ascii, valid_char;
    // printf("%d\n", (int) *str == 97 || (int) *str == 96);
    while (*str != '\0')
    {
        ascii = (int) *str;
        valid_char = ascii == 48 || ascii == 49 || ascii == 50 || ascii == 51
                  || ascii == 52 || ascii == 53 || ascii == 54 || ascii == 55
                  || ascii == 56 || ascii == 57 || ascii == 65 || ascii == 66
                  || ascii == 67 || ascii == 68 || ascii == 69 || ascii == 70
                  || ascii == 71 || ascii == 72 || ascii == 73 || ascii == 74
                  || ascii == 75 || ascii == 76 || ascii == 77 || ascii == 78
                  || ascii == 79 || ascii == 80 || ascii == 81 || ascii == 82
                  || ascii == 83 || ascii == 84 || ascii == 85 || ascii == 86
                  || ascii == 87 || ascii == 88 || ascii == 89 || ascii == 90
                  || ascii == 97 || ascii == 98 || ascii == 99 || ascii == 100
                  || ascii == 101 || ascii == 102 || ascii == 103 || ascii == 104
                  || ascii == 105 || ascii == 106 || ascii == 107 || ascii == 108
                  || ascii == 109 || ascii == 110 || ascii == 111 || ascii == 112
                  || ascii == 113 || ascii == 114 || ascii == 115 || ascii == 116
                  || ascii == 117 || ascii == 118 || ascii == 119 || ascii == 120
                  || ascii == 121 || ascii == 122 || ascii == 46;
        
        if (!valid_char) {
            printable = 0;
            break;
        }
        ++str;
    }

    return printable;
}

void parsefn (int argc, char* argv[])
{
    // Initialize pointer where filename will be stored.
    char* fname = NULL;
    /* Disable automatic error messages from getopt. We will display custom 
    error messages.*/
    opterr = 0;
    int printable;
    
    int c;
    while( (c = getopt(argc, argv, "f:")) != -1 )
    {
        switch(c)
        {
            case 'f':
                fname = optarg;
                printable = check_printable(fname);
                printf("printable %d\n", printable);
                if (!printable)
                    exit(EXIT_FAILURE);
                break;
            case '?':
                /* In case flag is properly set but no value to it is provided by the 
                user. Note: optopt is the command line option last matched */
                if (optopt == 'f') {
                    fprintf(stderr, "Flag -%c requires an argument. \n", optopt);
                    exit(EXIT_FAILURE);
                }
                // If you really don't know what has been passed, defer to this.
                else {
                    fprintf(stderr, "I don't know wtf you typed. \n");
                    exit(EXIT_FAILURE);
                }
            default:
                exit(EXIT_FAILURE);
        }
    }

}

int main (int argc, char* argv[]) 
{
    // write_to_disk("info.txt");
    parsefn(argc, argv);

    printf("%s \n", argv[2]);



    return 1;
}