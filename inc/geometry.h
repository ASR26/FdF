/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:36:36 by asolano-          #+#    #+#             */
/*   Updated: 2023/01/09 11:05:58 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

void	traslate(t_point *points, t_point move, int len);
void	scale(t_point *points, int scale, int len);
void	isometric(t_map *map);
void	bending(t_point *points, int len, float range);
void	parallel(t_map *map);
#endif
