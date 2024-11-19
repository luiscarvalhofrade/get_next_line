/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:53:47 by luide-ca          #+#    #+#             */
/*   Updated: 2024/11/11 15:53:49 by luide-ca         ###   ########.fr       */
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
	char			*str_buf;
	struct s_list	*next;
}					t_list;

char	*get_line_db(t_list *list);
char	*get_next_line(int fd);

int		found_new_line(t_list *list);
int		len_to_new_line(t_list *list);

void	copy_str(t_list *list, char *str);
void	create_list(t_list **list, int fd);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
void	polish_list(t_list **list);

t_list	*find_last_node(t_list *list);

#endif
