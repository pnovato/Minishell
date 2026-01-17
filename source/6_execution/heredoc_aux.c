#include "../../include/minishell.h"

int transform_heredoc_node(t_node *node)
{
    t_node *new_left;

    new_left = copy_ast(node->left);
    if (!new_left)
        return (1);
    free_ast(node->left);
    node->left = new_left;
    node->right = NULL;
    node->type = NODE_LREDIRECT;
    return (0);
}

int heredoc_wait_parent(pid_t pid, int rfd, int *last_exit)
{
    int status;

    setup_signals_waiting();
    waitpid(pid, &status, 0);
    setup_signals_main();
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        write(1, "\n", 1);
        close(rfd);
        *last_exit = 130;
        g_signal_status = 131;
        return (1);
    }
    return (0);
}

void run_heredoc_child(t_node *node, t_shell *sh, int *pipe_fd, int last_exit)
{
    close(pipe_fd[0]);
    setup_signals_heredoc_child();
    g_signal_status = 0;
    heredoc_child_loop(node, sh, pipe_fd[1], last_exit);
    close(pipe_fd[1]);
    cleanup_child_min(sh->ast, sh->tokens, sh->env, sh->line);
    _exit(0);
}

int heredoc_child_loop(t_node *node, t_shell *sh, int wfd, int last_exit)
{
    char *line;
    char *out;

    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, node->redirect_file) == 0)
        {
            free(line);
            break;
        }
        out = line;
        if (node->heredoc_expand)
        {
            out = expand_env_variables(line, sh->env, last_exit);
            free(line);
        }
        write(wfd, out, ft_strlen(out));
        write(wfd, "\n", 1);
        free(out);
    }
    return (0);
}

void close_if_valid(int *fd)
{
    if (!fd)
        return;
    if (*fd > 2)
        close(*fd);
    *fd = -1;
}
