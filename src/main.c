/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:36:21 by yothmani          #+#    #+#             */
/*   Updated: 2023/11/09 19:39:30 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	char	**env_path_list;
	pid_t	pid;

	if (!validation(argc, argv))
		return (EXIT_FAILURE);
	if (pipe(p_fd) < 0)
		return (error(" pipe creation failed\n"));
	env_path_list = extract_paths(envp);
	if (!env_path_list)
		return (error(" no env path found\n"));
	pid = fork();
	if (pid == -1)
	{
		clean_table(env_path_list);
		return (error(" fork failed\n"));
	}
	if (pid == 0)
		child_process(p_fd, argv, env_path_list, envp);
	waitpid(pid, NULL, 0);
	parent_process(p_fd, argv, env_path_list, envp);
	clean_table(env_path_list);
	return (EXIT_SUCCESS);
}
