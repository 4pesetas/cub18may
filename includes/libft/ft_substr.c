/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iulian <iulian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:41:42 by iumorave          #+#    #+#             */
/*   Updated: 2026/03/19 20:16:03 by iulian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((start > s_len) && (len + start) > (s_len))
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	subs = (char *) malloc ((len + 1) * sizeof (char));
	if (subs == NULL)
		return (NULL);
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

/*int main()
{
	char s[] = "test";
	char *subs = ft_substr(s, 2, 5);
	printf("%s\n", subs);
	free(subs);
	
	return 0;
}*/