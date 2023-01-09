/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:01:04 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/21 09:34:47 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función mide cuantos caracteres tiene una cadena y devuelve la longitud*/
int	ft_strlen(char *a)
{
	long	l;

	l = 0;
	while (a[l] != 0)
		l++;
	return (l);
}
