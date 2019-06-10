/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:46:29 by jlagos            #+#    #+#             */
/*   Updated: 2019/03/26 11:00:04 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

int		shift_coordinates(Tetrom *tetrom, int size)
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
	i = -1;
	j = -1;
	if (shift_down)
	{
		while (++j < 4)
			tetrom->row[j] += 1;
		get_reset_coordinates(tetrom, "col");
	}
	else
		while (++i < 4)
			tetrom->col[i] += 1;
	return (1);
}


int		store_place_piece(Tetrom *tetrom, unsigned long long *grid, int dim)
{
	unsigned int k_bit;
	int		i;

	i = -1;
	k_bit = 0;
	while (check_available_spot(tetrom, grid, dim))
		if (!shift_coordinates(tetrom, dim))
			return (0);
	while (++i < 4)
	{
		k_bit = (tetrom->row[i] * dim) + tetrom->col[i];
		bit_field_write(k_bit,FIELD_WIDTH, 1, grid);
	}
	return (1);
}

void		reset_piece_coordinates(Tetrom *head)
{
	Tetrom	*curr;

	curr = head;
	while (curr)
	{
		get_reset_coordinates(curr, "both");
		curr = curr->next;
	}
}

/*int			check_if_piece_placed(Tetrom *curr, unsigned int *grid, int dim)
{
	unsigned int 	flag;
	unsigned int	k_bit;
	int				i;

	i = -1;
	flag = 1;
	while (++i < 4)
	{
		k_bit = (curr->row[i] * dim) + curr->col[i];
		flag = flag << k_bit;
		if (!((*grid) & flag))
			return (0);
		flag = flag >> k_bit;
	}
	return (1);
}*/

void		clear_all_pieces(Tetrom *start, char to_place_p, unsigned long long *grid, int dim)
{
	Tetrom			*curr;
	unsigned int 	k_bit;
	unsigned int	flag;
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

/*
** Undoes previous placed piece, shifts over to the next available spot
** Function will return 0 ONLY if the piece cannot be shift any further
** Before it returns 0, it will reset piece back to the most upper left it can be 
** 
*/
int		undo_prev_piece(Tetrom *tetrom, char to_place_p, unsigned long long *grid, int dim)
{
	clear_all_pieces(tetrom, to_place_p, grid, dim);
	if (!shift_coordinates(tetrom, dim) || !store_place_piece(tetrom, grid, dim))
	{
		get_reset_coordinates(tetrom, "both");
		store_place_piece(tetrom, grid, dim);
		return (0);
	}
	return (1);
}

void		fillit(Tetrom *tetrom, int num_of_tetrom)
{
	Tetrom				*head;
	int					dim;
	unsigned long long 	grid;
	char				**board;
	char				to_place;

	head = tetrom;
	dim = starting_board_size((double)num_of_tetrom * 4);
	grid = 0;
	while (tetrom->height > dim)
		dim++;
	while (tetrom)
	{
		if (!store_place_piece(tetrom, &grid, dim))
		{
			to_place = tetrom->alphabet;
			while (!undo_prev_piece(locate_prev_piece(head, tetrom->alphabet - 1), to_place, &grid, dim))
			{
				tetrom = locate_prev_piece(head, tetrom->alphabet - 1);
				if (tetrom->alphabet == 'A')
				{
					dim++;
					ft_memset(&grid, 0, sizeof(grid));
					reset_piece_coordinates(head);
					break ;
				}
			}
			/*ft_putstr("After undo_prev: ");
			ft_putchar('\n');
			print_bits32(grid);
			ft_putchar('\n');*/
			get_reset_coordinates(tetrom, "both");
		}
		else
		{
			/*ft_putstr("piece: ");
			ft_putchar(tetrom->alphabet);
			ft_putchar('\n');
			ft_putstr("Current bitfield set: ");
			print_bits32(grid);
			ft_putchar('\n');*/
			tetrom = tetrom->next;
			if (tetrom)
				get_reset_coordinates(tetrom, "both");
		}
	}
	/*ft_putstr("Final bitfield set: ");
	print_bits32(grid);
	ft_putchar('\n');*/
	board = convert_bitfield(head, dim);
	print_grid(board);
}
