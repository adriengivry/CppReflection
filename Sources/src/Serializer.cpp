/**
* Project Reflection
* @author Adrien Givry
* @version 1.0
*/

#include <string>

#include "Serializer.h"

std::string Reflection::Serializer::Indent(uint32_t p_indent)
{
	std::string result;

	for (uint32_t i = 0; i < p_indent; ++i)
		result += "\t";

	return result;
}

std::string Reflection::Serializer::Serialize(const std::string& p_name, Reflectable& p_toSerialize, uint32_t p_indent)
{
	std::string result;

	result += Indent(p_indent) + "<field>\n";
	result += Indent(p_indent + 1) + "<name>" + p_name + "</name>\n";
	result += Indent(p_indent + 1) + "<type>" + p_toSerialize.GetType().name() + "</type>\n";

	result += Indent(p_indent + 1) + "<fields>\n";

	for (auto field : p_toSerialize.GetMembers())
		result += Serialize(p_toSerialize, *field, p_indent + 2);

	result += Indent(p_indent + 1) + "</fields>\n";
	result += Indent(p_indent) + "</field>\n";

	return result;
}

std::string Reflection::Serializer::Serialize(Reflectable& p_toSerialize, const TypeDescriptor& p_member, uint32_t p_indent)
{
	std::string result;

	std::byte* dataPointer = reinterpret_cast<std::byte*>(&p_toSerialize) + p_member.offset;

	if (p_member.IsReflectable())
	{
		result += Serialize(p_member.name, *reinterpret_cast<Reflectable*>(dataPointer), p_indent);
	}
	else
	{
		if (p_member.type == typeid(int))
			result += Serialize(p_member.name, *reinterpret_cast<int*>(dataPointer), p_indent);

		if (p_member.type == typeid(float))
			result += Serialize(p_member.name, *reinterpret_cast<float*>(dataPointer), p_indent);

		if (p_member.type == typeid(bool))
			result += Serialize(p_member.name, *reinterpret_cast<bool*>(dataPointer), p_indent);

		if (p_member.type == typeid(char))
			result += Serialize(p_member.name, *reinterpret_cast<char*>(dataPointer), p_indent);

		if (p_member.type == typeid(std::string))
			result += Serialize(p_member.name, *reinterpret_cast<std::string*>(dataPointer), p_indent);
	}

	return result;
}

std::string Reflection::Serializer::Serialize(const std::string & p_name, int p_toSerialize, uint32_t p_indent)
{
	std::string result;

	result += Indent(p_indent) + "<field>\n";
	result += Indent(p_indent) + "\t<name>" + p_name + "</name>\n";
	result += Indent(p_indent) + "\t<type>int</type>\n";
	result += Indent(p_indent) + "\t<value>" + std::to_string(p_toSerialize) + "</value>\n";
	result += Indent(p_indent) + "</field>\n";

	return result;
}

std::string Reflection::Serializer::Serialize(const std::string & p_name, float p_toSerialize, uint32_t p_indent)
{
	std::string result;

	result += Indent(p_indent) + "<field>\n";
	result += Indent(p_indent) + "\t<name>" + p_name + "</name>\n";
	result += Indent(p_indent) + "\t<type>float</type>\n";
	result += Indent(p_indent) + "\t<value>" + std::to_string(p_toSerialize) + "</value>\n";
	result += Indent(p_indent) + "</field>\n";

	return result;
}

std::string Reflection::Serializer::Serialize(const std::string & p_name, bool p_toSerialize, uint32_t p_indent)
{
	std::string result;

	result += Indent(p_indent) + "<field>\n";
	result += Indent(p_indent) + "\t<name>" + p_name + "</name>\n";
	result += Indent(p_indent) + "\t<type>bool</type>\n";
	result += Indent(p_indent) + "\t<value>" + std::to_string(p_toSerialize) + "</value>\n";
	result += Indent(p_indent) + "</field>\n";

	return result;
}

std::string Reflection::Serializer::Serialize(const std::string & p_name, std::string p_toSerialize, uint32_t p_indent)
{
	std::string result;

	result += Indent(p_indent) + "<field>\n";
	result += Indent(p_indent) + "\t<name>" + p_name + "</name>\n";
	result += Indent(p_indent) + "\t<type>string</type>\n";
	result += Indent(p_indent) + "\t<value>" + p_toSerialize + "</value>\n";
	result += Indent(p_indent) + "</field>\n";

	return result;
}
