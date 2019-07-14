/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:22:31 by jlagos            #+#    #+#             */
/*   Updated: 2019/06/25 10:22:46 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetrominoes.h"

void	free_llist(t_tetrom *head)
{
	t_tetrom 	*curr;
	t_tetrom	*temp;
	int			i;

	curr = head;
	while (curr)
	{
		i = -1;
		while (curr->piece[++i])
			ft_strdel(&curr->piece[i]);
		temp = curr->next;
		free(curr);
		curr = temp;
	}
}

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
		if (fd < 0 || !(head = assemble_tetrominoes(&start, &num_of_pieces, fd)))
		{
			ft_putstr("error\n");
			if (!(fd < 0))
				free_llist(head);
			return (0);
		}
		board = fillit(head, num_of_pieces);
		print_grid(board);
		free_llist(head);
	}
	else
		ft_putstr("usage: ./fillit source_file\n");
	return (0);
}
