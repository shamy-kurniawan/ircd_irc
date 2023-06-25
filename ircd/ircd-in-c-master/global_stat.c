#include <time.h>
#include <arpa/inet.h>

#include "replies.h"
#include "global_stat.h"
#include "network_io.h"

const char *server_version = __DATE__;
char motd[1024];

time_t server_start_time;

void initialize_global_stat()
{
	server_start_time = time(NULL);
}	

void send_welcome(struct client *cli)
{
	char addr_buffer[30];

	struct sockaddr_in server_addr;
	socklen_t addrlen = sizeof(struct sockaddr);

	getsockname(cli->fd, (struct sockaddr *) &server_addr, &addrlen);

	inet_ntop(AF_INET, &(server_addr.sin_addr), addr_buffer, 30);

	send_message(cli->fd, -1, "%03d %s :Welcome to the %s!%s@%s", RPL_WELCOME, cli->nick, cli->nick, cli->user, cli->ip_addr);
	send_message(cli->fd, -1, "%03d %s :Your host is %s, running version %s", RPL_YOURHOST, cli->nick, addr_buffer, server_version); 
	send_message(cli->fd, -1, "%03d %s :This server was created %s", RPL_CREATED, cli->nick, ctime(&server_start_time));
	send_message(cli->fd, -1, "%d %s :-%s Message of the day-", RPL_MOTDSTART, cli->nick, addr_buffer);
	send_message(cli->fd, -1, "%d %s :-%s", RPL_MOTD, cli->nick, motd);
	send_message(cli->fd, -1, "%d %s :End of /MOTD command", RPL_ENDOFMOTD, cli->nick);
}
