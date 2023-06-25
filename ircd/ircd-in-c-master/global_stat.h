#ifndef STAT_H
#define STAT_H

#include "client.h"

extern char motd[1024];
extern const char *server_version;
extern time_t server_start_time;

void initialize_global_stat();

void send_welcome(struct client *cli);
#endif
