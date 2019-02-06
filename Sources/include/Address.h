/**
* Project Reflection
* @author Adrien Givry
* @version 1.0
*/

#pragma once

#include <string>

#include "Reflectable.h"

namespace Reflection
{
	/**
	* Simple test struct to demonstrate how reflection can be used
	* @note An instance of this class is stored in the "Person" class for serialization demo
	*/
	struct Address : Reflectable
	{
		ENABLE_REFLECTION();

	public:
		Address(const std::string& p_location, int p_number);

	private:
		REFLECTABLE(std::string, m_street);
		REFLECTABLE(int, m_number);
	};
}