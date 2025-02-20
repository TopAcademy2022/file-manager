#pragma once

namespace status
{
	/// <summary>
	/// ��� �������
	/// </summary>
	enum StatusCode
	{
		Status_AllGood = 0,
		Error_DirectoryNotFound = 1,
		Error_FileNotFound = 2,
		Status_DirectoryOrFileWasFound = 3,
		Status_DirectoryWasCreated = 4,
		Status_FileWasCreated = 5,
		Error_FileWasCreated = 6,
		Error_NoAccessRights = 7
	};
}