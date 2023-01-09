/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:40:05 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/16 12:42:50 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

int		draw_map(t_meta *meta, int fit);
void	load_map(t_map *map, char *path);
void	generate_background(t_meta *meta, int backcolor, int menucolor);
void	draw_menu(t_meta *meta);
void	load_color(int max, int min, t_point *point, t_colors colors);
void	generate_stars(t_meta *meta);
#endif
