#include "../../include/minishell.h"

int exec_ast(t_node *node, t_env *env_list, int *last_exit)
{
    if (!node)
        return (1); //erro generico
    if (node->type == NODE_COMMAND)
        return (exec_command_node(node, env_list, last_exit));
    if (node->type == NODE_PIPE)
        return (exec_pipe_node(node, env_list, last_exit));
    return (1);
}

int exec_command_node(t_node *node, t_env *env_list, int *last_exit)
{
	pid_t	pid;
	int	status;
	
	if (!node->av || !node->av[0])
        	return (1);
    	if (is_builtin(node->av[0]))
	{
        	//*last_exit = execute_builtin(node->av, env_list);  depois pegar a saida, e retornar. Mas vou ter que mudar funcao execute_builtin que e void
		execute_builtin(node->av, env_list);
		return (0);
	}
    	pid = fork();
    	if (pid == 0)
    	{
        	execve(resolve_path(node->av[0], env_list), node->av, env_to_array(env_list));
        	perror("execve");
        	exit(127);
    	}
    	waitpid(pid, &status, 0);
    	if (WIFEXITED(status))
        	*last_exit = WEXITSTATUS(status);
   	 return (*last_exit);
}
