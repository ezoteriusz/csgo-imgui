#pragma once
#include <cstdint>
#include <string_view>

namespace hash
{
	// fnv constants
	constexpr std::uint32_t BASE = 0x811C9DC5;
	constexpr std::uint32_t PRIME = 0x1000193;

	// compile-time FNV hash
	consteval std::uint32_t CompileTime(const char* data, const std::uint32_t value = BASE) noexcept
	{
		return (data[0] == '\0') ? value : CompileTime(&data[1], (value ^ std::uint32_t(data[0])) * PRIME);
	}

	// run-time FNV hash
	inline const std::uint32_t RunTime(const std::string_view data) noexcept
	{
		std::uint32_t hashed = BASE;

		// hash characters
		for (const char& character : data)
		{
			hashed ^= character;
			hashed *= PRIME;
		}

		return hashed;
	}
}

namespace fnv_1a {
	template< typename S >
	struct fnv_internal;
	template< typename S >
	struct fnv1a;

	template< >
	struct fnv_internal< uint32_t > {
		constexpr static uint32_t default_offset_basis = 0x811C9DC5;
		constexpr static uint32_t prime = 0x01000193;
	};

	template< >
	struct fnv1a< uint32_t > : public fnv_internal< uint32_t > {
		constexpr static uint32_t hash(char const* string, const uint32_t val = default_offset_basis) {
			return (string[0] == '\0')
				? val
				: hash(&string[1], (val ^ uint32_t(string[0])) * prime);
		}

		constexpr static uint32_t hash(wchar_t const* string, const uint32_t val = default_offset_basis) {
			return (string[0] == L'\0')
				? val
				: hash(&string[1], (val ^ uint32_t(string[0])) * prime);
		}
	};
}

using fnv = fnv_1a::fnv1a< uint32_t >;