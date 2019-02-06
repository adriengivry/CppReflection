/**
* Project Reflection
* @author Adrien Givry
* @version 1.0
*/

#pragma once

#include "Reflectable.h"

namespace Reflection
{
	/**
	* A simple class that transform a Reflectable object to an XML string
	*/
	class Serializer
	{
	public:
		static std::string Indent(uint32_t p_indent);

		static std::string Serialize(const std::string& p_name, Reflectable& p_toSerialize, uint32_t p_indent = 0);
		static std::string Serialize(Reflectable& p_toSerialize, const TypeDescriptor& p_member, uint32_t p_indent = 0);
		static std::string Serialize(const std::string& p_name, int p_toSerialize, uint32_t p_indent = 0);
		static std::string Serialize(const std::string& p_name, float p_toSerialize, uint32_t p_indent = 0);
		static std::string Serialize(const std::string& p_name, bool p_toSerialize, uint32_t p_indent = 0);
		static std::string Serialize(const std::string& p_name, std::string p_toSerialize, uint32_t p_indent = 0);
	};
}