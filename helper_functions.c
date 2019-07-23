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

void		clear_reset_pieces(t_tetrom *head, uint64_t *grid, int *dim)
{
	t_tetrom	*curr;

	curr = head;
	while (curr)
	{
		get_rc_piece(curr);
		curr = curr->next;
	}
	(*dim)++;
	(*grid) = 0;
}

void		get_rc_piece(t_tetrom *curr)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		curr->row[i] = curr->reset_row[i];
		curr->col[i] = curr->reset_col[i];
	}
}

/*
** position the value and the mask (line 51 & 52)
** invert the mask (line 53)
** filter the existing value, reset to zero (line 54)
** set the bit field (line 55)
*/

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

int			shift_c_to_pos(t_tetrom *tetrom, uint64_t *grid, int dim)
{
	while (check_available_spot(tetrom, grid, dim))
		if (!shift_coordinates(tetrom, dim))
			return (0);
	return (1);
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
