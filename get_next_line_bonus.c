/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozcelik <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:11:45 by aozcelik          #+#    #+#             */
/*   Updated: 2022/01/24 13:33:05 by aozcelik         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ilk_satr(char *str)
{
	int		i;
	char	*satr;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n' && str)
		i++;
	satr = malloc(i + 2);
	if (!satr)
		return (NULL);
	ft_memmove(satr, str, i + 1);
	satr[i + 1] = '\0';
	return (satr);
}

static char	*sradaki_satr(char *str)
{
	int		i;
	char	*satr;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	satr = malloc(ft_strlen(&str[i]) + 1);
	if (!satr)
		return (0);
	ft_memmove(satr, &str[i + 1], ft_strlen(&str[i]));
	satr[ft_strlen(&str[i])] = '\0';
	free(str);
	if (ft_strlen(satr) == 0)
		return (free(satr), NULL);
	return (satr);
}

char	*get_next_line(int fd)
{
	static char	*kelime[10240];
	char		*satr;
	char		veri[BUFFER_SIZE + 1];
	int			okuma;

	satr = NULL;
	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	okuma = 1;
	while (okuma != 0 && !(yeni_satr(kelime[fd])))
	{
		okuma = read(fd, veri, BUFFER_SIZE);
		if (okuma == -1)
			return (NULL);
		veri[okuma] = '\0';
		if (!okuma)
			break ;
		kelime[fd] = ft_strjoin(kelime[fd], veri);
	}
	satr = ilk_satr(kelime[fd]);
	kelime[fd] = sradaki_satr(kelime[fd]);
	return (satr);
}

#include <stdio.h>
int main()
{
    char *c;
    int fd = open("test", O_RDONLY);
    
    c = get_next_line(fd);
    while(c)
    {
        printf("%s",c);
        free(c);
        c = get_next_line(fd);
    }

}
