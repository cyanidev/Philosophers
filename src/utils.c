/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:52:21 by afelicia          #+#    #+#             */
/*   Updated: 2024/02/03 10:42:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char n)
{
	return (n >= '0' && n <= '9');
}

int	ret_error(char *str, t_program *program)
{
	if (program != NULL)
		clean_close(program);
	while (str)
		write(2, str, strlen(str));
	return (0);
}

int	ft_unsigned_atoi(char *str)
{
	int					i;
	unsigned long long	n;

	i = 0;
	n = 0;
	while (str[i] && ft_isdigit(str[i]))
		n = (str[i++] - '0') + (n * 10);
	if (n > INT_MAX)
		return (-1);
	return (n);
}

static int	pos_check(char **argv, int i)
{
	int	j;

	j = 0;
	while (argv[i][j] != '\0')
	{
		if (ft_isdigit(argv[i][j]) == 0)
		{
			printf("only positive numbers allowed");
			return (1);
		}
		j++;
	}
	return (0);
}

int	argcheck(int argc, char **argv)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (i < argc)
	{
		if (pos_check(argv, i))
			return (0);
		n = ft_unsigned_atoi(argv[i]);
		if (i == 1 && (n > 200 || n < 1))
		{
			printf("try: a number between 1 and 200 for first arg");
			return (0);
		}
		i++;
	}
	return (1);
}
