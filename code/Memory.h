#pragma once
#include "IMemory.h"

/// <summary>
/// Container for the memory that you want to monitor. 
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
class Memory : public IMemory {
public:
	Memory() = delete;
	Memory(const T& ref, const char* description = "", const char* suffix = "");
	std::string What() override;
private:
	std::string m_description;
	const T* m_p_value;
	std::string m_suffix;
};

//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
// Template Implementation
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************

#include <sstream>
/// <summary> 
/// Constructor of Memory. It defines how the memory will be displayed in the terminal.
/// </summary>
template<typename T>
inline Memory<T>::Memory(const T& ref, const char* description, const char* suffix) {
	m_description = description;
	m_p_value = &ref;
	m_suffix = suffix;
}
/// <summary>
/// Formats the string to be displayed in the terminal. 
/// </summary>
template<typename T>
inline std::string Memory<T>::What() {
	std::stringstream ss;
	std::string value;
	// 🤓 ATTENTION.
	// the if statement asks "is this valid C++?".
	// the requires ask "For the current T, would this expression compile?".
	// it turns a compilation error into a condition nicely haha.
	if constexpr (requires { std::to_string(*m_p_value); }) {
		value = std::to_string(*m_p_value);
	}
	// if only wants to garantee the implicit convertion,
	// use std::is_convertible_v<T, std::string>.
	// else just use the requires like the code below.
	else if constexpr (requires { static_cast<std::string>(*m_p_value); }) {
		value = static_cast<std::string>(*m_p_value);
	}
	else {
		value = "Invalid Type, please implement `operator std::string() const;` for this type.";
	}
	ss << m_description << ": " << value << m_suffix << "\n";
	return ss.str();
}
/// <summary>
/// Special template for uint8_t so it display number instead of ASCII character. 
/// </summary>
template<>
inline std::string Memory<uint8_t>::What() {
	std::stringstream ss;
	ss << m_description << ": " << static_cast<unsigned int>(*m_p_value) << m_suffix << "\n";
	return ss.str();
}

