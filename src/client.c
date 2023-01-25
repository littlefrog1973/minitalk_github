/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:55:52 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/25 13:42:03 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	respond_to_sig1(pid_t signum)
{
	if (signum == SIGUSR1)
		ft_printf("Server-> Got it");
}

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
	char	*dummy;
	int		i;

	dummy = NULL;
	pid_str = ft_itoa((int) client_pid);
	if (!pid_str)
	{
		ft_printf("Error\n: Out of memory\n");
		exit(1);
	}
	if (ft_strlen(pid_str) == PID_DIGIT - 2)
		dummy = ft_strjoin("00", pid_str);
	else if (ft_strlen(pid_str) == PID_DIGIT - 1)
		dummy = ft_strjoin("0", pid_str);
	else if (ft_strlen(pid_str) == PID_DIGIT)
		dummy = ft_strjoin("", pid_str);
	if (!dummy)
	{
		free(pid_str);
		ft_printf("Error\n: Out of memory\n");
		exit(1);
	}
	free(pid_str);
	pid_str = dummy;
	i = 0;
	while (i < PID_DIGIT)
	{
		send_to_server(server_pid, pid_str[i]);
		i++;
	}
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
	ft_printf("Client PID = %d\n", getpid());
	if (!pid_no)
	{
		ft_printf("Wrong PID\n");
		return (1);
	}
	if (str_to_bit(pid_no, argv[2]))
		ft_printf("Invalid message\n");
	while (1)
	{
		signal(SIGUSR1, respond_to_sig1);
		pause();
	}
	return (0);
}
