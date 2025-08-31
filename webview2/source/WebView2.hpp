#pragma once
#include <WebView2.h>
#include <windows.h>
#include <wil/com.h>

class WebView2 {
public:
	wil::com_ptr<ICoreWebView2> webview1;
	wil::com_ptr<ICoreWebView2_2> webview2;
	wil::com_ptr<ICoreWebView2_3> webview3;
};

class Environments {
public:
	ICoreWebView2Environment* env1;
};

class Settings {
public:
	wil::com_ptr<ICoreWebView2Settings> settings1;
	wil::com_ptr<ICoreWebView2Settings2> settings2;
	wil::com_ptr<ICoreWebView2Settings3> settings3;
	wil::com_ptr<ICoreWebView2Settings4> settings4;
	wil::com_ptr<ICoreWebView2Settings5> settings5;
	wil::com_ptr<ICoreWebView2Settings6> settings6;
	wil::com_ptr<ICoreWebView2Settings7> settings7;
	wil::com_ptr<ICoreWebView2Settings8> settings8;
	wil::com_ptr<ICoreWebView2Settings9> settings9;
};

class Controllers {
public:
	wil::com_ptr<ICoreWebView2Controller> controller1;
	wil::com_ptr<ICoreWebView2Controller2> controller2;
	wil::com_ptr<ICoreWebView2Controller3> controller3;
	wil::com_ptr<ICoreWebView2Controller4> controller4;
};

#ifndef _WINDOWS
#include <wrl.h>

using namespace Microsoft::WRL;

#define CHECK(p) if (!p) { return E_POINTER; }
void Log(const WCHAR* message);
void CopyString(wchar_t const* source, rsize_t* size, LPWSTR target);


/*class WC : public WebView2Connector {
protected:

public:
	virtual ~WC() {
		Log(__FUNCTIONW__ L"\n");
		this->Close();
	}

	virtual HRESULT Close(void);
};*/

#endif
