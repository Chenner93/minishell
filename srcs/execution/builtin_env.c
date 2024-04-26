/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckenaip <ckenaip@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:16:36 by ckenaip           #+#    #+#             */
/*   Updated: 2024/04/25 14:19:59 by ckenaip          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/exec.h"

/*

    env SANS arguments et SANS options

    a voir ce quon choisi de faire en cas d'arguments present
    si on choisi de considerer comme une erreur
    renvoyer 127 !
    il ne check que et uniquement que son premier parametre, pas les suivant

    ex :
    ckenaip@paul-f4Ar7s1:~/Project_42/Z_Training$ env fqwefqwef fef fefqq f efw qf
    env: ‘fqwefqwef’: No such file or directory
    
    meme si le fichier existe et est bien present
*/