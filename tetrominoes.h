/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrominoes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlagos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:26:01 by jlagos            #+#    #+#             */
/*   Updated: 2019/03/26 11:26:16 by jlagos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETROMINOES_H
# define TETROMINOES_H
# define BUFFER_SIZE 20
# define FIELD_WIDTH 1
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include "./libft_1/libft.h"

typedef struct			s_tetrom
{
	char				**piece;
	char				alphabet;
	int					row[4];
	int					col[4];
	int					height;
	struct s_tetrom		*next;
}						t_tetrom;

typedef struct			s_point
{
	int i;
	int j;
	int curr;
}						t_point;

t_tetrom				*assemble_tetrominoes(t_tetrom *tetrom,
int *t_count, int fd);
t_tetrom				*locate_piece(t_tetrom *head, char letter);
char					**fillit(t_tetrom *tetrom, int num_of_tetrom);
char					**create_empty_grid(int len);
char					**convert_bitfield(t_tetrom *start, int dim);
void					get_reset_coordinates(t_tetrom *tetrom, char *str);
void					clear_reset_pieces(t_tetrom *head, uint64_t *grid,
int *dim);
void					insert_spaces(int *s, int *i, int *flag, char *str);
void					bit_field_write(unsigned int bit,
unsigned int value, uint64_t *byte);
void					print_grid(char **grid);
void					print_bits32(unsigned int octet);
int						check_if_insert_space(char *str, int index);
int						shift_coordinates(t_tetrom *tetrom, int size);
int						check_available_spot(t_tetrom *tetrom,
uint64_t *grid, int dim);
int						store_place_piece(t_tetrom *tetrom, uint64_t *grid,
int dim);
int						starting_board_size(double num);

#endif
