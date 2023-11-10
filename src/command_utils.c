/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yothmani <yothmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:34:43 by yothmani          #+#    #+#             */
/*   Updated: 2023/11/10 13:53:26 by yothmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

bool	execute_cmd(char *cmd, char **envp)
{
	char	**tmp;
	char	*cmd_path;
	char	*error_msg;

	tmp = ft_split(cmd, ' ');
	cmd_path = get_cmd_path(tmp[0], envp);
	if (!cmd_path)
	{
		clean_table(tmp);
		error_msg = ft_strjoin("command not found: ", cmd);
		error(error_msg);
		free(error_msg);
		return (false);
	}
	if (execve(cmd_path, tmp, envp) == -1)
		return (false);
	free(cmd_path);
	clean_table(tmp);
	return (true);
}

char	**extract_paths(char **envp)
{
	char	**paths_tab;
	char	*path;

	if (!envp)
		return (NULL);
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	path = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	paths_tab = ft_split(path, ':');
	free(path);
	return (paths_tab);
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
