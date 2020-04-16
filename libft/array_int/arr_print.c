/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 15:23:23 by Nik               #+#    #+#             */
/*   Updated: 2020/04/16 15:09:33 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array_int.h"

void	arr_print(int *arr)
{
	int i;

	i = 1;
	while (i <= ARR_LEN)
	{
		ft_printf("%d ", arr[i++]);
	}
	ft_printf("\n");
}
