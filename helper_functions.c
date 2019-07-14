/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:21:13 by jlagos            #+#    #+#             */
/*   Updated: 2019/06/25 10:21:15 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

void		print_grid(char **grid)
{
	int	i;

	i = -1;
	while (grid[++i])
	{
		ft_putstr(grid[i]);
		ft_putchar('\n');
	}
}

void		clear_reset_pieces(t_tetrom *head, uint64_t *grid, int *dim)
{
	t_tetrom	*curr;
	int			i;

	curr = head;
	while (curr)
	{
		 i = -1;
		while (++i < 4)
		{
			curr->row[i] = curr->reset_row[i];
			curr->col[i] = curr->reset_col[i];
		}
		//get_reset_coordinates(curr, 'B');
		curr = curr->next;
	}
	(*dim)++;
	(*grid) = 0;
}

/*
** position the value and the mask (line 51 & 52)
** invert the mask (line 53)
** filter the existing value, reset to zero (line 54)
** set the bit field (line 55)
*/

void		bit_field_write(unsigned int bit, uint64_t value,
uint64_t *byte)
{
	uint64_t mask;

	mask = 1;
	value = value << bit;
	mask = mask << bit;
	mask ^= 0xFFFFFFFFFFFFFFFF;
	*byte &= mask;
	*byte |= value;
}

char		**create_empty_grid(int len)
{
	char	**grid;
	int		i;

	grid = ft_2dstrnew(len);
	i = -1;
	while (++i < len)
		ft_memset(grid[i], '.', len);
	return (grid);
}

int			check_available_spot(t_tetrom *tetrom, uint64_t *grid, int dim)
{
	uint64_t			flag;
	unsigned int		k_bit;
	int					i;

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
