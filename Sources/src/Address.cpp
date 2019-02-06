/**
* Project Reflection
* @author Adrien Givry
* @version 1.0
*/

#include "Address.h"

Reflection::Address::Address(const std::string & p_street, int p_number) :
	m_street(p_street), m_number(p_number)
{
	EXPOSE_METADATA();
	REFLECT(m_street);
	REFLECT(m_number);
}