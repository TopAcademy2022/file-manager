#include "far.h"

status::StatusCode Far::SearchFileOrDirectory(std::string objectName, std::string pathToFind)
{
	if (!this->_status->GetPresentError())
	{
		if (pathToFind.empty())
		{
			pathToFind = this->_currentDirectory;
		}

		try
		{
			for (auto const& entry : std::filesystem::directory_iterator{ pathToFind })
			{
				if (entry.path().filename() == objectName)
				{
					this->_status->SetStatusCode(status::StatusCode::Status_DirectoryOrFileWasFound);
					break;
				}
			}

			if (this->_status->GetStatusCode() != status::StatusCode::Status_DirectoryOrFileWasFound)
			{
				this->_status->SetStatusCode(status::StatusCode::Error_FileNotFound);
			}
		}
		catch (std::exception ex)
		{
			this->_status->SetStatusCode(status::StatusCode::Error_DirectoryNotFound);
			this->_status->PrintMessage();

			std::string errorText = "Method: Far::SearchFileOrDirectory(std::string objectName, std::string pathToFind)\n";
			errorText.append("ErrorStatusCode: " + this->_status->GetStatusCode());
			errorText.append("\n");

			this->_status->CreateLogFile(errorText + ex.what() + '\n');
		}
	}

	return this->_status->GetStatusCode();
}

Far::Far(std::string currentDirectory)
{
	this->_status = new Status();
	this->_currentDirectory = currentDirectory;
}

void Far::PrintContentFromDirectory(std::string pathToDirectory)
{
	if (!this->_status->GetPresentError())
	{
		if (pathToDirectory.empty())
		{
			pathToDirectory = this->_currentDirectory;
		}

		try
		{
			for (auto const& entry : std::filesystem::directory_iterator{ pathToDirectory })
			{
				std::cout << entry.path().filename() << '\n';
			}
		}
		catch (std::exception ex)
		{
			this->_status->SetStatusCode(status::StatusCode::Error_DirectoryNotFound);
			this->_status->PrintMessage();

			std::string errorText = "Method: Far::PrintContentFromDirectory(std::string pathToDirectory)\n";
			errorText.append("ErrorStatusCode: " + this->_status->GetStatusCode() + '\n');

			this->_status->CreateLogFile(errorText + ex.what() + "\n");
		}
	}
}

status::StatusCode Far::CreateDirectory(std::string createDirectoryName, std::string pathToDirectory)
{
	if (!this->_status->GetPresentError())
	{
		if (pathToDirectory.empty())
		{
			pathToDirectory = this->_currentDirectory;
		}
		if (pathToDirectory[pathToDirectory.size() - 1] != '/')
		{
			pathToDirectory.push_back('/');
		}

		try
		{
			std::filesystem::create_directory(pathToDirectory + createDirectoryName);

			if (this->SearchFileOrDirectory(createDirectoryName, pathToDirectory))
			{
				this->_status->SetStatusCode(status::StatusCode::Status_DirectoryWasCreated);
			}
			else
			{
				this->_status->SetStatusCode(status::StatusCode::Error_NoAccessRights);
				this->_status->PrintMessage();

				std::string errorText = "Method: Far::CreateDirectory(std::string createDirectoryName, std::string pathToDirectory)\n";
				errorText.append("ErrorStatusCode: " + this->_status->GetStatusCode() + '\n');

				this->_status->CreateLogFile(errorText);
			}
		}
		catch (std::exception ex)
		{
			this->_status->SetStatusCode(status::StatusCode::Error_DirectoryNotFound);
			this->_status->PrintMessage();

			std::string errorText = "Method: Far::CreateDirectory(std::string createDirectoryName, std::string pathToDirectory)\n";
			errorText.append("ErrorStatusCode: " + this->_status->GetStatusCode() + '\n');

			this->_status->CreateLogFile(errorText + ex.what() + "\n");
		}
	}

	return this->_status->GetStatusCode();
}

status::StatusCode Far::CreateFile(std::string fileName, std::string fileType, std::string pathToDirectory)
{
	if (!this->_status->GetPresentError())
	{
		if (pathToDirectory.empty())
		{
			pathToDirectory = this->_currentDirectory;
		}
		if (pathToDirectory[pathToDirectory.size() - 1] != '/')
		{
			pathToDirectory.push_back('/');
		}
		if (fileType[0] != '.')
		{
			fileType = '.' + fileType;
		}
		if (this->SearchFileOrDirectory(fileName + fileType, pathToDirectory) != status::StatusCode::Error_FileNotFound)
		{
			this->_status->SetStatusCode(status::StatusCode::Error_FileWasCreated);
			this->_status->PrintMessage();
			
			std::string errorText = "Method: Far::CreateFile(std::string fileName, std::string fileType, std::string pathToDirectory)\n";
			// TODO: rewrite, its not worked
			errorText.append("ErrorStatusCode: " + this->_status->GetStatusCode() + '\n');
			errorText.append("Файл уже был создан" + '\n');

			this->_status->CreateLogFile(errorText);

			return this->_status->GetStatusCode();
		}

		try
		{
			std::ofstream file = std::ofstream();
			file.open(pathToDirectory + fileName + fileType);
			file.close();

			if (this->SearchFileOrDirectory(fileName + fileType, pathToDirectory))
			{
				this->_status->SetStatusCode(status::StatusCode::Status_FileWasCreated);
				// TODO: Указывать полный путь до директории
				this->_status->PrintMessage("Путь создания: " + pathToDirectory);
			}
			else
			{
				this->_status->SetStatusCode(status::StatusCode::Error_NoAccessRights);
				this->_status->PrintMessage();

				std::string errorText = "Method: Far::CreateFile(std::string fileName, std::string fileType, std::string pathToDirectory)\n";
				errorText.append("ErrorStatusCode: " + this->_status->GetStatusCode() + '\n');

				this->_status->CreateLogFile(errorText);
			}
		}
		catch (std::exception ex)
		{
			this->_status->SetStatusCode(status::StatusCode::Error_DirectoryNotFound);
			this->_status->PrintMessage();

			std::string errorText = "Method: Far::CreateFile(std::string fileName, std::string fileType, std::string pathToDirectory)\n";
			errorText.append("ErrorStatusCode: " + this->_status->GetStatusCode() + '\n');

			this->_status->CreateLogFile(errorText + ex.what() + "\n");
		}
	}

	return this->_status->GetStatusCode();
}


status::StatusCode Far::Delete(std::string path) {
	try {
		if (std::filesystem::exists(path)) {
			if (std::filesystem::is_regular_file(path)) {
				if (std::filesystem::remove(path)) {
					return status::StatusCode::Status_AllGood;
				}
			}
			else if (std::filesystem::is_directory(path)) {
				if (std::filesystem::remove_all(path)) {
					return status::StatusCode::Status_AllGood;
				}
			}
		}
		else {
			return status::StatusCode::Error_PathNotFound;
		}
	}
	catch (const std::exception& e) {
		return status::StatusCode::Error_PathNotFound;
	}
}
