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
  }

  return 0;
}