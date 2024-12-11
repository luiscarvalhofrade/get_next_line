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

void	ft_reorg_lst(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buffer;

	if (!list)
		return ;
	buffer = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buffer || !clean_node)
		return ;
	last_node = ft_find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[i++])
		buffer[k++] = last_node->content[i];
	buffer[k] = '\0';
	clean_node->content = buffer;
	clean_node->next_node = NULL;
	ft_free(list, clean_node, buffer);
}

char	*ft_get_line(t_list *list)
{
	int		new_line_len;
	char	*new_line;

	if (!list)
		return (0);
	new_line_len = ft_len_of_new_line(list);
	new_line = malloc(new_line_len + 1);
	if (!new_line)
		return (0);
	ft_copy_string(list, new_line);
	return (new_line);
}

void	ft_append_buffer(t_list **list, char *buffer, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_find_last_node(list[fd]);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		list[fd] = new_node;
	else
		last_node->next_node = new_node;
	new_node->content = buffer;
	new_node->next_node = NULL;
}

void	ft_create_lst(t_list **list, int fd)
{
	int		char_read;	
	char	*buffer;

	while (!ft_found_new_line(list[fd]))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read == -1)
		{
			free(buffer);
			ft_free(&list[fd], NULL, NULL);
			return ;
		}
		if (char_read == 0)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		ft_append_buffer(list, buffer, fd);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	char			*next_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (0);
	ft_create_lst(list, fd);
	if (!list[fd])
	{
		ft_free(&list[fd], NULL, NULL);
		return (0);
	}
	next_line = ft_get_line(list[fd]);
	if (!next_line)
	{
		ft_free(&list[fd], NULL, NULL);
		return (0);
	}
	ft_reorg_lst(&list[fd]);
	return (next_line);
}
