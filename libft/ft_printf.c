/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:27:46 by ikaismou          #+#    #+#             */
/*   Updated: 2022/12/24 14:17:55 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *str, int *len)
{
	int	i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		ft_putchar(str[i], len);
		i++;
	}
}

void	format(va_list args, const char c, int *len)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), len);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), len);
	else if (c == 'i' || c == 'd')
		ft_putnbr(va_arg(args, int), len);
	else if (c == 'u')
		ft_putnbr_base(va_arg(args, unsigned int), 10,
			"0123456789", len);
	else if (c == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), 16,
			"0123456789abcdef", len);
	else if (c == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), 16,
			"0123456789ABCDEF", len);
	else if (c == 'p')
	{
		ft_putstr("0x", len);
		ft_putnbr_base(va_arg(args, long long unsigned int), 16,
			"0123456789abcdef", len);
	}
	else if (c == '%')
		ft_putchar('%', len);
}

void	ft_putchar(char c, int *len)
{
	if (*len == -1)
		return ;
	if (write (1, &c, 1) != -1)
		*len += 1;
	else
		*len = -1;
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i] && len != -1)
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				break ;
			format(args, str[i + 1], &len);
			i++;
		}
		else
			ft_putchar(str[i], &len);
		i++;
	}
	va_end(args);
	return (len);
}
