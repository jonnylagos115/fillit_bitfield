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

/*
**	Resets the coordinates for every piece, cleans the board and increments
**	the size of the board up by one.
*/

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

/*
**	Resets the coordinates of the given piece to their starting position.
*/

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
**	Creates the 2d (square) string array with the dimentions of len,
**	and fills it with '.'
**
**	Returns the completed array.
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

/*
**	Checks in the grid to see if the piece fits at the specific coordinates.
**
**	Returns 1 if it doesn't fit, 0 if it does.
*/

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
