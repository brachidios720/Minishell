/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:41:27 by spagliar          #+#    #+#             */
/*   Updated: 2023/06/09 13:41:44 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*ft_read_to_carstock(int fd, char *carstock);
char	*ft_cpy_line(char *line, char *carstock);
char	*ft_freejoin(char *carstock, char *buff);
char	*ft_new_carstock(char *carstock);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *carstock, char *buff);
size_t	ft_strlen(const char *s);

#endif
