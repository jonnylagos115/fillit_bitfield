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

void		print_bits64(uint64_t octet)
{
	int 			i;
	unsigned char 	bit;

	i = 64;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
	ft_putchar('\n');
}

int			shift_coordinates(t_tetrom *tetrom, int size)
{
	int i;
	int	j;
	int	shift_down;

	i = -1;
	j = -1;
	shift_down = 0;
	while (++i < 4)
		if (tetrom->col[i] == size - 1)
			shift_down = 1;
	while (shift_down && ++j < 4)
		if ((tetrom->row[j] + 1) >= size)
			return (0);
	j = -1;
	if (shift_down)
	{
		while (++j < 4)
		{
			tetrom->row[j] += 1;
			tetrom->col[j] = tetrom->reset_col[j];
		}
	}
	else
		while (++j < 4)
			tetrom->col[j] += 1;
	return (1);
}

int			store_place_piece(t_tetrom *tetrom, uint64_t *grid, int dim)
{
	unsigned int	k_bit;
	int				i;

	i = -1;
	k_bit = 0;
	while (check_available_spot(tetrom, grid, dim))
		if (!shift_coordinates(tetrom, dim))
			return (0);
	while (++i < 4)
	{
		k_bit = (tetrom->row[i] * dim) + tetrom->col[i];
		bit_field_write(k_bit, (uint64_t)1, grid);
	}
	return (1);
}

void		clear_all_pieces(t_tetrom *start, char to_place_p,
uint64_t *grid, int dim)
{
	t_tetrom		*curr;
	unsigned int	k_bit;
	uint64_t		flag;
	int				i;

	curr = start;
	k_bit = 0;
	flag = 1;
	i = -1;
	while (curr && curr->alphabet != to_place_p)
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
		i = -1;
		curr = curr->next;
	}
}

int			undo_prev_piece(t_tetrom *head, t_tetrom **tetrom, uint64_t *grid,
int dim)
{
	t_tetrom	*curr_prev;
	int			i;

	curr_prev = locate_piece(head, (*tetrom)->alphabet - 1);
	while (curr_prev)
	{
		clear_all_pieces(curr_prev, (*tetrom)->alphabet, grid, dim);
		if (!shift_coordinates(curr_prev, dim) ||
			!store_place_piece(curr_prev, grid, dim))
		{
			//get_reset_coordinates(curr_prev, 'B');
			i = -1;
			while (++i < 4)
			{
				curr_prev->row[i] = curr_prev->reset_row[i];
				curr_prev->col[i] = curr_prev->reset_col[i];
			}
			store_place_piece(curr_prev, grid, dim);
			curr_prev = locate_piece(head, curr_prev->alphabet - 1);
		}
		else
		{
			(*tetrom) = locate_piece(head, curr_prev->alphabet + 1);
			return (1);
		}
	}
	(*tetrom) = locate_piece(head, 'A');
	return (0);
}

char		**fillit(t_tetrom *tetrom, int num_of_tetrom)
{
	t_tetrom			*head;
	int					dim;
	int					i;
	uint64_t			grid;

	head = tetrom;
	dim = starting_board_size((double)num_of_tetrom * 4);
	while (tetrom->height > dim)
		dim++;
	grid = 0;
	while (tetrom)
	{
		if (!store_place_piece(tetrom, &grid, dim))
		{
			if (!undo_prev_piece(head, &tetrom, &grid, dim))
				clear_reset_pieces(head, &grid, &dim);
		}
		else
			tetrom = tetrom->next;
		if (tetrom)
		{
			//get_reset_coordinates(tetrom, 'B');
			i = -1;
			while (++i < 4)
			{
				tetrom->row[i] = tetrom->reset_row[i];
				tetrom->col[i] = tetrom->reset_col[i];
			}
		}
	}
	return (convert_bitfield(head, dim));
}
