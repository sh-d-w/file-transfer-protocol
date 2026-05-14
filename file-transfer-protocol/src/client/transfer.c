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

int		get(char *response)
{
	int		c;
	int		y;
	int		fd;
	char	*t;
	t_ce	*e;
	char	buf[BUFF_SIZE];

	c = 0;
	y = 0;
	e = clientcloud(0, 1);
	my_system(t = strconcat("touch ", &response[4], 0));
	if (!(fd = open(&response[4], O_WRONLY)))
		return (printf("client get error\n"));
	while ((y == BUFF_SIZE || !c) && (y = read(e->sockfd, buf, BUFF_SIZE)) > 0 &&
		(y == BUFF_SIZE || ++c == 1))
	{
	
		buf[y] = '\0';
		write(fd, buf, y);
	}
	close(fd);
	return (0);
}

int		put(char *request)
{
	int		c;
	int		y;
	t_ce	*e;
	int		fd;
//	char	*t;
	char	buf[BUFF_SIZE];

	c = 0;
	y = 0;
	e = clientcloud(0, 1);
//	t = strconcat(data->path, "/", &request[4], 0);
	if (!(fd = open(&request[4], O_RDONLY)))
		return (printf("server get error\n"));
	while ((y == BUFF_SIZE || !c) && (y = read(fd, buf, BUFF_SIZE)) > 0 &&
		(y == BUFF_SIZE || ++c == 1))
	{
		buf[y] = '\0';
		write(e->sockfd, buf, y);
	}
	close(fd);
	printf("client:put\n");
	return (0);
}

int		receive_line(char *line, int (*f)(char *))
{
	t_ce	*e;
	char	*t;
	char	*out;
	int		count;

	out = NULL;
	e = clientcloud(0, 1);
	e->cmd = strdup((char *)e->buf);
//	if (!(count = 0) && e->function < 5)
	write(e->sockfd, line, e->len);
//	line[e->len] = '\0';
	// while (++count && e->function < 5 && (e->len = recv(e->sockfd, line,
	// 				BUFF_SIZE, 0)) > 0 && e->len >= BUFF_SIZE)
	// {
	// 	line[e->len] = '\0';
	// 	t = out;
	// 	out = strconcat(out ? out : "", line, 0);
	// 	free(t ? t : NULL);
	// }
	f(e->cmd);//out = strconcat(out ? out : "", line, 0));
	free(e->cmd ? e->cmd : NULL);
//	free(out ? out : NULL);
//	if (!e->len)
//		exit(4 + 0 * printf("The server terminated prematurely\n"));
	return (1);
}
