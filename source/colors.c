#define red     "\x1b[31m"
#define green   "\x1b[32m"
#define yellow  "\x1b[33m"
#define blue    "\x1b[34m"
#define magenta "\x1b[35m"
#define cyan    "\x1b[36m"
#define white   "\x1b[0m"


void printColor (char* output, char* color) {

    if (strcmp (color, "red")     == 0) printf (red "%s",     output);
    if (strcmp (color, "green")   == 0) printf (green "%s",   output);
    if (strcmp (color, "yellow")  == 0) printf (yellow "%s",  output);
    if (strcmp (color, "blue")    == 0) printf (blue "%s",    output);
    if (strcmp (color, "magenta") == 0) printf (magenta "%s", output);
    if (strcmp (color, "cyan")    == 0) printf (cyan "%s",    output);

    printf (white "\n\n");
}