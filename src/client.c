/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:55:52 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/30 17:11:23 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_argv[2];

static void	send_to_server(pid_t pid, unsigned char chr)
/* Send bit by bit of chr per call, by masking with bit_mask
to avoid while loop. */
{
	static int				i = -1;
	static unsigned char	bit_mask[] = {1, 2, 4, 8, 16, 32, 64, 128};

	i++;
	if (i == BYTE)
		i = 0;
	if (chr & bit_mask[i])
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
}

static void	str_to_bin(void)
/* Chop str to byte and ask send_to_server to send that byte,
bit by bit to client */
{
	static int		bit_count;
	static int		char_count = -1;
	static int		str_num = 0;
	static int		serv_pid = 0;

	bit_count++;
	if (!str_num)
		str_num = (int) ft_strlen(g_argv[1]);
	if (!serv_pid)
		serv_pid = ft_atoi(g_argv[0]);
	if (char_count == -1)
		char_count++;
	if (((bit_count % 8) == 1) && (bit_count > 1))
		char_count++;
	if (char_count > str_num)
		exit (0);
	send_to_server(serv_pid, (unsigned char) g_argv[1][char_count]);
	usleep(5);
}

static void	action(pid_t signum)
{
	if (signum == SIGUSR1)
		str_to_bin();
	else
	{
		ft_printf("Server received all messages.\n");
		exit (0);
	}
}

int	main(int argc, char *argv[])
{
	ft_putstr_fd("Client PID = ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr_fd("Error\n: Fewer or Too Many parameters\n", STDOUT_FILENO);
		return (1);
	}
	g_argv[0] = argv[1];
	g_argv[1] = argv[2];
	str_to_bin();
	while (1)
	{
		pause();
	}
	return (0);
}
