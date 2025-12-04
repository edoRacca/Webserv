/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GABIBBO <GABIBBO@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:52:09 by GABIBBO          #+#    #+#             */
/*   Updated: 2025/12/04 13:52:10 by GABIBBO        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ether.hpp"

bool	requestParsing(std::string input)
{
	std::string	method;
	int			i;

	method = input.substr(0, input.find(' '), 0)
}