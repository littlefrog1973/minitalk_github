/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:05:34 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/01/25 11:12:03 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	bit_to_char(int signum)
{
	static int				bits_count;
	static unsigned char	chr;
//	static char				pid_str[5];
//	static int				pid_digit_count;
	static int				write_pid;

	bits_count++;
	if (signum == SIGUSR1 && bits_count != 8)
		chr >>= 1;
	if (signum == SIGUSR2)
	{
		chr |= 128;
		if (bits_count != 8)
			chr >>= 1;
	}
/*	if (bits_count == 8 && pid_digit_count <= PID_DIGIT)
	{
		pid_str[pid_digit_count] = chr;
		if (pid_digit_count == 5)
		{
			write(1, &pid_str, 5);
			write(1, "\n", 1);
			write_pid = 1;
		}
		pid_digit_count++;
		bits_count = 0;
		chr = 0;
	}
*/
	write_pid = 1;
	if (bits_count == 8 && write_pid)
	{
		write(1, &chr, 1);
		bits_count = 0;
		chr = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID = %d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, bit_to_char);
		signal(SIGUSR2, bit_to_char);
		pause();
	}
	return (0);
}
