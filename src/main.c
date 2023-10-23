/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:36:21 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/23 13:03:28 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	char	**env_path_list;
	pid_t	pid;

	if (!validation(argc, argv))
	{
		error(" validation failed\n");
		return (1);
	}
	if (pipe(p_fd) < 0)
	{
		error(" pipe creation failed\n");
		return (1);
	}
	env_path_list = extract_paths(envp);
	if (!env_path_list)
	{
		error(" no env path found\n");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		error(" fork failed\n");
		return (1);
	}
	if (pid == 0)
	{
		if (!file_handler(p_fd, argv[1], true))
		{
			return (EXIT_FAILURE);
		}
		if (!execute_cmd(env_path_list, argv[2], envp))
		{
			clean_table(env_path_list);
			return (EXIT_FAILURE);
		}
	}
	waitpid(pid, NULL, 0);
	if (!file_handler(p_fd, argv[argc - 1], false))
	{
		return (EXIT_FAILURE);
	}
	if (!execute_cmd(env_path_list, argv[3], envp))
	{
		clean_table(env_path_list);
		// clean_table(envp);
		return (EXIT_FAILURE);
	}
	clean_table(env_path_list);
	return (EXIT_SUCCESS);
}
