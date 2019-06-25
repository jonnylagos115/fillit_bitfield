/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:34:58 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/10 12:51:43 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh_str;
	size_t	i;
	size_t	j;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	fresh_str = (char *)malloc(total_len + 1 * sizeof(char));
	if (fresh_str == NULL)
		return (NULL);
	while (s1[i])
	{
		fresh_str[i] = s1[i];
		i++;
	}
	while (s2[j])
		fresh_str[i++] = s2[j++];
	fresh_str[i] = '\0';
	return (fresh_str);
}
