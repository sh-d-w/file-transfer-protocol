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

t_ce	*clientcloud(t_ce *nw, int n)
{
	static t_ce		*e;

	return (e + 0 * (!n && (e = nw)));
}

int		start_client(int ac, char **av)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (ac < 2 || (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		exit(2 + 0 * printf(ac > 1 ? "Problem in creating the socket\n" :
					"Usage: ./TCPclient <ip address of server> <port>\n"));
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(av[1]);
	servaddr.sin_port = htons(((ac > 2) ? atoi(av[2]) : 3000));
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		exit(3 + 0 * printf("Problem in connecting to the server"));
	return (sockfd);
}

int		main(int ac, char **av)
{
	t_ce	e;
	char	buf[BUFF_SIZE];

	clientcloud(&e, 0);
	e.sockfd = start_client(ac, av);
	while ((ac > 1 ? write(1, av[1], strlen(av[1])) : 1) && write(1, "$ ", 2)
			&& (e.len = read(0, e.buf, BUFF_SIZE)) > 0 &&
				!(e.buf[e.len - 1] = '\0'))
	{
		shell((char *)e.buf);
	}
	return (0);
}
