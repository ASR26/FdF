/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:02:32 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/16 12:04:05 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_MOUSE_H
# define CONTROL_MOUSE_H

int		mouse_move(int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);
int		mouse_press(int button, int x, int y, void *param);
#endif
