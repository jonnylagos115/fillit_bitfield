/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstrnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:10:38 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/24 17:28:54 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_2dstrnew(int len)
{
	char	**str;
	int		i;

	if (!(str = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = ft_strnew(len);
	str[i] = NULL;
	return (str);
}
