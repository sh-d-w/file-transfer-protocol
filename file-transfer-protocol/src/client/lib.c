/*                       __________________							  */
/*                        S |-| - D - \/\/ 							  */
/*                       ==================							  */
/*																	  */
/*   	   Original code developed during 42.fr curriculum. 		  */
/* 			  Project renamed and refactored for clarity.			  */
/*             Created: 2017-07-16 by S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ				  */
/*																	  */
/*   Copyright [2026] [S𝔥𝔞⁽ᵃʰⁱ⁾d M𝔞𝔥𝔬𝔪𝔢ᵈ] under Apache 2.0 License	  */

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int		my_system(char *s)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	if (!(pid = fork()))
		execl("/bin/sh", "sh", "-c", s, (char *)0);
	wpid = waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		wpid = waitpid(pid, &status, WUNTRACED);
	return (1);
}

char	*file_get_contents(char *s)
{
	char	*tmp;
	char	*t;
	int		fd;

	t = (char *)malloc(sizeof(char) * 9000000);
	fd = open(s, O_RDONLY);
	t[read(fd, t, 9000000)] = '\0';
	close(fd);
	tmp = strdup(t);
	free(t);
	return (tmp);
}

char	*itoa(int n)
{
	char	*s;
	int		t[13];

	t[11] = -1;
	t[12] = -1;
	if (n == 0)
		t[++t[12]] = 0;
	s = (char *)malloc(sizeof(char) * 11);
	if (s && n < 0 && (s[++t[11]] = '-'))
		n = -n;
	while (n > 0 && ((t[++t[12]] = n % 10) >= 0))
		n /= 10;
	while (s && --t[12] + 1 > -1 && (s[++t[11]] = 48 + t[t[12] + 1]))
		s[t[11] + 1] = '\0';
	return (s);
}

char	*strconcat(const char *s, ...)
{
	va_list		a;
	char		*t;
	char		*tmp;

	va_start(a, s);
	t = strcpy(malloc(sizeof(char) * 1000000), s);
	while ((tmp = va_arg(a, char *)))
		strcat(t, tmp);
	tmp = strdup(t);
	free(t);
	va_end(a);
	return (tmp);
}
