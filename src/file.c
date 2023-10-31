/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:34:43 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/31 17:53:29 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

bool	file_handler(int *fd_p, char *file_path, bool in_out)
{
	int	fd;
	int	fd_1;
	int	fd_2;
	int	permission;

	permission = O_RDONLY;
	fd_1 = STDIN_FILENO;
	fd_2 = STDOUT_FILENO;
	if (!in_out)
	{
		permission = O_WRONLY | O_CREAT | O_TRUNC;
		fd_1 = STDOUT_FILENO;
		fd_2 = STDIN_FILENO;
	}
	if (in_out && access(file_path, permission) < 0)
	{
		fprintf(stderr, "\nError: <%s> does not exist.\n\n", file_path);
		return (false);
	}
	fd = open(file_path, permission, 0644);
	if (fd < 0)
		return (error(strerror(errno)), false);
	if (dup2(fd, fd_1) == -1)
		return (error("input file descriptor failed \n"), false);
	if (dup2(fd_p[fd_2], fd_2) == -1)
		return (error("output file descriptor failed \n"), false);
	close(fd_p[fd_1]);
	return (true);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (access(cmd_path, F_OK) == 0)
		{
			clean_table(paths);
			paths = NULL;
			return (cmd_path);
		}
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	return (NULL);
}

void	clean_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

bool	execute_cmd(char **paths, char *cmd, char **envp)
{
	char	**tmp;
	char	*cmd_path;
	char	*error_msg;

	tmp = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(paths, tmp[0]);
	if (!cmd_path)
	{
		clean_table(tmp);
		tmp = NULL;
		error_msg = ft_strjoin("command not found: ", cmd);
		error(error_msg);
		free(error_msg);
		return (false);
	}
	if (execve(cmd_path, tmp, envp) == -1)
	{
		free(cmd_path);
		clean_table(tmp);
		error("execution failed!");
		return (false);
	}
	free(cmd_path);
	clean_table(tmp);
	return (true);
}
