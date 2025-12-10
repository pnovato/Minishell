#include "../../include/minishell.h"

int	exec_heredoc(t_node *node, t_env *env_list, int *last_exit)
{
	char	*line;
	int	pipe_fd[2];
	(void)env_list;
	(void)*last_exit;

	if (pipe(pipe_fd) == -1)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, node->redirect_file) == 0)
		{
			free(line);
			break;
		}
		//printf("heredoc: linha = [%s]\n", line);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	node->heredoc_fd = pipe_fd[0];
	node->type = NODE_LREDIRECT;
	//printf("heredoc: pipe criado com fd = %d\n", pipe_fd[0]);
	return (0);
}
