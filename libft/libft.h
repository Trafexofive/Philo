/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:58:54 by mlamkadm          #+#    #+#             */
/*   Updated: 2023/12/02 19:51:21 by mlamkadm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>

# define BUFFER_SIZE 5

//categorize functions provide documention when nesessary


//string manipulation
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

size_t	ft_strlen(const char *c);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	**ft_split(const char *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
long	ft_atoi(const char *str);
char	*get_next_line(int fd);
int		ft_find_nl(char *s, int c);

#endif