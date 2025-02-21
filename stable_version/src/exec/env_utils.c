#include "minishell.h"

int    env_list_size(t_env *env)
{
    int     size;
    t_env   *current;

    size = 0;
    current = env;
    while (current)
    {
        size++;
        current = current->next;
    }
    return (size);
}


char    *create_env_string(char *key, char *value)
{
    char    *tmp;
    char    *result;

    tmp = ft_strjoin(key, "=");
    if (!tmp)
        return (NULL);
    result = ft_strjoin(tmp, value);
    free(tmp);
    return (result);
}

// char    *get_env_value(t_env *env, char *key)
// {
//     t_env   *current;

//     current = env;
//     while (current)
//     {
//         if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
//             return (current->value);
//         current = current->next;
//     }
//     return (NULL);
// }

char    **env_list_to_array(t_env *env)
{
    char    **arr;
    t_env   *current;
    int     size;
    int     i;

    size = env_list_size(env);
    arr = malloc(sizeof(char *) * (size + 1));
    if (!arr)
        return (NULL);
    current = env;
    i = 0;
    while (current)
    {
        arr[i] = create_env_string(current->key, current->value);
        if (!arr[i])
        {
            free_env_array(arr);
            return (NULL);
        }
        current = current->next;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

void    free_env_array(char **env_arr)
{
    int    i;

    if (!env_arr)
        return ;
    i = 0;
    while (env_arr[i])
    {
        free(env_arr[i]);
        i++;
    }
    free(env_arr);
}