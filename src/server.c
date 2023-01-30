/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:05:34 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/30 17:12:54 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	bit_to_char(int signum, siginfo_t *info, void *context)
/*Put received bit to 8th pos and RHS one by one to form received unsigned char
Cannot use while loop in this interruptible function, only advance once
per interrupt*/
{
	static unsigned char	bits_count = 0;
	static unsigned char	chr = 0;

	(void) context;
	bits_count++;
	if (bits_count > BYTE)
		bits_count = 1;
	if (signum == SIGUSR2)
		chr |= 0b10000000;
	if (bits_count != BYTE)
		chr >>= 1;
	if (bits_count == 8 && chr)
	{
		write(STDOUT_FILENO, &chr, 1);
		bits_count = 0;
		chr = 0;
	}
	else if (bits_count == 8 && !chr)
	{
		kill(info->si_pid, SIGUSR2);
		return ;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	s_sigaction;

	ft_memset(&s_sigaction, 0, sizeof(s_sigaction));
	pid = getpid();
	ft_putstr_fd("Server PID = ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	s_sigaction.sa_sigaction = bit_to_char;
	s_sigaction.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigaction(SIGUSR1, &s_sigaction, NULL);
	sigaction(SIGUSR2, &s_sigaction, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
