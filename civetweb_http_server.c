//==============================================================================
// Configuration
//==============================================================================
#define HTTP_PORT "3001"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "civetweb.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

static inline void SLEEP(int x)
{
#ifdef _WIN32
  Sleep(x * 1000);
#else
  sleep(x);
#endif
}

static int EXITNOW = 0;

int log_message(const struct mg_connection *conn, const char *message)
{
  printf("\n[CIVETWEB] {\"event\": \"error\", \"msg\": \"%s\"}", message);
  fflush(stdout);
  return 1;
}
//==============================================================================
// HTTP Handler
//==============================================================================
#pragma warning(disable : 4996)

int http_handler(struct mg_connection *conn, void *cbdata)
{

  const struct mg_request_info *ri = mg_get_request_info(conn);

  const char *folder = (const char *)cbdata;
  const char *file = strcmp(ri->local_uri, "/") == 0 ? "/index.html" : ri->local_uri;

  char *result = malloc(strlen(folder) + strlen(file) + 1); // +1 for the null-terminator
  // in real code you would check for errors in malloc here
  strcpy(result, folder);
  strcat(result, file);
  mg_send_file(conn, result);

  printf("[DEBUG] Static file served :  %s\n", result);
  // LOGGER(log);

  free(result);

  /* In this handler, we ignore the req_info and send the file "fileName". */
  return 1;
}

int main(int argc, char *argv[])
{
  /* options */
  const char *options[] = {"listening_ports", HTTP_PORT,
                           "request_timeout_ms",
                           "10000",
                           "error_log_file",
                           "error.log",
                           "enable_auth_domain_check",
                           "no",
                           0};

  struct mg_callbacks callbacks;
  struct mg_context *ctx;

  /* initialize */
  printf("[INFO] Initializing civetweb library ... ");
  fflush(stdout);
  if (mg_init_library(0))
  {
    fprintf(stderr, "[ERROR] Cannot start CivetWeb -inconsistent build.\n");
    fflush(stderr);
    return EXIT_FAILURE;
  }
  printf("OK.\n");
  fflush(stdout);

  /* Callback will print error messages to console */
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.log_message = log_message;

  /* start CivetWeb web server */
  printf("[INFO] Starting websocket server ... ");
  fflush(stdout);
  ctx = mg_start(&callbacks, 0, options);
  if (!ctx)
  {
    fprintf(stderr, "\n[ERROR] Cannot start websocket server.\n");
    fflush(stderr);
    return EXIT_FAILURE;
  }
  printf("OK.\n");
  fflush(stdout);

  // Request handler
  mg_set_request_handler(ctx, "/", http_handler, (void *)"html");
  printf("[INFO] HTTP server: http://localhost:%s\n", HTTP_PORT);
  fflush(stdout);

  /* Wait until the server should be closed */
  while (!EXITNOW)
  {
    SLEEP(100);
  }

  /* Stop the server */
  mg_stop(ctx);

  return EXIT_SUCCESS;
}
