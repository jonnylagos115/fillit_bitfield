/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:07:58 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/10 18:05:51 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;

	i = 0;
	if (!*needle)
		return (char *)haystack;
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			while (haystack[i] && haystack[i] == needle[i])
			{
				i++;
				if (!needle[i])
					return (char *)haystack;
			}
		}
		haystack++;
		i = 0;
	}
	return (NULL);
}
