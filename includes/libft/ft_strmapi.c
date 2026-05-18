/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:21:38 by iumorave          #+#    #+#             */
/*   Updated: 2026/03/19 20:15:53 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	int				len;
	unsigned int	i;

	len = ft_strlen(s);
	i = 0;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_str[len] = '\0';
	while (s[i])
	{
		new_str[i] = (*f)(i, s[i]);
		i++;
	}
	return (new_str);
}

/*char f(unsigned int i, char c)
{
	return c - 32;
}
int main()
{
	char s[] = "abcdef";

	char *new = ft_strmapi(s, f);
	printf("%s\n", new);
	free (new);
	return 0;
}*/