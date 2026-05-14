/*                       __________________							  */
/*                        S |-| - D - \/\/ 							  */
/*                       ==================							  */
/*																	  */
/*   	   Original code developed during 42.fr curriculum. 		  */
/* 			  Project renamed and refactored for clarity.			  */
/*             Created: 2017-07-16 by S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ				  */
/*																	  */
/*   Copyright [2026] [S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ] under Apache 2.0 License	  */

#include "../../includes/client.h"

int		ls(char *response)
{
	int		c;
	int		y;
	t_ce	*e;
	char	buf[BUFF_SIZE];

	c = 0;
	y = 0;
	e = clientcloud(0, 1);
	while ((y == BUFF_SIZE || !c) && (y = read(e->sockfd, buf, BUFF_SIZE)) > 0 &&
		(y == BUFF_SIZE || ++c == 1))
	{
		buf[y] = '\0';
		printf("%s\n", buf);
	}
	return (0);
}

int		cd(char *response)
{
	return (strlen(response) > 1 && printf("%s\n", response));
}

int		pwd(char *response)
{
	int		c;
	int		y;
	t_ce	*e;
	char	buf[BUFF_SIZE];

	c = 0;
	y = 0;
	e = clientcloud(0, 1);
	while ((y == BUFF_SIZE || !c) && (y = read(e->sockfd, buf, BUFF_SIZE)) > 0 &&
		(y == BUFF_SIZE || ++c == 1))
	{
		buf[y] = '\0';
		printf("%s\n", buf);
	}
	return (0);//printf("%s\n", response));
}

int		quit(char *response)
{
	t_ce	*e;

	e = clientcloud(0, 1);
	close(e->sockfd);
	exit(0);
}

int		shell(char *line)
{
	t_ce			*e;
	static int		slen[] = {2, 2, 3, 3, 4, 3};
	static char		*s[] = {"ls", "cd", "get", "pwd", "quit", "put"};
	static int		(*f[])(char *) = {&ls, &cd, &get, &pwd, &quit, &put};

	e = clientcloud(0, 1);
	e->function = -1;
	while (++e->function < 6 && strncmp(line, s[e->function],
		slen[e->function]))
		;
	return (e->function < 6 && receive_line(line, f[e->function]));
}
