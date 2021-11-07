// crt_isatty.c
/* This program checks to see whether
* stdin is piped or not.
* Check with: echo 9.12 4 | io_stdin_check    (bash environment at UNIX/WIN32)
*             io_stdin_check
*/

#include <stdio.h>
#include <io.h>
int main()
{

  if (_isatty(_fileno(stdin)))
    printf("No stdin\n");
  else
  {
    printf("Piped stdin\n");
    char str[100];
    int i;

    scanf("%s %d", str, &i);

    printf("You entered: %s %d ", str, i);

    /* fgets version */
    //  char *text = calloc(1, 1), buffer[100];
    // printf("Enter a message: \n");
    // while (fgets(buffer, 100, stdin)) /* break with ^D or ^Z */
    // {
    //   text = realloc(text, strlen(text) + 1 + strlen(buffer));
      // if( !text ) ... /* error handling */
      // strcat(text, buffer); /* note a '\n' is appended here everytime */
      // printf("%s", buffer);
    // }
    // printf("\ntext:\n%s", text);
  }

  return 0;
}