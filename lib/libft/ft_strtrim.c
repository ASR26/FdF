/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:00:51 by asolano-          #+#    #+#             */
/*   Updated: 2022/04/28 13:06:38 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Esta función elimina los caracteres de la string set del principio y del 
 * final de s1 hasta que encuentre un caracter que no pertenezca a set*/

#include"libft.h"

int	ft_checker(char ch1, char const *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (ch1 == s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	len;
	unsigned int	i;

	if (!s1)
		return (0);
	start = 0;
	while (ft_checker(s1[start], (char *) set))
		start++;
	len = 0;
	i = 0;
	while (s1[start + i])
	{
		if (!ft_checker(s1[start + i], (char *) set))
			len = i + 1;
		i++;
	}
	return (ft_substr(s1, start, len));
}
/*
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	start;
	size_t	end;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (ft_checker(s1[start], set))
		start++;
	if (start == ft_strlen(s1))
	{
		if (!(newstr = ft_strdup("")))
			return (0);
		else
			return (newstr);
	}
	while (ft_checker(s1[end - 1], set))
		end--;
	newstr = ft_substr(s1, start, end - start);
	return (newstr);
}*/
