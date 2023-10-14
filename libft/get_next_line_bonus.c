/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmouline <jul.moulines@free.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 23:57:18 by jmouline          #+#    #+#             */
/*   Updated: 2023/10/14 02:06:27 by jmouline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_read(int fd, char **stock, int count_read)
{
	char	*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = malloc(BUFFER_SIZE + 1);
	while (!ft_strchr_gnl(*stock, '\n') && count_read)
	{
		if (!buff)
			return (0);
		count_read = read(fd, buff, BUFFER_SIZE);
		if (count_read == -1)
			return (free(buff), free(*stock), -1);
		buff[count_read] = '\0';
		*stock = ft_strjoin_gnl(*stock, buff);
		if (!*stock)
			return (free(buff), 0);
	}
	free(buff);
	return (count_read);
}

char	*ft_get_line(char *stock)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = 0;
	if (!stock || !stock[i])
		return (NULL);
	while (stock[i] != '\n' && stock[i])
		i++;
	if (stock[i] == '\n')
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (stock[j] != '\n' && stock[j])
		dest[i++] = stock[j++];
	dest[i] = stock[j];
	if (dest[i] != '\0')
		dest[++i] = '\0';
	return (dest);
}

char	*ft_new_stock(char *stock, int count_read)
{
	char	*dest;
	char	*to_free;
	int		i;
	int		j;

	j = 0;
	to_free = stock;
	if (count_read == 0)
		return (free(to_free), NULL);
	while (*stock != '\n' && *stock)
		stock++;
	stock++;
	while (stock[j])
		j++;
	dest = malloc(j + 1);
	if (!dest)
		return (free(to_free), NULL);
	dest[j] = '\0';
	j = 0;
	i = 0;
	while (stock[j])
		dest[j++] = stock[i++];
	free(to_free);
	return (dest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock[1024];
	int			count_read;

	count_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	count_read = ft_read(fd, &stock[fd], count_read);
	if (count_read < 0)
		return (NULL);
	line = ft_get_line(stock[fd]);
	stock[fd] = ft_new_stock(stock[fd], count_read);
	if (!line)
		return (NULL);
	return (line);
}
