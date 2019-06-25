/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:15:38 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/10 15:57:47 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*strsub;
	size_t		i;

	if (!s)
		return (NULL);
	strsub = ft_strnew(len);
	i = 0;
	if (!strsub)
		return (NULL);
	while (i < len)
		strsub[i++] = s[start++];
	return (strsub);
}
