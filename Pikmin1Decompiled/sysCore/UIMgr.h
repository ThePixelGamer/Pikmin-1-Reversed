#include <Windows.h>
#include <CommCtrl.h>
#include "..\Externals.h"

class UIMgr
{
private:
public:
	UIMgr();
	~UIMgr();

	void RegisterGenWindowClass(LPCSTR, void *, bool);
};