#pragma once
#include <chrono>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>



#include <iostream>
#include<ctime>
#include<cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include <bitset>
#include <array>
#include <future>
#include <assert.h>

#include <filesystem>




template <typename Base, typename Derived>
struct isBaseOf {
	static constexpr bool value = std::is_base_of<Base, Derived>::value;
};

using Uint = unsigned int;


namespace MTB {
// Function to measure the execution time of a static function
template <typename Func, typename...TArgs>
long long measureExecutionTime(Func staticFunction, TArgs&&... mArgs)
{
	auto start = std::chrono::high_resolution_clock::now();

	// Call the provided static function
	staticFunction(mArgs...);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

	return duration.count();
}


	template<typename T>
	static std::vector<char> convertToBinary(T& object) {
		std::vector<char> binary;
		binary.resize(sizeof(object));
		std::memcpy(binary.data(), &object, sizeof(object));
		return binary;
	}
}