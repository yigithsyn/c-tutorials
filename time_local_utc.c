#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  char buf[20];
  time_t now;
  struct tm gm, lt;

  // Get current time
  time(&now);

  //UTC time
  gm = *gmtime(&now);
  strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &gm);
  printf("Buffer size: %d\n", strlen(buf));
  printf("UTC Time %s\n", buf);

  //Local time
  lt = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &lt);
  printf("Buffer size: %d\n", strlen(buf));
  printf("Local Time %s\n", buf);

  return 0;
}
