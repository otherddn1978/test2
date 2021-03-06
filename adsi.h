#define __ADSI_H_7CDDCD12_BF15_4742_A2ED_E93FF074EC29

/*******************************************************************************
????:      adsi.h
?????:     ???????? ?.?.
????????:  ??????? ??? ?????? ? ADSI
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

	// ????????? ?????????? ???????? ?????? ??????? Active Directory ?? GUID
	std::string GetClassNameByGUID(const std::string &id);
	// ????????? ?????????? ???????? ??????? Active Directory ?? GUID
	std::string GetObjectNameByGUID(const std::string &id, const std::string &namingContext = "defaultNamingContext");
	// ????????? ?????????? ???????? ??????????(?????????????) ??????? Active Directory ?? GUID
	std::string GetDeletedObjectNameByGUID(const std::string &id, const std::string &namingContext = "defaultNamingContext");

	// ?????????? ? LDAP ???????? (????????????? ??????? RootDSE)
	HRESULT ConnectLDAPServer();

protected:
	IADs				*rootDSE;	// ???????? ?????? ?????? ?????????
	IDirectorySearch	*schemaNC;	// ????????? ?????? ?? ????????? ???? ????? AD

	// ????????????? ????????? ?????? AD
	void NCInit(const std::wstring &namingContext, IDirectorySearch **NC);
	// ????????????? ????????? ?????? ???????????? ???????? ? AD
	void NCInitDel(const std::wstring &namingContext, IDirectorySearch **NC);
private:
	IDirectorySearch	*confNC;	// ????????? ?????? ?? ????????? ???????????? AD
	IDirectorySearch	*defNC;		// ????????? ?????? ?? ????????? ?? ?????????
	IDirectorySearch	*confNCDel;	// ????????? ?????? ?? ????????? ????????? ???????????? AD
	IDirectorySearch	*defNCDel;	// ????????? ?????? ?? ????????? ????????? ???????? AD
	IDirectorySearch	*domainDnsNC;	// ?????????? ?????? ?? ?????????? DNS
	IDirectorySearch	*forestDnsNC;

	// ????????? ???????? ?????? ??? ???????????? ????????
	void SetSearchSettings(IDirectorySearch *NC);
	// ????????? ???????? ?????? ??? ???????????? ????????
	void SetSearchSettingsDel(IDirectorySearch *NC);
	// ????????? ?????????? ??????
	std::vector<std::string> GetSearchResult(IDirectorySearch *NC, ADS_SEARCH_HANDLE hSearch, LPWSTR attr[], DWORD numberAttributes);
};

// ?????????????? ???????????? ?????? GUID ???? {19195A5B-6DA0-11D0-AFD3-00C04FD930C9}
// ? Octet-?????? ???? \\5B\\5A\\19\\19\\A0\\6D\\D0\\11\\AF\\D3\\00\\C0\\4F\\D9\\30\\C9
std::wstring GUIDStrToOctetString(const std::wstring &strGUID);

#endif // #ifndef __ADSI_H_7CDDCD12_BF15_4742_A2ED_E93FF074EC29