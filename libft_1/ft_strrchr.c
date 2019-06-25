/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 12:00:33 by jlagos            #+#    #+#             */
/*   Updated: 2018/11/18 16:38:08 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_c;
	size_t		i;

	i = ft_strlen(s);
	last_c = NULL;
	while (s[i] != (unsigned char)c)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	last_c = &s[i];
	return ((char *)last_c);
}
