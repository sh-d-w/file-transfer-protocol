/*                       __________________							  */
/*                        S |-| - D - \/\/ 							  */
/*                       ==================							  */
/*																	  */
/*   	   Original code developed during 42.fr curriculum. 		  */
/* 			  Project renamed and refactored for clarity.			  */
/*             Created: 2017-07-16 by S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ				  */
/*																	  */
/*   Copyright [2026] [S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ] under Apache 2.0 License	  */

#ifndef SERVER_H
# define SERVER_H
# define BUFF_SIZE 4096
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>

typedef struct		s_client
{
	int				len;
	int				connfd;
	int				malloced;
	int				function;
	char			path[BUFF_SIZE];
	char			rpath[BUFF_SIZE];
	char			*putfilename;
	char			*putdata;
}					t_client;

typedef struct		s_se
{
	int				n;
	int				listenfd;
}					t_se;

/*
** client.c
*/
t_se				*servercloud(t_se *nw, int n);

/*
** lib.c
*/
char				*itoa(int n);
char				*strconcat(const char *s, ...);
char				*file_get_contents(char *s);
int					my_system(char *s);

/*
** shell.c
*/
int					ls(t_client *data, char *request, char **response);
int					cd(t_client *data, char *request, char **response);
int					pwd(t_client *data, char *request, char **response);
int					quit(t_client *data, char *request, char **response);
int					shell(t_client *data, char *request, int len);

/*
** transfer.c
*/
int					get(t_client *data, char *request, char **response);
int					put(t_client *data, char *request, char **response);
int					send_line(t_client *data, char *request, int len,
		int (*f)(t_client *, char *, char **));
#endif
