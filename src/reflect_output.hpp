/*
* Copyright (C) 2016 Vladimir Antonyan <antonyan_v@outlook.com>
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*/

#ifndef REFLECT_OUTPUT_HPP
#define REFLECT_OUTPUT_HPP

#include "debug.hpp"
#include "reflect_class.hpp"

#include <llvm/Support/raw_ostream.h>

#include <string>

namespace reflector {

// @class reflect_output
class reflect_output
{
public:
	explicit reflect_output(llvm::raw_fd_ostream& o)
		: m_out(o)
	{
	}

	void dump(const reflected_class::reflected_collection& reflected)
	{
		dump_comments();
		dump_include_guards_begin();
		dump_includes();
		dump_reflect_manager(reflected);
		dump_forward_delcaration(reflected);
		dump_reflect_class(reflected);
		dump_include_guards_end();
	}
private:
	void dump_comments()
	{
		m_out << "/*\n";
		m_out << " ********************************************************\n";
		m_out << " * This code is licensed see LICENSE.txt for details.\n *\n";
		m_out << " * This file was generated by 'greflect' tool.\n";
		m_out << " * Send comments to antonyan_v@outlook.com.\n";
		m_out << " ********************************************************\n";
		m_out << "*/\n\n";
	}

	void dump_include_guards_begin()
	{
		m_out << "#ifndef REFLECT_HPP\n";
		m_out << "#define REFLECT_HPP\n\n";
	}

	void dump_include_guards_end()
	{
		m_out << "#endif // REFLECT_HPP\n";
	}

	void dump_includes()
	{
		m_out << "#include <exception>\n";
		m_out << "#include <map>\n";
		m_out << "#include <set>\n";
		m_out << "#include <string>\n";
		m_out << "#include <typeinfo>\n";
		m_out << "\n";
	}

	void dump_reflect_class_as_template()
	{
		m_out << "// @class reflect\n";
		m_out << "template <typename T>\n";
		m_out << "class reflect\n{\nprivate:\n";
		m_out << "\treflect();\n\n";
		m_out << "\t~reflect();\n\n";
		m_out << "\treflect(const reflect&);\n\n";
		m_out << "\treflect& operator =(const reflect&);\n\n\n";
		m_out << "}; // template class reflect \n\n";
	}

	void dump_forward_delcaration(const reflected_class::reflected_collection& reflected)
	{
		m_out << "// forward declatation\n";
		for (auto i : reflected) {
			m_out << "class " << i->get_name() << ";\n";
		}
		m_out << "\n";
	}

	void dump_reflect_class(const reflected_class::reflected_collection& reflected)
	{
		dump_reflect_class_as_template();
		for (auto i : reflected) {
			i->dump(m_out);
		}
	}

	void dump_reflect_manager(const reflected_class::reflected_collection& reflected)
	{
		m_out << "// @class reflect_manager\nclass reflect_manager\n{\n";
		m_out << "public:\n\ttemplate <typename T>\n";
		m_out << "\tstatic bool is_reflected(const T& o)\n\t{\n";
		m_out << "\t\tstatic std::set<std::string> reflected_classes;\n";
		m_out << "\t\t// @note: The additional names for support VC++\n";
		m_out << "\t\tif (reflected_classes.empty()) {\n";
		for (auto i : reflected) {
			std::string name = i->get_name();
			m_out << "\t\t\treflected_classes.insert(\"" << std::to_string(name.size()) + name << "\");\n";
			//@note: The additional names for support VC++
			m_out << "\t\t\treflected_classes.insert(\"class " << name << "\");\n";
		}
		m_out << "\t\t}\n\t\treturn reflected_classes.find(typeid(o).name()) != reflected_classes.end();\n\t}\n\n";
		m_out << "}; // class reflect_manager\n\n";
	}

private:
	llvm::raw_fd_ostream& m_out;
}; // class reflect_output

} // namespace reflector

#endif //REFLECT_OUTPUT_HPP