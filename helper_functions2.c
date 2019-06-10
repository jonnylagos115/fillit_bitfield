/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 13:37:02 by jlagos            #+#    #+#             */
/*   Updated: 2019/05/06 13:37:04 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

int		starting_board_size(double num)
{
	double 	lo;
	double 	hi;
	double 	mid;
	int		i;

	lo = 0;
	hi = num;
	i = -1;
	while (++i < 1000)
  	{
		mid = (lo+hi)/2;
    	if (mid * mid == num)
	 	 	return ((int)mid);
    	if (mid * mid > num) 
			hi = mid;
    	else
			lo = mid;
	}
	i = (int)mid;
	if (mid > i + 0.5)
		mid += 1;
	if (mid - 1 > 3.0)
		mid -= 1;
	return ((int)mid);
}

Tetrom		*locate_prev_piece(Tetrom *head, char letter)
{
	Tetrom *tetrom;

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

void		print_bits(unsigned char octet)
{
	int 			i;
	unsigned char 	bit;

	i = 8;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}

void		print_bits32(unsigned int octet)
{
	int 			i;
	unsigned int	bit;

	i = 64;
	while (i--)
	{
		bit = (octet >> i & 1) + '0';
		write(1, &bit, 1);
	}
}

/*
** resets piece coordinates to the upper most left corner of grid
*/
void	get_reset_coordinates(Tetrom *tetrom, char *str)
{
	int		i;
	int		j;
	int		curr;

	i = -1;
	j = -1;
	curr = 0;
	while (tetrom->piece[++i] && curr != 4)
	{
		while (tetrom->piece[i][++j])
		{
			if (tetrom->piece[i][j] == '#')
			{
				if (!ft_strcmp(str, "row"))
					tetrom->row[curr] = i;
				else if (!ft_strcmp(str, "col"))
					tetrom->col[curr] = j;
				else if (!ft_strcmp(str, "both"))
				{
					tetrom->row[curr] = (unsigned int)i;
					tetrom->col[curr] = (unsigned int)j;
				}
				curr++;
			}
		}
		j = -1;
	}
}

char	**convert_bitfield(Tetrom *start, int dim)
{
	Tetrom	*curr;
	char	**grid;
	int		i;

	curr = start;
	grid = create_empty_grid(dim);
	i = -1;
	while (curr)
	{
		while (++i < 4)
			grid[curr->row[i]][curr->col[i]] = curr->alphabet;
		i = -1;
		curr = curr->next;	
	}
	return (grid);
}

char 	**ft_2dstrdup(char **s1, int size)
{
	char 	**dup;
	int 	i;

	dup = ft_2dstrnew(size);
	i = -1;
	while (++i < size)
		ft_strncpy(dup[i], s1[i], size);
	dup[i] = NULL;
	return (dup);
}

