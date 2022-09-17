/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aozcelik <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:47:09 by aozcelik          #+#    #+#             */
/*   Updated: 2022/01/24 11:23:55 by aozcelik         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*kelime;
	char		*satr;
	char		veri[BUFFER_SIZE + 1];
	int			okuma;

	satr = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	okuma = 1;
	while (okuma != 0 && !(yeni_satr(kelime)))
	{
		okuma = read(fd, veri, BUFFER_SIZE);
		if (okuma == -1)
			return (NULL);
		veri[okuma] = '\0';
		if (!okuma)
			break ;
		kelime = ft_strjoin(kelime, veri);
	}
	satr = ilk_satr(kelime);
	kelime = sradaki_satr(kelime);
	return (satr);
}
