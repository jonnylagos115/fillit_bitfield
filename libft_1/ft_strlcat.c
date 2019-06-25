/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 10:59:27 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/12 17:01:53 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dst);
	if (len > dstsize)
		return (dstsize + ft_strlen(src));
	while (src[i])
	{
		if (dstsize - 1 > len)
			dst[len] = src[i];
		else
		{
			dst[len] = '\0';
			break ;
		}
		i++;
		len++;
	}
	dst[len] = '\0';
	return (len);
}
