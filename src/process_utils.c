/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:42:37 by yothmani          #+#    #+#             */
/*   Updated: 2023/11/01 14:56:21 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	error(char *msg)
{
	fprintf(stderr, "\n\033[31m\U0001F6A8Error\033[0m: %s\n\n", msg);
	return (EXIT_FAILURE);
}

bool	validation(int argc, char **argv)
{
	int	fd;

	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		error("File descriptor not found\n");
		close(fd);
		return (false);
	}
	close(fd);
	if (argc != 5)
	{
		error("Usage: ./pipex <file1> <cmd1> <cmd2> <file2> \n");
		return (false);
	}
	if (access(argv[1], O_RDONLY) < 0)
	{
		fprintf(stderr, "\nError: The file <%s> does not exist.\n\n", argv[1]);
		return (false);
	}
	return (true);
}

void	child_process(int *fd, char **argv, char **env_path_list, char **envp)
{
	int	fd_in;

	env_path_list = extract_paths(envp);
	fd_in = open(argv[1], O_RDONLY, 0644);
	if (fd_in < 0)
		error(strerror(errno));
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd[0]);
	if (!execute_cmd(env_path_list, argv[2], envp))
		clean_table(env_path_list);
}

void	parent_process(int *fd, char **argv, char **env_path_list, char **envp)
{
	int	fd_out;

	env_path_list = extract_paths(envp);
	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		error(strerror(errno));
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[1]);
	if (!execute_cmd(env_path_list, argv[3], envp))
		clean_table(env_path_list);
}
