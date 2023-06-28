#include "libft.h"

int    ft_strlen_dtab(char **tab)
{
    int    i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}