/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:22:14 by jlagos            #+#    #+#             */
/*   Updated: 2018/12/07 10:26:03 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*string;

	i = 0;
	string = (char *)malloc(size + 1 * sizeof(char));
	if (string == NULL)
		return (NULL);
	while (i < size + 1)
		string[i++] = '\0';
	return (string);
}
