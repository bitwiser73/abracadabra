#include <cstdint>
#include <iostream>

#include <windows.h>

// - Older driver version uses '\\.\AppleKeyboard'
// - '0x00000001' would disable Fn lock

int main()
{
	struct MESSAGE {
		uint32_t code;
	} message = { 0 };

	auto hAppleKeyboard = CreateFileA("\\\\.\\AppleKeyMagic2Keyboard", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hAppleKeyboard == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Failed to open device [" << GetLastError() << "]" << std::endl;
		return -1;
	}

	DWORD count;
	BOOL ret = DeviceIoControl(
		hAppleKeyboard,
		0x0B403201C,
		static_cast<void*>(&message),
		sizeof(message),
		NULL,
		0,
		&count,
		NULL);
	if (!ret)
	{
		std::cerr << "Failed to I/O on device [" << GetLastError() << "]" << std::endl;
		return -2;
	}

	return 0;
}
