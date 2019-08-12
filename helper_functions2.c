/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:21:49 by jlagos            #+#    #+#             */
/*   Updated: 2019/06/25 10:22:14 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

/*
**	Finds the minimum size of the grid for the number of pieces.
**	(Hint: it's just the square root, with extra addition sometimes.)
**
**	Returns the starting board size.
*/

int			starting_board_size(int num)
{
	int		factors[10];
	int		num_of_factors;
	int		i;
	int		num_cpy;

	i = num;
	num_of_factors = -1;
	num_cpy = num;
	while (num_cpy != 1)
	{
		while ((i * i) > num_cpy)
			i--;
		if ((i * i) % num_cpy == 0)
		{
			factors[++num_of_factors] = i;
			num_cpy /= (i * i);
		}
		else
			num_cpy--;
	}
	i = factors[num_of_factors];
	while (--num_of_factors >= 0)
		i *= factors[num_of_factors];
	i = i + 2 > (num / 4) - 2 ? i : i + 1;
	return ((num / 4) % 2 == 0 && (num / 4) > i ? i + 1 : i);
}

/*
**	Finds the list associated with letter in the linked list head.
**
**	Returns the list if found, NULL if not found or invalid letter.
*/

t_tetrom	*locate_piece(t_tetrom *head, char letter)
{
	t_tetrom *tetrom;

	tetrom = head;
	if (letter < 'A')
		return (NULL);
	while (tetrom->next)
	{
		if (tetrom->alphabet == letter)
			break ;
		tetrom = tetrom->next;
	}
	return (tetrom);
}

/*
**	Assigns row, col, reset_row, and reset_col (in struct tetrom)
**	to the coordinates of the 4 minos in the tetrominos.
*/

void		get_reset_coordinates(t_tetrom *tetrom)
{
	int		i;
	int		j;
	int		curr_mino;

	i = -1;
	j = -1;
	curr_mino = 0;
	while (tetrom->piece[++i] && curr_mino != 4)
	{
		while (tetrom->piece[i][++j])
		{
			if (tetrom->piece[i][j] == '#')
			{
				tetrom->reset_row[curr_mino] = i;
				tetrom->reset_col[curr_mino] = j;
				tetrom->row[curr_mino] = i;
				tetrom->col[curr_mino] = j;
				curr_mino++;
			}
		}
		j = -1;
	}
}

/*
**	Creates the grid to be printed to the standard output.
**	The function assumes all the pieces are all properly placed
**	and places the pieces based off of their coordinates into the grid.
**
**	Returns the grid.
*/

char		**convert_bitfield(t_tetrom *start, int dim)
{
	t_tetrom	*curr_mino;
	char		**grid;
	int			i;

	curr_mino = start;
	grid = create_empty_grid(dim);
	i = -1;
	while (curr_mino)
	{
		while (++i < 4)
			grid[curr_mino->row[i]][curr_mino->col[i]] = curr_mino->alphabet;
		i = -1;
		curr_mino = curr_mino->next;
	}
	return (grid);
}

/*
**	Checks every '.' to see if it needs to be replaced with a ' '.
**	If it does, make the replacement.
*/

void		insert_spaces(char *str)
{
	int		i;
	int		spaces;
	int		touches;

	i = 0;
	spaces = 0;
	while (!(i == -1 && spaces != 1) && ++i > -1 && spaces != 2)
	{
		if (str[i] == '.')
		{
			touches = 0;
			if ((i != 0 && (str[i - 1] == '#' || str[i - 1] == ' ')) ||
			str[i + 1] == '#' || str[i + 1] == ' ')
				touches++;
			if ((i > 4 && (str[i - 5] == '#' || str[i - 5] == ' ')) ||
			(i < 14 && (str[i + 5] == '#' || str[i + 5] == ' ')))
				touches++;
			if (touches >= 2)
			{
				str[i] = ' ';
				spaces++;
			}
		}
		i = str[i] ? i : -1;
	}
}
