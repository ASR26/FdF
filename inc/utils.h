/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:55:12 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/28 11:13:47 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	dbl_free(char **ptr);
int		ft_round(double num);
void	matrix_init(float (*matrix)[3]);
void	print_nbr(t_meta *meta, int x, int y, int nbr);
void	print_str(t_meta *meta, int x, int y, char *str);
void	copy_map(t_point *src, t_point *dst, int len);
int		valid_pixel(t_point pixel);
#endif
