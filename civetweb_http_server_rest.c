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

static int http_handler(struct mg_connection *conn, void *cbdata)
{

  const struct mg_request_info *ri = mg_get_request_info(conn);
  (void)cbdata; /* currently unused */

  mg_printf(conn,
            "HTTP/1.1 200 OK\r\nContent-Type: "
            "text/plain\r\nConnection: close\r\n\r\n");
  if (0 == strcmp(ri->request_method, "GET"))
  {
    return mg_printf(conn, "GET method received.");
  }
  if (0 == strcmp(ri->request_method, "PUT"))
  {
    return mg_printf(conn, "PUT method received.");
  }
  if (0 == strcmp(ri->request_method, "POST"))
  {
    const struct mg_request_info *ri = mg_get_request_info(conn);
    for (int i = 0; i < MG_MAX_HEADERS; i++)
    {
      if (ri->http_headers[i].name)
        printf("%s: %s\n", ri->http_headers[i].name, ri->http_headers[i].value);
      else
        break;
    }

    char post_data[1024];
    int post_data_len = mg_read(conn, post_data, sizeof(post_data));

    printf("Post data: %.*s\n", post_data_len, post_data);
    return mg_printf(conn, "%.*s", post_data_len, post_data);
  }
  if (0 == strcmp(ri->request_method, "DELETE"))
  {
    return mg_printf(conn, "DELETE method received.");
  }

  /* this is not a GET request */
  mg_send_http_error(
      conn, 405, "Only GET, PUT, POST, DELETE methodS are supported");
  return 405;
}

int main(int argc, char *argv[])
{
  /* options */
  const char *options[] = {"listening_ports",
                           HTTP_PORT,
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
  mg_set_request_handler(ctx, "/api", http_handler, NULL);
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
