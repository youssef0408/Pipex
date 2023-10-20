/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:36:21 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/20 00:45:22 by yothmani         ###   ########.fr       */
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
	if (valid < 0)
		error("validation error Code ");
	if (pipe(p_fd) < 0)
		return (1);
	env_path_list = extract_paths(envp);
	pid = fork();
	if (pid == -1)
		error(" no child process is created");
	if (pid == 0)
	{
		file_handler(p_fd, argv[1], true);
		if (execute_cmd(env_path_list, argv[2], envp))
			error("exec error 1st cmd");
	}
	waitpid(pid, NULL, 0);
	file_handler(p_fd, argv[argc - 1], false);
	if (execute_cmd(env_path_list, argv[3], envp))
		error("exec error 2nd cmd");
	return (0);
}
