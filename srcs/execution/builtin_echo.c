/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:51:21 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/25 13:56:43 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"

/*
    seul option -n pouvant detenir PLEIN de n
    si autre chose qu'un n, alors c'est un argument et non une option

    echo ne prend pas de fd_in, mais accepte les fd_out
    
*/