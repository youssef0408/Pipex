/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:36:21 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/17 21:35:07 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	num1;
	int	num2;
	int	valid;
	


	printf("envp is: %s\n", envp[2]);
	


	valid = validation(argc, argv);
	if (valid < 0)
		error(valid, "validation error Code ");
	if (pipe(fd) < 0)
		return (1);
	file_handler(fd[1], "./input.txt", true);
	// parsing of the cmd from arg[2]
	scanf("%d %d", &num1, &num2);
	file_handler(fd[0], "./output.txt", false);
	// exec command from arg[3]
	printf("salut = %d", num1 + num2);
	return (0);
}
