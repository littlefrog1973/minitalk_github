/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:55:52 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/24 16:45:09 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_to_server(pid_t pid, unsigned char chr)
{
	int	i;

	i = 0;
	while (i < BYTE)
	{
		if (chr & 1)
		{
			kill(pid, SIGUSR2);
			usleep(30);
		}
		else
		{
			kill(pid, SIGUSR1);
			usleep(30);
		}
		chr >>= 1;
		i++;
	}
}
static void	send_pid_to_server(pid_t server_pid, pid_t client_pid)
{
	char	*pid_str;
	int		i;

	pid_str = ft_itoa((int) client_pid);
	if (!pid_str)
	{
		ft_printf("Error\n: Out of memory");
		exit (1);
	}
	pid_str[ft_strlen(pid_str)] = '#';
	i = 0;
	while (pid_str[i] != '#')
	{
		send_to_server(server_pid, pid_str[i]);
		i++;
	}
	send_to_server(server_pid, pid_str[i]);
	free(pid_str);
}

static int	str_to_bit(pid_t pid, char *str)
{
	unsigned char	chr;

	if (!str)
		return (1);
	send_pid_to_server(pid, getpid());
	while (*str)
	{
		chr = *str;
		send_to_server(pid, chr);
		str++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pid_t	pid_no;

	if (argc != 3)
	{
		ft_printf("Error\n: Fewer or Larger parameters");
		return (1);
	}
	pid_no = ft_atoi(argv[1]);
	if (!pid_no)
	{
		ft_printf("Wrong PID\n");
		return (1);
	}
	if (str_to_bit(pid_no, argv[2]))
		ft_printf("Invalid message\n");
	return (0);
}
