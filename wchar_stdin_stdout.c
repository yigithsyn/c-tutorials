#include <stdio.h>
#include <direct.h>

int main()
{
  int result;
  wchar_t input[256];
  printf("Enter a Turkish sentence: ");
  result = wscanf(L"%ls", input); // C4996
  wprintf(L"The number of fields input is %d\n", result);
  wprintf(L"Field value is %ls\n", input);
  return 0;
}