/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:25:10 by luide-ca          #+#    #+#             */
/*   Updated: 2024/11/13 13:25:11 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next_node;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node->content[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

void	ft_clean_line(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	clean_node = (t_list *)malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->content[i] != '\0'
		&& last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] != '\0'
		&& last_node->content[++i])
		buf[k++] = last_node->content[i];
	buf[k] = '\0';
	clean_node->content = buf;
	clean_node->next_node = NULL;
	dealloc(list, clean_node, buf);
}

char	*ft_get_line(t_list *list)
{
	int		len;
	int		i;
	char	*next_line;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				break ;
			}
			i++;
			len++;
		}
		list = list->next_node;
	}
	next_line = (char *)malloc((len + 1) * sizeof(char));
	if (next_line)
		return (0);
	ft_string_copy(list, next_line);
	return (next_line);
}

void	ft_create_lst(t_list **lst, int fd)
{
	char	*buffer;
	t_list	*lst_node;
	int		num_char;

	num_char = 1;
	while (!ft_strchr(buffer, '\n') && num_char > 0)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return ;
		num_char = read(fd, buffer, BUFFER_SIZE);
		if (!num_char)
		{
			free(buffer);
			return ;
		}
		buffer[num_char] = '\0';
		lst_node = ft_lstnew(buffer);
		ft_lstadd_back(lst, lst_node);
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*next_line;
	int				read_value;

	read_value = read(fd, &next_line, BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (read_value < 0)
	{
		free(lst);
		return (0);
	}
	ft_create_lst(&lst, fd);
	if (!lst)
		return (0);
	next_line = ft_get_line(lst);
	ft_clean_line(&lst);
	return (next_line);
}
