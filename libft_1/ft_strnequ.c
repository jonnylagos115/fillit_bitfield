/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:32:12 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/10 17:29:41 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	char *temp_s1;
	char *temp_s2;

	if (!s1 || !s2)
		return (0);
	temp_s1 = (char *)s1;
	temp_s2 = (char *)s2;
	if (*temp_s1 != *temp_s2 && *temp_s1 && *temp_s2)
		return (0);
	while (*temp_s1 == *temp_s2 && *temp_s1 && *temp_s2 && --n)
	{
		temp_s1++;
		temp_s2++;
		if (*temp_s1 != *temp_s2)
			return (0);
	}
	return (1);
}
