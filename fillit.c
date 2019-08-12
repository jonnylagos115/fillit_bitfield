/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:19:31 by jlagos            #+#    #+#             */
/*   Updated: 2019/06/25 10:19:58 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

int			shift_coordinates(t_tetrom *tetrom, int size)
{
	int i;
	int	j;

	i = 0;
	j = -1;
	while (i < 4 && tetrom->col[i] != size - 1)
		i++;
	if (i == 4)
		while (--i > -1)
			tetrom->col[i] += 1;
	else
	{
		while (++j < 4)
			if (tetrom->row[j] + 1 >= size)
				return (1);
		while (--j > -1)
		{
			tetrom->row[j] += 1;
			tetrom->col[j] = tetrom->reset_col[j];
		}
	}
	return (0);
}

int			store_place_piece(t_tetrom *tetrom, uint64_t *grid, int dim)
{
	u_int64_t		value;
	unsigned int	k_bit;
	int				i;

	i = -1;
	while (check_available_spot(tetrom, grid, dim))
		if (shift_coordinates(tetrom, dim))
			return (1);
	while (++i < 4)
	{
		k_bit = (tetrom->row[i] * dim) + tetrom->col[i];
		value = 1;
		value = value << k_bit;
		*grid |= value;
	}
	return (0);
}

void		clear_piece(t_tetrom *curr, uint64_t *grid, int dim)
{
	unsigned int	k_bit;
	uint64_t		flag;
	int				i;

	flag = 1;
	i = -1;
	if (curr)
	{
		while (++i < 4)
		{
			k_bit = (curr->row[i] * dim) + curr->col[i];
			flag = flag << k_bit;
			flag = ~flag;
			*grid = (*grid) & flag;
			flag = ~flag;
			flag = flag >> k_bit;
		}
	}
}

int			undo_prev_piece(t_tetrom *head, t_tetrom **tetrom, uint64_t *grid,
int dim)
{
	t_tetrom	*curr_prev;

	curr_prev = locate_piece(head, (*tetrom)->alphabet - 1);
	while (curr_prev)
	{
		clear_piece(curr_prev, grid, dim);
		if (!shift_coordinates(curr_prev, dim)
		&& !store_place_piece(curr_prev, grid, dim))
		{
			(*tetrom) = locate_piece(head, curr_prev->alphabet + 1);
			return (0);
		}
		get_rc_piece(*tetrom);
		shift_c_to_pos(*tetrom, grid, dim);
		curr_prev = locate_piece(head, curr_prev->alphabet - 1);
	}
	(*tetrom) = locate_piece(head, 'A');
	return (1);
}

char		**fillit(t_tetrom *tetrom, int num_of_tetrom)
{
	t_tetrom			*head;
	int					dim;
	uint64_t			grid;

	head = tetrom;
	dim = starting_board_size((double)num_of_tetrom * 4);
	while (tetrom->height > dim)
		dim++;
	grid = 0;
	while (tetrom)
	{
		if (store_place_piece(tetrom, &grid, dim))
		{
			if (undo_prev_piece(head, &tetrom, &grid, dim))
				clear_reset_pieces(head, &grid, &dim);
		}
		else
			tetrom = tetrom->next;
		if (tetrom)
			get_rc_piece(tetrom);
	}
	return (convert_bitfield(head, dim));
}
