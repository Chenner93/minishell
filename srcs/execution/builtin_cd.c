/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:47:38 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/25 13:50:02 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"

// cd ~ ramene a home, pas besoin de le gerer
// ne fonctionne pas dans une pipe, sinon fonctionne peu importe le dup -> fd
// peut etre tester si ne fonctionne pas a cause du fait quil soit dans un enfant
// et non directement dans le parents

// void	builtin_cd()
// {

// }