/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:04:13 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/26 13:10:01 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_UTILS_H
# define CONTROL_UTILS_H

void	angle_control(int key, t_meta *meta);
void	angle(float *ang, float value);
void	colorize(t_map *map);
int		terminate_program(void *param);
void	terminate(char *s);
void	control_colorscheme(int key, t_map *map);
#endif
