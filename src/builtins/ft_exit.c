/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:21:14 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/04 17:03:39 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_atoi_exit(char *str, int *is_error)
{
	unsigned long long	exit_output;
	int					i;
	int					j;
	int					sign;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	j = i;
	exit_output = 0;
	while ('0' <= str[i] && str[i] <= '9')
		exit_output = exit_output * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i]
		|| ((sign == 1 && exit_output > LONG_MAX)
			|| (sign == -1 && (exit_output > (LONG_MAX - 1)))))
		*is_error = 1;
	return ((int)((exit_output * sign) % 256));
}

void	ft_exit(t_data *data, char **args)
{
	int	exit_output;
	int	is_error;

	exit_output = 0;
	is_error = 0;
	if (count_arg(args) == 2)
	{
		exit_output = ft_atoi_exit(args[1], &is_error);
		if (is_error == 1)
		{
			write(2, "exit: ", 6);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			free_data(data, 2);
		}
	}
	else if (count_arg(args) > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		*(data->exit_code) = 1;
		return ;
	}
	if (count_arg(args) == 1)
		free_data(data, *(data->exit_code));
	free_data(data, exit_output);
}
