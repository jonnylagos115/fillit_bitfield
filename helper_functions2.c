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

int			starting_board_size(double num)
{
	double	lo;
	double	hi;
	double	mid;
	int		i;

	lo = 0;
	hi = num;
	i = -1;
	while (++i < 1000)
	{
		mid = (lo + hi) / 2;
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

void		get_reset_coordinates(t_tetrom *tetrom)
{
	t_point p;

	p.i = -1;
	p.j = -1;
	p.curr = 0;
	while (tetrom->piece[++p.i] && p.curr != 4)
	{
		while (tetrom->piece[p.i][++p.j])
		{
			if (tetrom->piece[p.i][p.j] == '#')
			{
				tetrom->reset_row[p.curr] = p.i;
				tetrom->reset_col[p.curr] = p.j;
				tetrom->row[p.curr] = p.i;
				tetrom->col[p.curr] = p.j;
				p.curr++;
			}
		}
		p.j = -1;
	}
}

char		**convert_bitfield(t_tetrom *start, int dim)
{
	t_tetrom	*curr;
	char		**grid;
	int			i;

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

void		insert_spaces(int *s, int *i, int *flag, char *str)
{
	while ((((*s) += 5) <= 15))
	{
		if (str[(*i) + (*s)] == '#' || str[(*i) + (*s)] == ' ')
		{
			if ((*i) != 0 && str[((*i) - 1) + (*s)] == '.')
				(*flag) += check_if_insert_space(str, (*i) - 1 + (*s));
			if (str[((*i) + 1) + (*s)] == '.')
				(*flag) += check_if_insert_space(str, (*i) + 1 + (*s));
			if (((*i) + (*s)) > 4 && str[((*i) + (*s)) - 5] == '.')
				(*flag) += check_if_insert_space(str, (*i) + (*s) - 5);
			if (((*i) + (*s)) < 14 && str[((*i) + (*s)) + 5] == '.')
				(*flag) += check_if_insert_space(str, (*i) + (*s) + 5);
		}
	}
	(*s) = -5;
	if (*flag)
	{
		(*i) = -1;
		(*flag) = 0;
	}
}
