/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:54:23 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/10 19:23:51 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t			is_whitespace(size_t *i, size_t *len, char *s)
{
	while (*(s + *i) == ' ' || *(s + *i) == '\n' || *(s + *i) == '\t')
		(*i)++;
	while (*(s + *len) == ' ' || *(s + *len) == '\n' || *(s + *len) == '\t'
			|| *(s + *len) == '\0')
	{
		if ((*len) == 0)
			break ;
		(*len)--;
	}
	if (*i || *len < ft_strlen(s))
		return (1);
	return (0);
}

char					*ft_strtrim(char const *s)
{
	char	*strtrim;
	size_t	i;
	size_t	k;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	len = ft_strlen(s);
	if (!is_whitespace(&i, &len, (char *)s))
		return ((char *)s);
	else if (ft_strlen(s) == i)
		return (ft_strnew(0));
	strtrim = ft_strnew((len - i) + 1);
	if (!strtrim)
		return (NULL);
	while (i < len + 1)
		strtrim[k++] = s[i++];
	return (strtrim);
}
