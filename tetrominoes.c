/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrominoes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:20:30 by jlagos            #+#    #+#             */
/*   Updated: 2019/06/25 10:20:33 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

unsigned int		check_invalid_tetrom(char *str)
{
	int i;
	int touches;

	i = -1;
	touches = 0;
	while (str[++i])
	{
		if (str[i] == '#')
		{
			if (i != 0 && str[i - 1] == '#')
				touches++;
			if (str[i + 1] == '#')
				touches++;
			if (i > 4 && str[i - 5] == '#')
				touches++;
			if (i < 14 && str[i + 5] == '#')
				touches++;
		}
	}
	if (touches < 6)
		return (0);
	return (1);
}

int					check_if_lines_valid(char *str)
{
	int			i;
	int			check_nl;
	int			block_nbr;

	i = -1;
	check_nl = 4;
	block_nbr = 0;
	while (str[++i])
	{
		if (str[i] == '#')
			block_nbr++;
		if (i == check_nl)
		{
			if (str[i] == '\n')
				check_nl += 5;
			else
				return (0);
		}
		else if (str[i] != '.' && str[i] != '#')
			return (0);
		if (block_nbr > 4)
			return (0);
	}
	return (1);
}

int					check_if_insert_space(char *str, int index)
{
	int	touches;

	touches = 0;
	if (index != 0 && (str[index - 1] == '#' || str[index - 1] == ' '))
		touches++;
	if (str[index + 1] == '#' || str[index + 1] == ' ')
		touches++;
	if (index > 4 && (str[index - 5] == '#' || str[index - 5] == ' '))
		touches++;
	if (index < 14 && (str[index + 5] == '#' || str[index + 5] == ' '))
		touches++;
	if (touches >= 2)
	{
		str[index] = ' ';
		return (1);
	}
	return (0);
}

/*
** create_store_piece(Tetrom *tetrom, char *str)
** Function traverses through string to locate where to assign character space
** The reason I do this is to get the sole shape of the piece
** in string array form (calling ft_strsplit) without it being inside a 4x4 grid
** Example:
** (Before in char array form)		(After in string array form)
** ....(\n)							##
** .##.(\n)			 			 	 #
** . #.(\n)			 			 	 #
** . #.(\n)
** Then functions stores the height, width, and piece itself
*/

void				create_store_piece(t_tetrom *tetrom, char *str)
{
	static char		letter;
	int				i;
	int				s;
	int				flag;

	i = -1;
	s = -5;
	flag = 0;
	if (!letter)
		letter = 'A';
	while (++i < 4)
		insert_spaces(&s, &i, &flag, str);
	i = -1;
	while (((i += 5) <= 20))
		str[i] = '.';
	tetrom->piece = ft_strsplit(str, '.');
	tetrom->alphabet = letter++;
	tetrom->height = ft_2dstrlen(tetrom->piece);
	get_reset_coordinates(tetrom, "both");
}

/*
** Tetrom *assemble_tetrominoes(Tetrom *tetrom, int fd)
** Parses through the file, creates a list if piece is valid and
** adds it onto the linked list of pieces
*/

t_tetrom			*assemble_tetrominoes(t_tetrom *tetrom, int *t_count,
int fd)
{
	t_tetrom		*head;
	t_tetrom		*tmp;
	char			line[BUFFER_SIZE + 1];

	head = tetrom;
	while (read(fd, line, BUFFER_SIZE))
	{
		line[BUFFER_SIZE] = '\0';
		if (!check_if_lines_valid(line) || !check_invalid_tetrom(line))
			return (NULL);
		if (!tetrom)
		{
			if (!(tetrom = (t_tetrom *)malloc(sizeof(*tetrom))))
				return (NULL);
			tmp->next = tetrom;
			tetrom->next = NULL;
		}
		create_store_piece(tetrom, line);
		tmp = tetrom;
		tetrom = tetrom->next;
		(*t_count)++;
		if (!read(fd, line, 1))
			return (head);
	}
	return (NULL);
}
