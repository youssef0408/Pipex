/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:56:39 by yothmani          #+#    #+#             */
/*   Updated: 2023/10/25 21:59:09 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// 2 fichier 
// 3 cmd
// fd |  p1|p2 |p3 |outfile 



bool	cmd_handler(int *fd_c, char **argv, bool in_out)
{
	int	fd_1;
	int	fd_2;
	
	fd_1 = STDIN_FILENO; 
	fd_2 = STDOUT_FILENO; 
	if (!in_out)
	{
		fd_1 = STDOUT_FILENO;
		fd_2 = STDIN_FILENO; 
	}
	if (dup2(fd_c[fd_1], fd_1) == -1)
	{
		error("input file descriptor failed \n");
		return (false);
	}

	if (dup2(fd_c[fd_2], fd_2) == -1)
	{
		error("output file descriptor failed \n");
		return (false);
	}
	
	close(fd_c[fd_1]);
	return (true);
}


int	main(int argc, char **argv, char **envp)
{
	int		p_fd[2];
	char	**env_path_list;
	pid_t	pid;

	// if (!validation(argc, argv))
	// 	return (1);
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
			return (EXIT_FAILURE);
		if (!execute_cmd(env_path_list, argv[2], envp))
		{
			clean_table(env_path_list);
			return (EXIT_FAILURE);
		}
		int i = 2;
		bool in_out;
		// int fd_c[10];
		in_out = true;
		// int	p = 1;
		while(i + 1 <= argc - 3 )
		{
			if (pipe(p_fd) < 0)
			{
				error(" pipe creation failed\n");
				return (1);
			}
			if (!cmd_handler(p_fd, in_out))
				return (EXIT_FAILURE);
			if (!execute_cmd(env_path_list, argv[i], envp))
			{
				clean_table(env_path_list);
				return (EXIT_FAILURE);
			}
			// p++;
			i++;
			in_out =!in_out;
			// j++;
			waitpid(pid, NULL, 0);
		}
	}
	if (!file_handler(p_fd, argv[argc - 1], false))
	{
		clean_table(env_path_list);
		return (EXIT_FAILURE);
	}
	if (!execute_cmd(env_path_list, argv[argc - 2], envp))
	{
		clean_table(env_path_list);
		return (EXIT_FAILURE);
	}
	clean_table(env_path_list);
	return (EXIT_SUCCESS);
}







// bool	file_output2(int *fd_p, char *file_path,int j)
// {
// 	int	fd;

// 	if ( access(file_path,  O_WRONLY | O_CREAT | O_TRUNC) < 0)
// 	{
// 		fprintf(stderr, "\nError: The file <%s> does not exist.\n\n",
// 			file_path);
// 		return (false);
// 	}
// 	fd = open(file_path,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		error(strerror(errno));
// 		return (false);
// 	}
	
// 	if (dup2(fd, 1) == -1)
// 	{
// 		error("input file descriptor failed \n");
// 		return (false);
// 	}
// 	fprintf(stderr, "\nError: ====The file <%d> does not exist.\n\n",
// 			j);
// 	if (dup2(fd_p[j-1], 0) == -1)
// 	{
// 		error("output file descriptor failedqqqq \n");
// 		return (false);
// 	}
	
// 	close(fd_p[j]);
// 	return (true);
// }



// int	child_process(int *p_fd, char **env_path_list,char **envp,bool in_out,char **argv,int j)
// {

// 	pid_t	pid;

// (void )in_out;


// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		error(" fork failed\n");
// 		return (1);
// 	}

	
// 	if (pid == 0)
// 	{
		
		
// 			dup2(p_fd[j-1], 0);
// 		dup2(p_fd[j], 1);
	
	
	
		
// 		if (!execute_cmd(env_path_list, argv[j], envp))
// 		{
// 			fprintf(stderr, "error commande %s\n", argv[j]);
			
// 			clean_table(env_path_list);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 			dup2(p_fd[j-1], 0);
// 		dup2(p_fd[j], 1);
// 		waitpid(pid, NULL, 0);
// 		fprintf(stderr, "commande 2 %s\n", argv[j]);
// 		if (!execute_cmd(env_path_list, argv[j], envp))
// 		{
// 			fprintf(stderr, "error commande 2%s\n", argv[j]);
// 			clean_table(env_path_list);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	return (0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	int		p_fd[6];
// 	char	**env_path_list;
// 	pid_t	pid;
	
// 	int		j;

// 	// if (!validation(argc, argv))
// 	// {
// 	// 	error(" validation failed\n");
// 	// 	return (1);
// 	// }
// 	if (pipe(p_fd) < 0)
// 	{
// 		error(" pipe creation failed\n");
// 		return (1);
// 	}
// 	env_path_list = extract_paths(envp);
// 	if (!env_path_list)
// 	{
// 		error(" no env path found\n");
// 		return (1);
// 	}
// 	if (!file_handler(p_fd, argv[1], true))
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		error(" fork failed\n");
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
// 		if (!execute_cmd(env_path_list, argv[2], envp))
// 		{
// 			clean_table(env_path_list);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	j = 3;
// 	bool in_out;
// 	in_out=false;
// 	while (j < argc - 2)
// 	{
// 		child_process(p_fd, env_path_list,envp,in_out,argv,j);
// 			j++;
// 			in_out=!in_out;
// 	}
// 	// if (!file_handler(p_fd, argv[argc - 1], true))
// 	// {
// 	// 	return (EXIT_FAILURE);
// 	// }
	
// 	if (!file_output2(p_fd, argv[argc - 1], j))
// 	{
// 		return (EXIT_FAILURE);
// 	}
// 	if (!execute_cmd(env_path_list, argv[argc - 2], envp))
// 	{
// 		clean_table(env_path_list);
// 		return (EXIT_FAILURE);
// 	}
// 	clean_table(env_path_list);
// 	return (EXIT_SUCCESS);
// }
