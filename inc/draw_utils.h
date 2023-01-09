/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:31:26 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/16 12:33:22 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H

int		draw_line(t_meta *meta, t_point start, t_point end);
void	draw_dot(t_meta *meta, t_point point, int radius);
int		gradient(int startcolor, int endcolor, int len, int pix);
int		my_putpixel(t_meta *meta, t_point pixel);
void	shadow(t_point *points, int len);
#endif
