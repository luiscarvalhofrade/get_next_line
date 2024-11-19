/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:40:02 by luide-ca          #+#    #+#             */
/*   Updated: 2024/11/12 15:40:03 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	if (list == NULL)
		return ;
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[i++])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_line_db(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_new_line(list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	append(t_list **list, char *buf, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(list[fd]);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int		char_read;	
	char	*buf;

	while (!found_new_line(list[fd]))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == -1)
		{
			free(buf);
			dealloc(&list[fd], NULL, NULL);
			return ;
		}
		if (char_read == 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf, fd);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*next_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(list, fd);
	if (list[fd] == NULL)
	{
		dealloc(&list[fd], NULL, NULL);
		return (NULL);
	}
	next_line = get_line_db(list[fd]);
	if (next_line == NULL)
	{
		dealloc(&list[fd], NULL, NULL);
		return (NULL);
	}
	polish_list(&list[fd]);
	return (next_line);
}
