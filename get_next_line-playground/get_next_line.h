/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:58:19 by luide-ca          #+#    #+#             */
/*   Updated: 2024/11/13 13:58:21 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next_node;
}					t_list;

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_get_line(t_list *list);

t_list	*find_last_node(t_list *list);
t_list	*ft_lstnew(void *content);

void	ft_string_copy(t_list *list, char *next_line);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_create_lst(t_list **lst, int fd);
void	ft_clean_line(t_list **list);
void	dealloc(t_list **list, t_list *clean_node, char *buf);

#endif
