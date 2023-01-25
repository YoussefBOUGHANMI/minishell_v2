void	ft_command(char *cmd)
{
	int	pid;
	char	*new_argv[] = { cmd, NULL };
	char 	*new_envp[] = { NULL };

	if (parce_command(cmd))
	{
		pid = fork();
		if (pid == 0)
		{
			(execve("/bin/ls", new_argv, new_envp));
		}
	}
	else
		printf("%s%s\n", "cmd not found: ", cmd);
}