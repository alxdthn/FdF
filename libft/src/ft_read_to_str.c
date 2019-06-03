/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalexand <nalexand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 21:48:03 by nalexand          #+#    #+#             */
/*   Updated: 2019/06/02 03:49:38 by nalexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_read_to_str(char *file, char **str, int b_size)
{
	char	buf[b_size];
	char	*tmp;
	ssize_t	size;
	int		ret;
	int		fd;

	size = 0;
	*str = NULL;
	fd = open(file, O_RDONLY);
	while ((ret = read(fd, buf, b_size)))
	{
		if (!(tmp = ft_memjoin(*str, buf, size, ret)))
			return (-1);
		ft_memdel((void **)str);
		*str = tmp;
		size += ret;
	}
	close(fd);
	return (size);
}
