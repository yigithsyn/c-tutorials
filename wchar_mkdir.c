#include <stdio.h>
#include <direct.h>
#include <string.h>
#include <windows.h>
#include <stringapiset.h>

#define UTF8_PATH_MAX 256
#define UTF16_PATH_MAX 256

static void
mg_strlcpy(char *dst, const char *src, size_t n)
{
  for (; *src != '\0' && n > 1; n--)
  {
    *dst++ = *src++;
  }
  *dst = '\0';
}

static void
change_slashes_to_backslashes(char *path)
{
  int i;

  for (i = 0; path[i] != '\0'; i++)
  {
    if (path[i] == '/')
    {
      path[i] = '\\';
    }

    /* remove double backslash (check i > 0 to preserve UNC paths,
		 * like \\server\file.txt) */
    if ((i > 0) && (path[i] == '\\'))
    {
      while ((path[i + 1] == '\\') || (path[i + 1] == '/'))
      {
        (void)memmove(path + i + 1, path + i + 2, strlen(path + i + 1));
      }
    }
  }
}

/* Helper makros */
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif

int main()
{
  int result;
  char input[256] = "İçindekiler";
  // wchar_t input[256];
  // result = wscanf(L"%ls", input); // C4996
  // // printf("Enter a Turkish sentence: ");
  // // result = scanf("%s", input); // C4996
  // // printf("Field value is %s\n", input);

  char buf[UTF8_PATH_MAX], buf2[UTF8_PATH_MAX];
  wchar_t wbuf[UTF16_PATH_MAX];
  wchar_t wbuf2[UTF16_PATH_MAX + 1];

  mg_strlcpy(buf, input, sizeof(buf));

  memset(wbuf, 0, ARRAY_SIZE(wbuf) * sizeof(wchar_t));
  MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, (int)ARRAY_SIZE(wbuf));
  wprintf(L"Field value is %ls\n", wbuf);
  
  WideCharToMultiByte(
      CP_UTF8, 0, wbuf, (int)ARRAY_SIZE(wbuf), buf2, sizeof(buf2), NULL, NULL);
  if (strcmp(buf, buf2) != 0)
  {
    wbuf[0] = L'\0';
  }
  wprintf(L"Field value is %ls\n", wbuf);

  _wmkdir(wbuf);
  return 0;
}