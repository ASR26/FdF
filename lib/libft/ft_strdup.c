/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:33:01 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 10:13:12 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función aloja suficiente memoria para copiar s1, hace la copia y devuelve
 * un puntero al string, si no hay suficiente memoria devuelve 0*/
#include"libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		str_length;

	s2 = 0;
	str_length = ft_strlen(s1) + 1;
	s2 = malloc(sizeof (char) * str_length);
	if (s2 == 0)
		return (0);
	ft_strlcpy(s2, s1, str_length);
	return (s2);
}
