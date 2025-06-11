/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftpritf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:48:16 by fbui-min          #+#    #+#             */
/*   Updated: 2025/04/08 17:53:51 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>
# include <stddef.h>

bool	ft_put_char(char c, size_t *count);
bool	ft_put_udec(unsigned int n, size_t *count);
bool	ft_put_str(char *str, size_t *count);
bool	ft_put_dec(int n, size_t *count);
bool	ft_put_hex(unsigned int nbr, size_t *count, char cap);
bool	ft_put_ptr(void *address, size_t *count, bool is_first_call);

bool	check(va_list params, char c, size_t *count);
int		ft_printf(const char *format, ...);

#endif