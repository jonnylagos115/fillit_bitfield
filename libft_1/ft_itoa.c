/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:28:11 by jlagos            #+#    #+#             */
/*   Updated: 2019/01/10 15:24:03 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		num_len(int num)
{
	size_t len;

	len = 1;
	while (num /= 10)
		len++;
	return (len);
}

char				*ft_itoa(int n)
{
	char			*fresh_str;
	unsigned int	num;
	size_t			len;

	num = n;
	len = num_len(n);
	if (n < 0)
	{
		num = -n;
		len++;
	}
	if (!(fresh_str = ft_strnew(len)))
		return (NULL);
	fresh_str[--len] = num % 10 + '0';
	while (num /= 10)
		fresh_str[--len] = num % 10 + '0';
	if (n < 0)
		*(fresh_str + 0) = '-';
	return (fresh_str);
}
