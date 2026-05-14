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

t_se	*servercloud(t_se *nw, int n)
{
	static t_se		*e;

	return (e + 0 * (!n && (e = nw)));
}

int		client_process(int connfd, char *buf, struct sockaddr_in cliaddr)
{
	int			len;
	t_client	data;
	char		rpath[BUFF_SIZE];

//	data.function = -1;
	data.putdata = NULL;
	data.connfd = connfd;
//	data.putfilename = NULL;
	getcwd((char *)data.rpath, BUFF_SIZE);
	strcpy(data.path, data.rpath);
	printf("Received request...");//
	if (!buf)
		exit(1 + 0 * printf("memory error\n"));
	memset(buf, 0, BUFF_SIZE);
	while ((len = read(data.connfd, buf, BUFF_SIZE)) > 0)
	{
		buf[len] = '\0';
		shell(&data, buf, len);
	}
	free(buf ? buf : NULL);
	buf = NULL;
	if (len < 0)
		exit(1 + 0 * printf("Read error"));
	close(connfd);
	return (1);
}

int		start_server(int ac, char **av)
{
	int					listenfd;
	struct sockaddr_in	servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons((ac > 1) ? atoi(av[1]) : 3000);
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(listenfd, 8);
	return (listenfd);
}

int		main(int ac, char **av)
{
	t_se					e;
	pid_t					pid;
	socklen_t				clilen;
	int						connfd;
	struct sockaddr_in		cliaddr;

	servercloud(&e, 0);
	e.listenfd = start_server(ac, av);
	printf("Server running...waiting for connections.\n");
	while (1)
	{
		clilen = sizeof(cliaddr);
		connfd = accept(e.listenfd, (struct sockaddr *)&cliaddr, &clilen);
		if (!(pid = fork()))
			client_process(connfd, (char *)malloc(sizeof(char) * BUFF_SIZE),
					cliaddr);
	}
	return (0);
}
