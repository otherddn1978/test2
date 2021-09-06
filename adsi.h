#ifndef __ADSI_H_7CDDCD12_BF15_4742_A2ED_E93FF074EC29
#define __ADSI_H_7CDDCD12_BF15_4742_A2ED_E93FF074EC29

/*******************************************************************************
Файл:      adsi.h
Автор:     Кашавцев Ю.А.
Описание:  Обертки для работы с ADSI
*******************************************************************************/

#include <windows.h>
#include <atlbase.h>
#include <activeds.h>

#include <string>
#include <vector>

#include "win32c.h"

class TADSIError : public std::exception
{
public:
	TADSIError(const std::string &msg, DWORD err = 0) throw();
	virtual const char *what() const throw();
	DWORD GetError() const { return error; }
protected:
	DWORD		error;
	std::string	message;
};

class TADSI
{
public:
	TADSI():rootDSE(NULL), schemaNC(NULL), confNC(NULL), defNC(NULL), confNCDel(NULL), defNCDel(NULL), domainDnsNC(NULL), forestDnsNC(NULL){};
	~TADSI();

	// Получение строкового описания класса объекта Active Directory по GUID
	std::string GetClassNameByGUID(const std::string &id);
	// Получение строкового описания объекта Active Directory по GUID
	std::string GetObjectNameByGUID(const std::string &id, const std::string &namingContext = "defaultNamingContext");
	// Получение строкового описания удаленного(захороненного) объекта Active Directory по GUID
	std::string GetDeletedObjectNameByGUID(const std::string &id, const std::string &namingContext = "defaultNamingContext");

	// Соединение с LDAP сервером (инициализация объекта RootDSE)
	HRESULT ConnectLDAPServer();

protected:
	IADs				*rootDSE;	// Корневой объект службы каталогов
	IDirectorySearch	*schemaNC;	// Интерфейс поиска по контексту имен схемы AD

	// Инициализация контекста поиска AD
	void NCInit(const std::wstring &namingContext, IDirectorySearch **NC);
	// Инициализация контекста поиска захороненных объектов в AD
	void NCInitDel(const std::wstring &namingContext, IDirectorySearch **NC);
private:
	IDirectorySearch	*confNC;	// Интерфейс поиска по контексту конфигурации AD
	IDirectorySearch	*defNC;		// Интерфейс поиска по контексту по умолчанию
	IDirectorySearch	*confNCDel;	// Интерфейс поиска по контексту удаленной конфигурации AD
	IDirectorySearch	*defNCDel;	// Интерфейс поиска по контексту удаленных объектов AD
	IDirectorySearch	*domainDnsNC;	// Интерфейсы поиска по контекстам DNS
	IDirectorySearch	*forestDnsNC;

	// Установка настроек поиска для существующих объектов
	void SetSearchSettings(IDirectorySearch *NC);
	// Установка настроек поиска для захороненных объектов
	void SetSearchSettingsDel(IDirectorySearch *NC);
	// Получение результата поиска
	std::vector<std::string> GetSearchResult(IDirectorySearch *NC, ADS_SEARCH_HANDLE hSearch, LPWSTR attr[], DWORD numberAttributes);
};

// Преобразование отображаемой строки GUID вида {19195A5B-6DA0-11D0-AFD3-00C04FD930C9}
// к Octet-строке вида \\5B\\5A\\19\\19\\A0\\6D\\D0\\11\\AF\\D3\\00\\C0\\4F\\D9\\30\\C9
std::wstring GUIDStrToOctetString(const std::wstring &strGUID);

#endif // #ifndef __ADSI_H_7CDDCD12_BF15_4742_A2ED_E93FF074EC29