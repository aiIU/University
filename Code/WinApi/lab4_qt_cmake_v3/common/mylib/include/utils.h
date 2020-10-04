#pragma once

namespace utils
{
	string GetLastErrorMessage(string functionName = {});
	string ErrorCodeToString(int code, string functionName = {});
}