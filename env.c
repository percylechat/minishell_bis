#include "minishell.h"

char *ft_get_name(char *str)
{
    int i;
    int boolean;
    char *copy;

    i = 0;
    boolean = 0;
	// printf("get_name: %s", str);
    copy = ft_strdup(str);
    while (copy[i] && boolean == 0)
    {
        if (copy[i] == '=')
        {
            copy[i] = '\0';
            boolean = 1;
        }
        i++;
    }
    while (copy[i])
    {
        copy[i] = '\0';
        i++;
    }
    return (copy);
}

void	ft_lstdelone(t_list *lst)
{
	if (lst)
	{
		lst->name = "";
		lst->value = "";
	}
}


t_list	*ft_lstnew(char *name, void *value)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list*))))
		return (NULL);
	new->name = ft_strdup(name);
    new->value = value;
	new->next = NULL;
    new->prec = NULL;
	return (new);
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last;

	if (!new)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		new->next = NULL;
	}
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->next = NULL;
	}
}

t_list ft_record(void *lst, void *str)
{
    ((t_list *)lst)->name = ft_get_name(str);
    ((t_list *)lst)->value = ft_strchr(str, '=') + 1;
}

void	ft_lstiter(t_list *lst, t_list (*f)(void *, void *), char *str)
{
    int i = 0;
	if (!lst || !f)
		return ;
	f(lst, str);
	lst = lst->next;
}

t_list *set_env(char **env, char **tab, t_list *var_env)
{
    int i;
	int j;
	int k;
    t_list *lst;
    t_list *first;
	t_list *new;

	j = 0;
	while (tab[j])
	{
		j++;
	}
	i = j - 1;
	k = 0;
	// while (env[k])
	// 	k++;
	// k--;
	var_env = ft_lstnew(ft_get_name(env[k]), ft_strdup(ft_strchr(env[k], '=') + 1));
	first = &var_env;
	k++;
	while (env[k])
	{
		new = ft_lstnew(ft_get_name(env[k]), ft_strdup(ft_strchr(env[k], '=') + 1));
		ft_lstadd_back(&var_env, new);
		ft_lstiter(var_env, &ft_record, env[k]);
			printf("varenv: %s\n", var_env->name);
		k++;
	}
	char *name = ft_get_name(tab[i]);
	printf("name:%s\n", name);
	ft_lstadd_back(&var_env, ft_lstnew(name, ft_strchr(tab[i], '=') + 1));
	ft_lstiter(var_env, &ft_record, tab[i]);
	// var_env = ft_lstnew(name, ft_strchr(tab[i], '=') + 1);
	printf("varenv: %s\n", var_env->name);
	printf("newvarenv: %s\n", first->name);
	// while (i >= 1)
    // {
	// 	ft_lstadd_front(&var_env, ft_lstnew(ft_get_name(tab[i]), ft_strdup(ft_strchr(tab[i], '=') + 1)));
	// 	ft_lstiter(var_env, &ft_record, tab[i]);
	// 	i--;
	// }
	// while (k >= 1)
	// {
	// 	ft_lstadd_front(&var_env, ft_lstnew(ft_get_name(env[k]), ft_strdup(ft_strchr(env[k], '=') + 1)));
	// 	ft_lstiter(var_env, &ft_record, env[k]);
	// 	k--;
	// }
    return (var_env);
}

t_list	*unset(t_list *env, char **tab)
{
	int i;
	int j = 0;
	t_list *buf;
	t_list *el;

	while (tab[j])
		j++;
	i = 1;
	while (env->next)
	{
		while (i < j)
		{
			if (strcmp(tab[i], env->next->name) == 0)
			{
				buf = env->next->next;
				el = env->next;
				free(env->next->name);
				free(env->next->value);
				free(env->next->next);
				free(el);
				if (buf)
					env->next = buf;
			}
			i++;
		}
		env = env->next;
		i = 1;
	}
	return (env);
}

void print_env(char **tab, t_list *env)
{
	char *str = NULL;
	char *str2 = NULL;
	printf("\nenv:name%s\nenv:value%s\n", &env->name, &env->value);
	while (env->next != NULL)
	{
		if (env->name)
    	{
			printf("\nenv:name%s\nenv:value%s\n", &env->name, &env->value);
			str2 = ft_strjoin(&env->name, "=");
			str = ft_strjoin(str2, (char *)&env->value);
		}
		env = env->next;
	}
}