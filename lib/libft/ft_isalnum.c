/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 09:44:12 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 08:49:48 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función comprueba que el carácter introducido es una letra o un número,
 *devuelve 1 * si lo es y 0 si no*/
int	ft_isalnum(int a)
{
	if ((a >= '0' && a <= '9' ) || (a >= 'a' && a <= 'z')
		|| (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}
