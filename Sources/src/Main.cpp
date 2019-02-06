/**
* Project Reflection
* @author Adrien Givry
* @version 1.0
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "Person.h"
#include "Serializer.h"

/* Iterate over the __global_meta_data__ and print its content */
void Demo_ParseReflectedData()
{
	std::string reflectedData = "Here is the output of the 'Demo_ParseReflectedData' function:\n\n";

	for (const auto&[key, value] : __global_meta_data__)
	{
		reflectedData += "Type:" + key + "\n";

		for (auto member : value.get().members)
		{
			reflectedData += "\t Name:" + member->name;
			reflectedData += "\t Type:" + std::string(member->type.name()) + "\n";
		}

		reflectedData += "\n";
	}

	std::cout << reflectedData << std::endl;
}

/* Serialize a Reflectable and output it to a file */
void Demo_SerializeToXML(Reflection::Reflectable& p_toSerialize)
{
	std::ofstream out("output.xml");
	out << Reflection::Serializer::Serialize("person", p_toSerialize);
	out.close();

	std::cout << "'output.xml' file generated" << std::endl;
}

int main()
{
	Reflection::Person person(34, "John", true, "Street of Nowhere", 1234);

	Demo_ParseReflectedData();
	Demo_SerializeToXML(person);

	std::cin.get();

	return 0;
}