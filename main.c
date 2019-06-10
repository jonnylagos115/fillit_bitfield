/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:17:13 by jlagos            #+#    #+#             */
/*   Updated: 2019/02/13 17:27:34 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

int		main(int ac, char **ag)
{
	t_tetrom	start;
	t_tetrom	*head;
	int			fd;
	int			num_of_pieces;
	char		**board;

	if (ac == 2)
	{
		fd = open(ag[1], O_RDONLY);
		num_of_pieces = 0;
		start.next = NULL;
		if (fd < 0)
		{
			ft_putstr("ERROR!\n");
			return (-1);
		}
		if (!(head = assemble_tetrominoes(&start, &num_of_pieces, fd)))
		{
			ft_putstr("error\n");
			return (0);
		}
		board = fillit(head, num_of_pieces);
		print_grid(board);
	}
	return (0);
}
