/*                       __________________							  */
/*                        S |-| - D - \/\/ 							  */
/*                       ==================							  */
/*																	  */
/*   	   Original code developed during 42.fr curriculum. 		  */
/* 			  Project renamed and refactored for clarity.			  */
/*             Created: 2017-07-16 by S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ				  */
/*																	  */
/*   Copyright [2026] [S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ] under Apache 2.0 License	  */

#ifndef CLIENT_H
# define CLIENT_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# define BUFF_SIZE 4096

typedef struct		s_ce
{
	int				len;
	char			*cmd;
	int				sockfd;
	int				function;
	char			*receiveline;
	char			buf[BUFF_SIZE];
}					t_ce;

/*
** client.c
*/
t_ce				*clientcloud(t_ce *nw, int n);

/*
** lib.c
*/
char				*itoa(int n);
int					my_system(char *s);
char				*file_get_contents(char *s);
char				*strconcat(const char *s, ...);

/*
** shell.c
*/
int					ls(char *response);
int					cd(char *response);
int					pwd(char *response);
int					quit(char *response);
int					shell(char *line);

/*
** transfer.c
*/
int					get(char *response);
int					put(char *request);
int					receive_line(char *line, int (*f)(char *));
#endif
