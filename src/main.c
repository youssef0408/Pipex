/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:36:21 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/24 16:27:44 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  infile => pipe(o) ==> pipe(1) ==> outfile

#include "../includes/pipex.h"

int	main4(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	char	**env_path_list;
	pid_t	pid;
	pid_t	pid2;
	int		j;

	// if (! validation(argc, argv) ){
	// 		error(" validation failed\n");
	// 		return (1);
	// }
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
	if (!file_handler(p_fd, argv[argc - 1], false))
	{
		return (EXIT_FAILURE);
	}
	if (!file_handler(p_fd, argv[1], true))
	{
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		error(" fork failed\n");
		return (1);
	}
	if (pid == 0)
	{
		if (!execute_cmd(env_path_list, argv[2], envp))
		{
			clean_table(env_path_list);
			return (EXIT_FAILURE);
		}
	}
	j = 3;
	while (j < argc - 2)
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			error(" fork failed\n");
			return (1);
		}
		if (pid2 == 0)
		{
			close(p_fd[0]);
			dup2(p_fd[1], STDOUT_FILENO);
			if (!execute_cmd(env_path_list, argv[j], envp))
			{
				clean_table(env_path_list);
				return (EXIT_FAILURE);
			}
		}
		else
		{
			close(p_fd[1]);
			dup2(p_fd[0], STDIN_FILENO);
			waitpid(pid2, NULL, 0);
		}
		j++;
	}
	
	if (!execute_cmd(env_path_list, argv[argc - 2], envp))
	{
		clean_table(env_path_list);
		// clean_table(envp);
		return (EXIT_FAILURE);
	}
	clean_table(env_path_list);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	char	**env_path_list;
	pid_t	pid;

	if (!validation(argc, argv))
	{
		// error(" validation failed\n");
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
		waitpid(pid, NULL, 0);
	}
	if (!file_handler(p_fd, argv[argc - 1], false))
	{
		clean_table(env_path_list);
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
