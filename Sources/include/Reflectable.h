/**
* Project Reflection
* @author Adrien Givry
* @version 1.0
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <list>

/**
* Alow the Reflectable to access metadata from the dervied class
*/
#define EXPOSE_METADATA()\
this->__meta_data__ = &__meta_data_internal__;\
__meta_data_internal__.typeWrapper = std::make_unique<Reflection::TypeInfoWrapper>(typeid(*this));\
__global_meta_data__.insert({__meta_data_internal__.typeWrapper->type.name(), std::ref(__meta_data_internal__)})


/**
* Store the variable metadata to the __meta_data_internal__ (Accessible via Reflectable __meta_data__)
*/
#define REFLECT(varName)\
if (!std::remove_reference<decltype(*this)>::type::__##varName##__.IsInit())\
{\
std::remove_reference<decltype(*this)>::type::__##varName##__.Init(#varName, offsetof(std::remove_reference<decltype(*this)>::type, varName), std::is_base_of<Reflectable, decltype(std::remove_reference<decltype(*this)>::type::varName)>::value);\
std::remove_reference<decltype(*this)>::type::__meta_data_internal__.members.push_back(&std::remove_reference<decltype(*this)>::type::__##varName##__);\
}

/**
* Enable the reflection for this class (You can't make a member reflectable before calling this macro
*/
#define ENABLE_REFLECTION() inline static Reflection::MetaData __meta_data_internal__

/**
* Make a member reflectable
*/
#define REFLECTABLE(type, name)\
type name;\
inline static Reflection::TypeDescriptor __##name##__ { typeid(type) };\

namespace Reflection
{
	/**
	* Describes a member variable
	*/
	struct TypeDescriptor
	{
		std::string name = "*";
		size_t offset;
		const std::type_info& type;
		bool reflectable;

		TypeDescriptor(const std::type_info& p_type) : type(p_type) {}
		bool IsInit() const { return name != "*"; }
		bool IsReflectable() const { return reflectable; }
		void Init(const std::string& p_name, size_t p_offset, bool p_reflectable) { name = p_name; offset = p_offset; reflectable = p_reflectable; }
	};

	/**
	* Wraps a type_info
	*/
	struct TypeInfoWrapper
	{
		TypeInfoWrapper(const std::type_info& p_type) : type(p_type) {}

		const std::type_info& type;
	};

	/**
	* Class/Sturct meta data (Contains a vector of TypeDescriptors and a TypeInfoWrapper that gives
	* informations about the Class/Struct
	*/
	struct MetaData
	{
		std::unique_ptr<TypeInfoWrapper> typeWrapper;
		std::vector<TypeDescriptor*> members;

		~MetaData() { typeWrapper.release(); }
	};

	/**
	* Make any class inherits from this one to make the reflection possible and
	* to access __meta_data__ from an reflected instance
	*/
	class Reflectable
	{
	public:
		std::vector<TypeDescriptor*>& GetMembers() { return __meta_data__->members; }
		const std::type_info& GetType() { return __meta_data__->typeWrapper->type; }

	protected:
		MetaData* __meta_data__;
	};
}

/**
* A simple unordered_map of every Class/Struct meta data.
* It can be used like a dictionnary to find information about
* a given Class/Struct
*/
extern std::unordered_map<std::string, std::reference_wrapper<Reflection::MetaData>> __global_meta_data__;