#include "../../include/builtins.h"

void    builtin_cd(char **args)
{
    char    cwd[1024];
    char    *path;

    if (args[1] && ft_strcmp(args[1], "-") == 0)
    {
        path = getenv("OLDPWD");
        if (!path)
        {
            ft_putendl_fd("cd: OLDPWD not set", 2);
            return ;
        }
        printf("%s\n", path);
    }
    else
        path = args[1] ? args[1] : getenv("HOME");

    if (!path)
    {
        ft_putendl_fd("cd: HOME not set", 2);
        return ;
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("cd: getcwd");
        return ;
    }
    if (chdir(path) != 0)
    {
        perror("cd");
        return ;
    }
}
