// TODO: search adapter

// (1) *fix the structure with the strcombine thing : (√)
// (2) *Using relative paths.                       : (√)
// (3) *xecuting directories.                       : (√)
// (4) *check LEAKS(),                              : ()
// Checking commands without a path or when PATH is empty.

#include "../include/execution.h"
#include <sys/stat.h>
#include <errno.h>
void	err_write(char *minishell, char *cmd, char *err, int status)
{
	if (errno == ENOTDIR)
	{


		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
	}
	else
	{
		ft_putstr_fd(minishell, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(err, 2);
	}
	exit(status);
}

int	is_directory(char *path)
{
	struct stat	p_stat;

	stat(path, &p_stat);
	if (S_ISDIR(p_stat.st_mode))
		return (1);
	return (0);
}
int	check_access(char *path)
{
	int	status;

	status = 0;
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (status);
		else
		{
			status = 1;
			return (status);
		}
	}
	else
	{
		status = 2;
		return (status);
	}
}

char	*expand_cmd_path(char *path, char *cmd)
{
	char	*cmd_slash;
	char	*rtrn_path;
	int		status;

	if (!cmd[0])
		return (NULL);
	if ((ft_strchr(cmd, '/') && is_directory(cmd)) || is_directory(cmd))
		err_write("minishell: ", cmd, ": is a directory\n", 126);
	if (ft_strchr(cmd, '/'))
	{
		status = check_access(cmd);
		if (status == 2)
				err_write("minishell: ", cmd, ": No such file or directory\n", 127);
		else if (status == 1)
			err_write("minishell: ", cmd, ": Permission denied\n", 126);
		return (cmd);
	}
	if (!path)
		return (NULL);
	cmd_slash = strcombine(path, "/", false); // (|) *FREE CMD_SLASH
		////****// *FREE() (1) FREE_PATH  (2) FREE_CMD(AST->ARG)
	rtrn_path = strcombine(cmd_slash, cmd, false);
	free(cmd_slash);
	return (rtrn_path);
}

char	*check_cmd(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;
	int		status;

	i = 0;
	status = 0;
	cmd_path = NULL;
	if (!paths)
		cmd_path = expand_cmd_path(NULL, cmd);
	while (paths && (paths)[i])
	{
		cmd_path = expand_cmd_path(paths[i++], cmd);
		status = check_access(cmd_path);
		if (!status)
			return (cmd_path);
		else if (status == 1)
			err_write("minishell: ", cmd_path, ": Permission denied\n", 126);
	}
	if (status == 0 && !ft_strchr(cmd, '/'))
		err_write("minishell: ", cmd, ": No such file or directory\n", 127);
	if (status == 2)
		err_write("minishell: ", cmd, ": command not found\n", 127);
	return (cmd_path);
}

char	*cmd_expand(char *cmd, char **paths)
{
	char *check_return ;
	check_return = 0;
	if (!cmd)
		exit(0);
	check_return = check_cmd(paths, cmd);
	// system("leaks -q minishell"); //**LEAKS TEST**//=
	return (check_return); //add "/"  //add CMD
}
