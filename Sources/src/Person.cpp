/**
* Project Reflection
* @author Adrien Givry
* @version 1.0
*/

#include "Person.h"

#include <iostream>

Reflection::Person::Person(int p_age, std::string p_name, bool p_gender, const std::string& p_street, int p_number) :
	m_age(p_age),
	m_gender(p_gender),
	m_address(p_street, p_number),
	name(p_name)
{
	EXPOSE_METADATA();
	REFLECT(m_age);
	REFLECT(m_gender);
	REFLECT(m_address);
	REFLECT(name);
}