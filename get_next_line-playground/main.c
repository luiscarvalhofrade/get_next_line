/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:53:03 by luide-ca          #+#    #+#             */
/*   Updated: 2024/11/13 17:53:04 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;

    // Check if the filename is provided
    if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return (1);
    }

    // Open the file for reading
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Read and print each line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line); // `get_next_line` should include the newline, so no need for \n
        free(line); // Free the line after use
    }

    // Close the file
    close(fd);
    return (0);
}
