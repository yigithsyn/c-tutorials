#include <stdio.h>
#include <string.h>
#include <jansson.h>

int main()
{

  json_t *json = NULL, *json1 = NULL, *json2 = NULL, *json3 = NULL, *json4 = NULL, *njson = NULL;
  json_error_t error;
  char *bufc = NULL;
  fprintf(stdout, "\n- Read & Write JSON File\n");

  char filename[] = "object.json";
  char filepath[256] = {'\0'};

  sprintf(filepath, "%s/%s", ASSETS_DIR, "object.json");
  printf("Using sample object from file: \"%s\".", filepath);

  printf("\n-- Parsing file contents ... ");
  json = json_load_file(filepath, 0, &error);
  if (!json)
  {
    fprintf(stderr, "Failed: on line %d: %s", error.line, error.text);
    exit(1);
  }
  fprintf(stdout, "Passed.");

  fprintf(stdout, "\n-- Check for valid json ... ");
  if (!json_is_array(json) && !json_is_object(json))
  {
    fprintf(stdout, "Failed.");
    json_decref(json);
    exit(1);
  }
  fprintf(stdout, "Passed.");

  fprintf(stdout, "\n-- Check wheter array or object ... ");
  if (json_is_array(json))
    fprintf(stdout, "Array.");
  else
    fprintf(stdout, "Object.");
  printf("\n");

  /* Get */
  char key[] = "quiz.sport.q1.options";
  char *keyc = malloc(strlen(key) + 1);
  strcpy(keyc, key);
  char delim[] = ".";
  /* get the first token */
  char *token = strtok(keyc, delim);

  /* walk through other tokens */
  json1 = json;
  printf("[Object]");
  while (token != NULL)
  {
    printf(".%s", token);
    json1 = json_object_get(json1, token);
    token = strtok(NULL, delim);
  }
  bufc = json_dumps(json1, JSON_INDENT(2));
  printf("\n%s\n", bufc);
  free(bufc);
  free(keyc);

  /* Set */
  json1 = json;
  keyc = malloc(strlen(key) + 1);
  strcpy(keyc, key);
  token = strtok(keyc, delim);
  while (token != NULL)
  {
    json1 = json_object_get(json1, token);
    token = strtok(NULL, delim);
  }
  if (json_is_array(json1))
  {
    bufc = json_dumps(json1, JSON_INDENT(2));
    printf("\n%s\n", bufc);
    free(bufc);
    json_array_set(json1, 0, json_string("Chicago Bulls"));
    bufc = json_dumps(json1, JSON_INDENT(2));
    printf("\n%s\n", bufc);
    free(bufc);
  }
  free(keyc);

  // if (json_is_object(json))
  // {
  //   printf("\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ...");
  //   bufc = json_dumps(json, JSON_INDENT(2));
  //   printf("%s", bufc);
  //   free(bufc);
  //   printf("\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ... Check sub object 'quiz' ...");
  //   json1 = json_object_get(json, "quiz");
  //   if (!json_is_object(json1))
  //   {
  //     fprintf(stdout, "Failed.");
  //     json_decref(json);
  //     exit(1);
  //   }
  //   fprintf(stdout, "Passed.");

  //   fprintf(stdout, "\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ... Check sub object 'quiz.sport' ...");
  //   json2 = json_object_get(json1, "sport");
  //   if (!json_is_object(json2))
  //   {
  //     fprintf(stdout, "Failed.");
  //     json_decref(json);
  //     exit(1);
  //   }
  //   fprintf(stdout, "Passed.");

  //   fprintf(stdout, "\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ... Check sub object 'quiz.sport.q1' ...");
  //   json3 = json_object_get(json2, "q1");
  //   if (!json_is_object(json3))
  //   {
  //     fprintf(stdout, "Failed.");
  //     json_decref(json);
  //     exit(1);
  //   }
  //   fprintf(stdout, "Passed.");

  //   fprintf(stdout, "\n-- Edit json ... Editing nested key value 'quiz.sport.q1.question' ... Check key value 'quiz.sport.q1.question' ...");
  //   json3 = json_object_get(json2, "q1");
  //   if (!json_is_object(json3))
  //   {
  //     fprintf(stdout, "Failed.");
  //     json_decref(json);
  //     exit(1);
  //   }
  //   fprintf(stdout, "Passed.");

  //   printf("\n-- Edit json ... Updating nested key value 'quiz.sport.q1.question' ... Updating key value ...");
  //   bufc = json_dumps(json3, JSON_INDENT(2));
  //   printf("\nBefore: \n%s", bufc);
  //   free(bufc);

  //   if (json_object_set(json3, "question", json_string("New question?")) != 0)
  //   {
  //     printf("\nFailed.");
  //     json_decref(json);
  //     exit(1);
  //   }
  //   printf("\nPassed.");
  //   bufc = json_dumps(json3, JSON_INDENT(2));
  //   printf("\nAfter: \n%s", bufc);
  //   free(bufc);

  //   if (json_dump_file(json, "written.json", JSON_INDENT(2)) != 0)
  //   {
  //     printf("\nFailed.");
  //     json_decref(json);
  //     exit(1);
  //   }
  //   printf("\nPassed.");
  // }

  json_decref(json);

  return 0;
}