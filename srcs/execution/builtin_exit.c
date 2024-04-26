/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:01:31 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/25 14:21:53 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"

/*
    exit prend un parametre int ou rien
    exit a 0 si aucun parametre sinon exist a modulo 256 pour les +
    exit a 256 - (le modulo 256 du parametre), ex: -1 exit a 255 pour les -

    point d'accroche sur l'exit de bash dans bash
    il recupere la valeur de lexit de son child. est ce possible de le faire aussi ?

    attention, il print "exit\n"
*/