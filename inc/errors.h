/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:36:08 by asolano-          #+#    #+#             */
/*   Updated: 2022/09/16 12:36:16 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_ARGS		"❌Incorrect number of arguments, expected 1"
# define ERR_OPEN		"❌Error opening the file"
# define ERR_READ		"❌Error reading the file"
# define ERR_SPLIT		"❌Error splitting the line"
# define ERR_LINE		"\n❌Error: nº of elements is different for each line"
# define ERR_EMPTY		"❌Error: the file is empty or wrongly formatted"
# define ERR_MEM		"❌Memory error"
# define ERR_MAP		"❌Map Error"

void	terminate(char *s);
#endif
