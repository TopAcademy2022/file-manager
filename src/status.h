#pragma once


#include <iostream>
#include <fstream>
#include <boost/date_time.hpp>

/// <summary>
/// Статус
/// </summary>
namespace status
{
	/// <summary>
	/// Код статуса
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

/// <summary>
/// Класс Статус
/// </summary>
class Status
{
private:
	/// <summary>
	/// Код статуса
	/// </summary>
	status::StatusCode _statusCode;
public:
	/// <summary>
	/// Конструктор по умолчанию (делегирование)
	/// </summary>
	Status() : Status(status::StatusCode::Status_AllGood){}

	/// <summary>
	/// Конструктор с параметром
	/// </summary>
	/// <param name="statusCode">Код статуса</param>
	Status(status::StatusCode statusCode);

	/// <summary>
	/// Получить код статуса
	/// </summary>
	/// <returns>Код статуса</returns>
	status::StatusCode GetStatusCode();

	/// <summary>
	/// Установить код статуса
	/// </summary>
	/// <param name="newStatusCode">Новый код статуса</param>
	void SetStatusCode(status::StatusCode newStatusCode);

	/// <summary>
	/// Получить наличие ошибки
	/// </summary>
	/// <returns>Наличие ошибки</returns>
	bool GetPresentError();

	/// <summary>
	/// Вывести сообщение в консоль
	/// </summary>
	/// <param name="addedMessage">Добавляемый текст</param>
	void PrintMessage(std::string addedMessage = "");

	/// <summary>
	/// Создать отчёт
	/// </summary>
	/// <param name="logText">Текст отчёта</param>
	void CreateLogFile(std::string logText);
};

