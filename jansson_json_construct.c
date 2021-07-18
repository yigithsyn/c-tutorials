#include <stdio.h>
#include <string.h>
#include <jansson.h>

int main()
{
  // json_error_t error;

  json_t *keyval, *val;
  json_t *obj = json_object();
  val = json_string("Hüseyin");
  json_object_set(obj, "name", val);
  val = json_string("YİĞİT");
  json_object_set(obj, "surname", val);
  keyval = json_object_get(obj, "name");
  if (!json_is_string(keyval))
  {
    fprintf(stderr, "error: json key value is not a string\n");
    // json_decref(root);
  }
  printf("name: %s\n", json_string_value(keyval));
  keyval = json_object_get(obj, "surname");
  if (!json_is_string(keyval))
  {
    fprintf(stderr, "error: json key value is not a string\n");
    // json_decref(root);
  }
  printf("surname: %s\n", json_string_value(keyval));
  json_decref(obj);

  return 0;
}