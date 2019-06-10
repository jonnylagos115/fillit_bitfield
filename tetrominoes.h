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
# include "./libft_1/includes/libft.h"

typedef struct Tetrominoes
{
	char				**piece;
	char				alphabet;
	int					height;
	int					row[4];
	int					col[4];
	struct Tetrominoes	*next;
}Tetrom;

Tetrom					*assemble_tetrominoes(Tetrom *tetrom, int *tetrom_count, int fd);
Tetrom					*locate_prev_piece(Tetrom *head, char letter);
void					fillit(Tetrom *tetrom, int num_of_tetrom);
char					**create_empty_grid(int len);
char					**ft_2dstrcpy(char **dst, char **src);
char 					**ft_2dstrdup(char **s1, int size);
char					**convert_bitfield(Tetrom *start, int dim);
void					get_reset_coordinates(Tetrom *tetrom, char *str);
void					bit_field_write(unsigned int bit, char width, unsigned int value, unsigned long long *byte);
void    				print_grid(char **grid);
void					print_bits(unsigned char octet);
void					print_bits32(unsigned int octet);
unsigned int			ft_2dstrlen(char **str_arr);
unsigned int 			bit_field_read(unsigned int bit, char width, unsigned int byte);
int						shift_coordinates(Tetrom *tetrom, int size);
int						check_available_spot(Tetrom *tetrom, unsigned long long *grid, int dim);
int						store_place_piece(Tetrom *tetrom, unsigned long long *grid, int dim);
int						starting_board_size(double num);

#endif
