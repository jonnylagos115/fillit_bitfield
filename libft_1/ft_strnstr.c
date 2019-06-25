/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:37:19 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/11 11:25:35 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!*little)
		return (char *)big;
	while (len && *big)
	{
		while (little[i] && big[i] == little[i] && len && len - i)
			i++;
		if (!little[i])
			return (char *)big;
		len--;
		if (!len)
			return (NULL);
		big++;
		i = 0;
	}
	return (NULL);
}
