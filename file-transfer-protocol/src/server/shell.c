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

int		ls(t_client *data, char *request, char **response)
{
	char				*t;
	DIR					*fd;
	struct dirent		*dp;
	int					len;

	t = NULL;
	if ((fd = opendir(data->path)) < 0)
		exit(0 * printf("ls: error, no such directory\n"));
	while ((dp = readdir(fd)) > 0)
	{
		*response = strconcat(dp->d_name, " ", t, 0);
		free(t ? t : NULL);
		t = *response;
	}
	closedir(fd);
	if ((len = strlen(t)))
		write(data->connfd, t, len);
	printf("server: ls\n");
	return (0);
}

int		cd(t_client *data, char *request, char **response)
{
	int		x;
	char	*t;
	DIR		*fd;

	t = NULL;
	if (!request[3] || !strcmp(&request[3], "/") || !strcmp(&request[3], "~"))
		strcpy(data->path, data->rpath);
	else if (!strcmp(&request[3], "."))
		return (1);
	else if (!strcmp(&request[3], "..") && strcmp(data->rpath, data->path) &&
			(x = strlen(data->path)))
	{
		while (--x > -1 && data->path[x] != '/')
			;
		if (x > -1)
			data->path[x] = '\0';
	}
	else if (!strstr(&request[3], "/") && !strstr(&request[3], "..") && (fd =
				opendir((t = strconcat(data->path, "/", &request[3], 0)))) > 0)
	{
		strcat(strcat(data->path, "/"), &request[3]);
		closedir(fd);
	}
	free(t ? t : NULL);
	return (1 + 0 * printf("server: cd\n"));
}

int		pwd(t_client *data, char *request, char **response)
{
	int		len;

	if ((len = strlen(data->path)))
		write(data->connfd, data->path, len);
	printf("server: pwd\n");
	return (0);
}

int		quit(t_client *data, char *request, char **response)
{
	return (1 + 0 * printf("server: quit\n"));
}

int		shell(t_client *data, char *request, int len)
{
	int				x;
	char			*t;
	static int		slen[] = {2, 2, 3, 3, 4, 3};
	static char		*s[] = {"ls", "cd", "get", "pwd", "quit", "put"};
	static int		(*f[])(t_client *, char *, char **) = {&ls, &cd, &get,
		&pwd, &quit, &put};

	x = -1;
	while (++x < 6 && strncmp(request, s[x], slen[x]))
		;
//	if (data->function == 6 && x != 6)
//		my_system(t = strconcat("printf \"%s\" \"", data->putdata,
//					"\" | xxd -r > ", data->putfilename, 0));
//	data->function = x;
//	free(x != 6 ? data->putdata : NULL);
//	free(x != 6 ? data->putfilename : NULL);
//	data->putdata = (x == 6 ? data->putdata : NULL);
//	data->putfilename = (x == 6 ? data->putfilename : NULL);
//	x -= (x == 6 && data->putfilename);
	return (x < 6 && send_line(data, request, len, f[x]));
}
