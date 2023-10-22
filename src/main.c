/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:36:21 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/22 03:06:09 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	int		valid;
	char	**env_path_list;
	pid_t	pid;

	valid = validation(argc, argv);
	if (valid != 0)
		return (EXIT_FAILURE);
	if (pipe(p_fd) < 0)
		error(" pipe creation failed\n");
	env_path_list = extract_paths(envp);
	if (!env_path_list)
		error(" no env path found\n");
	pid = fork();
	if (pid == -1)
		error(" fork failed\n");
	if (pid == 0)
	{
		file_handler(p_fd, argv[1], true);
		if (execute_cmd(env_path_list, argv[2], envp) == 1)
		{
			clean_table(env_path_list);
			clean_table(envp);
			return (EXIT_FAILURE);
		}
	}
	waitpid(pid, NULL, 0);
	file_handler(p_fd, argv[4], false);
	if (execute_cmd(env_path_list, argv[3], envp) == 1)
	{
		clean_table(env_path_list);
		clean_table(envp);
		return (EXIT_FAILURE);
	}
	clean_table(env_path_list);
	return (EXIT_SUCCESS);
}
