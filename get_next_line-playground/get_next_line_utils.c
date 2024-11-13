/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:39:06 by luide-ca          #+#    #+#             */
/*   Updated: 2024/11/13 15:39:07 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*find_last_node(t_list *list)
{
	if (!list)
		return (0);
	while (list->next_node)
		list = list->next_node;
	return (list);
}

void	ft_string_copy(t_list *list, char *next_line)
{
	int	k;
	int	i;

	if (!list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				next_line[k++] = '\n';
				next_line[k] = '\0';
				return ;
			}
			next_line[k] = list->content[i++];
		}
		list = list->next_node;
	}
	next_line[k] = '\0';
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(t_list));
	if (!new_lst)
		return (0);
	new_lst->content = content;
	new_lst->next_node = NULL;
	return (new_lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next_node != NULL)
		last = last->next_node;
	last->next_node = new;
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}
