/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:20:43 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/10 19:23:04 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
static size_t	num_of_strings(char const *s, char c, size_t *x)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	while (s[i] == c)
	{
		i++;
		(*x)++;
	}
	while (s[i])
	{
		if (s[i] == c)
			if (s[i + 1] != c)
				len++;
		i++;
		if (s[i] == '\0' && s[i - 1] != c)
			len++;
	}
	return (len);
}

static size_t	len_str(char **s, char c)
{
	size_t len;

	len = 0;
	while (**s == c)
		(*s)++;
	if (**s == '\0')
		return (1);
	while (**s != c)
	{
		len++;
		(*s)++;
	}
	return (len);
}

static void		assign_char(char **str, char const *s, size_t *read_s, char c)
{
	size_t j;

	j = 0;
	while (s[*read_s] != c)
	{
		(*str)[j++] = s[*read_s];
		(*read_s)++;
	}
	(*str)[j] = '\0';
	while (s[*read_s] == c)
		(*read_s)++;
}

static void		*free_malloc(char ***strsplit, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		ft_strdel(&(*strsplit)[i++]);
	ft_strdel(*strsplit);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**strsplit;
	char	*temp;
	size_t	read_s;
	size_t	i;
	size_t	len;

	if (!s || !c)
		return (NULL);
	temp = (char *)s;
	read_s = 0;
	i = 0;
	len = num_of_strings(s, c, &read_s);
	if (!(strsplit = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	while (i < len)
	{
		if (!(strsplit[i] = ft_strnew(len_str(&temp, c))))
			return (free_malloc(&strsplit, i));
		i++;
	}
	strsplit[i] = NULL;
	i = 0;
	while (i < len)
		assign_char(&strsplit[i++], s, &read_s, c);
	return (strsplit);
}
