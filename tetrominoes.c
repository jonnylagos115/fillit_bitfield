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

/*
** Checks if the tetromino is a valid shape.
**
** Returns 0 on valid shape, 1 on invalid shape.
*/

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

/*
**	Checks the piece for proper formatting. Doesn't check if the
**	piece is a valid shape, check_invalid_tetrom does that.
**
**	Returns 0 on invalid format, 1 on valid.
*/

int					check_if_lines_valid(char *str)
{
	int			i;
	int			block_nbr;

	i = -1;
	block_nbr = 0;
	while (str[++i])
	{
		if (str[i] == '#')
			block_nbr++;
		if ((i + 1) % 5 == 0 ? str[i] != '\n' : str[i] != '.' && str[i] != '#')
			return (0);
	}
	return ((block_nbr == 4) ? 1 : 0);
}

/*
**	Function traverses through str (string containing piece from the file)
**	to locate where to assign ' '.
**	The reason I do this is to get the sole shape of the piece in string array
**	form (calling ft_strsplit).
**	Example:
**	(before changes)		(with ' ' added)		(After using ft_strsplit)
**	 ....(\n)				 ....(\n)				 ##(\0)
**	 .##.(\n)				 .##.(\n)			 	  #(\0)
**	 ..#.(\n)				 . #.(\n)			 	  #(\0)
**	 ..#.(\n)(\0)			 . #.(\n)(\0)
**	Then it stores the size and piece itself(from ft_strsplit) in the list.
*/

void				create_store_piece(t_tetrom *tetrom, char *str, int *tc)
{
	static char		letter;
	int				i;

	i = -1;
	if (!letter)
		letter = 'A';
	insert_spaces(str);
	while (((i += 5) <= 20))
		str[i] = '.';
	tetrom->piece = ft_strsplit(str, '.');
	tetrom->alphabet = letter++;
	tetrom->height = ft_2dstrlen(tetrom->piece);
	tetrom->width = ft_strlen(tetrom->piece[0]);
	(*tc)++;
	get_reset_coordinates(tetrom);
}

/*
**	Parses through the file, and creates a list for every valid piece
**	that is encountered and adds it onto the linked list of pieces.
**
**	Returns 0 on failure or invalid file, 1 on success. Blame Jonny for this.
*/

int					assemble_tetrominoes(t_tetrom *tetrom, int *t_count,
int fd)
{
	t_tetrom		*tmp;
	char			line[BUFFER_SIZE + 1];

	while (read(fd, line, BUFFER_SIZE) > 0)
	{
		line[BUFFER_SIZE] = '\0';
		if (!check_if_lines_valid(line) || !check_invalid_tetrom(line))
			return (0);
		if (!tetrom)
		{
			if (!(tetrom = (t_tetrom *)malloc(sizeof(*tetrom))))
				return (0);
			tmp->next = tetrom;
			tetrom->next = NULL;
		}
		create_store_piece(tetrom, line, t_count);
		tmp = tetrom;
		tetrom = tetrom->next;
		if (!read(fd, line, 1) || line[0] != '\n')
			return ((read(fd, line, 1)) == 0 ? 1 : 0);
	}
	return (0);
}
