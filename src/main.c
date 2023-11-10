/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:36:21 by yothmani          #+#    #+#             */
/*   Updated: 2023/11/10 14:26:35 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	pid_t	pid;

	if (!validation(argc, argv))
		return (1);
	if (pipe(p_fd) == -1)
		error(" pipe creation failed\n");
	pid = fork();
	if (pid == -1)
		error(" fork failed\n");
	if (pid == 0)
		child_process(p_fd, argv, envp);
	waitpid(pid, NULL, 0);
	parent_process(p_fd, argv, envp);
	return (0);
}
