
#include <stdlib.h>

void	free_split(char **split)
{
	int i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
