/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:33:59 by jlagos            #+#    #+#             */
/*   Updated: 2019/05/06 13:34:00 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

void    print_grid(char **grid)
{
    int i;

    i = -1;
    while (grid[++i])
	{
        ft_putstr(grid[i]);
		ft_putchar('\n');
	}
}

char	**ft_2dstrcpy(char **dst, char **src)
{
	size_t i;
	size_t j;

	i = -1;
	j = -1;
	while (src[++i])
	{
		while (src[i][++j])
			dst[i][j] = src[i][j];
		j = -1;
	}
	return (dst);
}

void	bit_field_write(unsigned int bit, char width, unsigned int value, unsigned long long *byte)
{
	unsigned long long mask;

	mask = 0;
	while(width--)
	{
		mask = mask << 1;
		mask |= 1;	
	}
	/* position the value and the mask */
	value = value << bit;  
	mask = mask << bit;
	/* invert the mask */
	mask ^= 0xFFFFFFFF;
	/* filter the existing value, reset to zero */
	*byte &= mask;
	/* set the bit field */
	*byte |= value;
}

unsigned int bit_field_read(unsigned int bit, char width, unsigned int byte)
{
	unsigned int mask;

	mask = 0;
	while(width--)
	{
		mask = mask << 1;
		mask |= 1;	
	}
	byte = byte >> bit;
	return( byte & mask );
}

char	**create_empty_grid(int len)
{
	char **grid;
	int i;

	grid = ft_2dstrnew(len);
	i = -1;
	while (++i < len)
		ft_memset(grid[i], '.', len);
	return (grid);
}

int		check_available_spot(Tetrom *tetrom, unsigned long long *grid, int dim)
{
	unsigned long long 	flag;
	unsigned int		k_bit;
	int				i;

	i = -1;
	flag = 1;
	while (++i < 4)
	{
		k_bit = (tetrom->row[i] * dim) + tetrom->col[i];
		flag = flag << k_bit;
		if ((*grid) & flag)
			return (1);
		flag = flag >> k_bit;
	}
	return (0);
}