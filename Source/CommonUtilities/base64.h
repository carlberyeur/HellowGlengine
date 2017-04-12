#pragma once

namespace CU
{
	std::string base64_decode(std::string const& encoded_string);
	std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);

	unsigned short HostToNetwork(unsigned short aUInt);
	unsigned int HostToNetwork(unsigned int aUInt);

	unsigned short NetworkToHost(unsigned short aUInt);
	unsigned int NetworkToHost(unsigned int aUInt);
}
