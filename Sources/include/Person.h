/**
* Project Reflection
* @author Adrien Givry
* @version 1.0
*/

#pragma once

#include "Address.h"

namespace Reflection
{
	/**
	* Simple test class to demonstrate how reflection can be used
	*/
	class Person : public Reflectable
	{
		ENABLE_REFLECTION();

	public:
		Person(int p_age, std::string p_name, bool p_gender, const std::string& p_street, int p_number);

	private:
		REFLECTABLE(int, m_age);
		REFLECTABLE(bool, m_gender);
		REFLECTABLE(Address, m_address);

	public:
		REFLECTABLE(std::string, name);
	};
}