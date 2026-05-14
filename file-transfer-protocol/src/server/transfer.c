/*                       __________________							  */
/*                        S |-| - D - \/\/ 							  */
/*                       ==================							  */
/*																	  */
/*   	   Original code developed during 42.fr curriculum. 		  */
/* 			  Project renamed and refactored for clarity.			  */
/*             Created: 2017-07-16 by S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ				  */
/*																	  */
/*   Copyright [2026] [S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ] under Apache 2.0 License	  */

#include "../../includes/server.h"

int		get(t_client *data, char *request, char **response)
{
	int		c;
	int		y;
	t_se	*e;
	int		fd;
	char	*t;
	char	buf[BUFF_SIZE];

	c = 0;
	y = 0;
	e = servercloud(0, 1);
	t = strconcat(data->path, "/", &request[4], 0);
	if (!(fd = open(&request[4], O_RDONLY)))
		return (printf("server get error\n"));
	while ((y == BUFF_SIZE || !c) && (y = read(fd, buf, BUFF_SIZE)) > 0 &&
		(y == BUFF_SIZE || ++c == 1))
	{
		buf[y] = '\0';
		write(data->connfd, buf, y);
	}
	close(fd);
	printf("server: get\n");
	return (0);//strlen(*response));
}

int		put(t_client *data, char *request, char **response)
{//client get.
	int		c;
	int		y;
	int		fd;
	char	*t;
	t_se	*e;
	char	buf[BUFF_SIZE];

	c = 0;
	y = 0;
	e = servercloud(0, 1);
	my_system(t = strconcat("touch ", &request[4], 0));
	if (!(fd = open(&request[4], O_WRONLY)))
		return (printf("server put error\n"));
	while ((y == BUFF_SIZE || !c) && (y = read(data->connfd, buf, BUFF_SIZE)) > 0 &&
		(y == BUFF_SIZE || ++c == 1))
	{
		buf[y] = '\0';
		write(fd, buf, y);
	}
	close(fd);
	printf("server: put\n");
	return (0);
}

int		send_line(t_client *data, char *request, int len,
		int (*f)(t_client *, char *, char **))
{
	int				x;
	char			*t;
	char			*response;
	static char		*syntax[] = {";", "|", "&"};

	x = -1;
	while (++x < 3)
		if ((t = strstr(request, syntax[x])))
			t[0] = '\0';
	f(data, request, &response);
	return (1);
}
