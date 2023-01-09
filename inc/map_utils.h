/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:44:59 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/23 10:46:47 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

void	colorize(t_map *map);
void	wired(t_meta *meta, t_point *wire);
void	doted(t_meta *meta, t_point *proyect);
void	z_division(t_point *proyect, float divisor, int len);
void	map_ini(t_map *map, int total);
void	show_info(t_map *map);
int		line_elems(char **elems);
void	z_limits(char **splitted, t_map *map);
int		valid_point(char *value);
#endif
