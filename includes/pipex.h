/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:33:43 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/22 19:51:05 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

bool	file_handler(int *fd, char *file_path, bool in_out);
int		error(char *msg);
bool		validation(int argc, char **argv);
char	*ft_itoa(int n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**extract_paths(char **envp);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_cmd_path(char **paths, char *cmd);
void	ft_putstr_fd(char *s, int fd);
bool	execute_cmd(char **paths, char *cmd, char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	clean_table(char **tab);
#endif