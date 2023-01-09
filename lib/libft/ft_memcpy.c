/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:29:48 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/27 09:06:54 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Esta función sustituye size caracteres el valor en memoria de src a dest, si 
 * src y dest se solapan el resultado será indefinido*/
#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	char	*temp_dest;
	char	*temp_src;

	if (size == 0 || dest == src)
		return (dest);
	if (!dest && !src)
		return (0);
	temp_src = (char *)src;
	temp_dest = (char *)dest;
	while (size--)
		temp_dest[size] = temp_src[size];
	return (dest);
}
