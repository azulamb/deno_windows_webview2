#ifdef _WINDOWS
#include "./source/WebView2.hpp"

// Settings
static TCHAR WINDOW_CLASS_NAME[] = L"SampleWeapnWindow";
static TCHAR WINDOW_TITLE[] = L"Weapn";

struct DATA {
	HWND hWnd;
	WebView2* webview2;
	Environments* environments;
	Settings* settings;
	Controllers* controllers;
	EventRegistrationToken token;
} data;

// Import funcs.

typedef HRESULT (*ImportedCreateCoreWebView2Controller)(
	Environments* environments,
	HWND hWnd,
	HRESULT(*callback)(HRESULT, ICoreWebView2Controller*),
	Controllers* controllers
);
ImportedCreateCoreWebView2Controller Environments_CreateCoreWebView2Controller;

typedef WebView2* (*ImportedCreateWebView2)();
ImportedCreateWebView2 WebView2_Create;

typedef Environments* (*ImportedCreateEnvironments)();
ImportedCreateEnvironments Environments_Create;

typedef Settings* (*ImportedCreateSettings)();
ImportedCreateSettings Settings_Create;

typedef Controllers* (*ImportedCreateControllers)();
ImportedCreateControllers Controllers_Create;

typedef HRESULT (*Imported_CreateCoreWebView2EnvironmentWithOptions)(
	Environments* environments,
	PCWSTR browserExecutableFolder,
	PCWSTR userDataFolder,
	ICoreWebView2EnvironmentOptions* environmentOptions,
	HRESULT(*callback)(HRESULT result, ICoreWebView2Environment* env)
);
Imported_CreateCoreWebView2EnvironmentWithOptions Global_CreateCoreWebView2EnvironmentWithOptions;

typedef EventRegistrationToken* (*ImportedCreateEventRegistrationToken)();
ImportedCreateEventRegistrationToken EventRegistrationToken_Create;

typedef void (*ImportedRemoveEventRegistrationToken)(EventRegistrationToken* token);
ImportedRemoveEventRegistrationToken EventRegistrationToken_Remove;

typedef HRESULT(*Importedput_Bounds)(Controllers* controllers, RECT bounds);
Importedput_Bounds Controllers_put_Bounds;

typedef HRESULT (*Importedget_CoreWebView2)(Controllers* controllers, WebView2* webview2);
Importedget_CoreWebView2 Controllers_get_CoreWebView2;

typedef HRESULT (*Importedget_Settings)(WebView2* webview2, Settings* settings);
Importedget_Settings WebView2_get_Settings;

typedef HRESULT (*Importedput_IsScriptEnabled)(Settings* settings, BOOL isScriptEnabled);
Importedput_IsScriptEnabled Settings_put_IsScriptEnabled;

typedef HRESULT (*Importedput_IsWebMessageEnabled)(Settings* settings, BOOL isWebMessageEnabled);
Importedput_IsWebMessageEnabled Settings_put_IsWebMessageEnabled;

typedef HRESULT (*Importedput_AreDefaultScriptDialogsEnabled)(Settings* settings, BOOL areDefaultScriptDialogsEnabled);
Importedput_AreDefaultScriptDialogsEnabled Settings_put_AreDefaultScriptDialogsEnabled;

typedef HRESULT (*Importedput_AreDevToolsEnabled)(Settings* settings, BOOL areDevToolsEnabled);
Importedput_AreDevToolsEnabled Settings_put_AreDevToolsEnabled;

typedef HRESULT (*Importedput_IsStatusBarEnabled)(Settings* settings, BOOL isStatusBarEnabled);
Importedput_IsStatusBarEnabled Settings_put_IsStatusBarEnabled;

typedef HRESULT (*Importedput_AreDefaultContextMenusEnabled)(Settings* settings, BOOL enabled);
Importedput_AreDefaultContextMenusEnabled Settings_put_AreDefaultContextMenusEnabled;

typedef HRESULT (*Importedput_AreHostObjectsAllowed)(Settings* settings, BOOL allowed);
Importedput_AreHostObjectsAllowed Settings_put_AreHostObjectsAllowed;

typedef HRESULT (*Importedput_IsBuiltInErrorPageEnabled)(Settings* settings, BOOL enabled);
Importedput_IsBuiltInErrorPageEnabled Settings_put_IsBuiltInErrorPageEnabled;

typedef HRESULT (*Importedput_IsZoomControlEnabled)(Settings* settings, BOOL enabled);
Importedput_IsZoomControlEnabled Settings_put_IsZoomControlEnabled;

typedef HRESULT(*ImportedNavigate)(WebView2* webview2, LPCWSTR uri);
ImportedNavigate WebView2_Navigate;

typedef HRESULT(*Importedremove_WebMessageReceived)(WebView2* webview2, EventRegistrationToken token);
Importedremove_WebMessageReceived WebView2_remove_WebMessageReceived;

void ExitError(int code) {
	DWORD error = GetLastError();
	exit(code);
}

void DebugLog(const WCHAR* message) {
	OutputDebugString(message);
}

void LoadDLL() {
	HMODULE hModule = LoadLibrary(L"../Debug/webview2.dll");
	if (hModule == NULL) {
		return;
	}
	Environments_CreateCoreWebView2Controller = (ImportedCreateCoreWebView2Controller)GetProcAddress(hModule, "Environments_CreateCoreWebView2Controller");
	WebView2_Create = (ImportedCreateWebView2)GetProcAddress(hModule, "WebView2_Create");
	Settings_Create = (ImportedCreateSettings)GetProcAddress(hModule, "Settings_Create");
	Environments_Create = (ImportedCreateEnvironments)GetProcAddress(hModule, "Environments_Create");
	Controllers_Create = (ImportedCreateControllers)GetProcAddress(hModule, "Controllers_Create");
	Global_CreateCoreWebView2EnvironmentWithOptions = (Imported_CreateCoreWebView2EnvironmentWithOptions)GetProcAddress(hModule, "Global_CreateCoreWebView2EnvironmentWithOptions");
	EventRegistrationToken_Create = (ImportedCreateEventRegistrationToken)GetProcAddress(hModule, "EventRegistrationToken_Create");
	EventRegistrationToken_Remove = (ImportedRemoveEventRegistrationToken)GetProcAddress(hModule, "EventRegistrationToken_Remove");
	Controllers_put_Bounds = (Importedput_Bounds)GetProcAddress(hModule, "Controllers_put_Bounds");
	Controllers_get_CoreWebView2 = (Importedget_CoreWebView2)GetProcAddress(hModule, "Controllers_get_CoreWebView2");
	WebView2_get_Settings = (Importedget_Settings)GetProcAddress(hModule, "WebView2_get_Settings");
	Settings_put_IsScriptEnabled = (Importedput_IsScriptEnabled)GetProcAddress(hModule, "Settings_put_IsScriptEnabled");
	Settings_put_IsWebMessageEnabled = (Importedput_IsWebMessageEnabled)GetProcAddress(hModule, "Settings_put_IsWebMessageEnabled");
	Settings_put_AreDefaultScriptDialogsEnabled = (Importedput_AreDefaultScriptDialogsEnabled)GetProcAddress(hModule, "Settings_put_AreDefaultScriptDialogsEnabled");
	Settings_put_AreDevToolsEnabled = (Importedput_AreDevToolsEnabled)GetProcAddress(hModule, "Settings_put_AreDevToolsEnabled");
	Settings_put_IsStatusBarEnabled = (Importedput_IsStatusBarEnabled)GetProcAddress(hModule, "Settings_put_IsStatusBarEnabled");
	Settings_put_AreDefaultContextMenusEnabled = (Importedput_AreDefaultContextMenusEnabled)GetProcAddress(hModule, "Settings_put_AreDefaultContextMenusEnabled");
	Settings_put_AreHostObjectsAllowed = (Importedput_AreHostObjectsAllowed)GetProcAddress(hModule, "Settings_put_AreHostObjectsAllowed");
	Settings_put_IsBuiltInErrorPageEnabled = (Importedput_IsBuiltInErrorPageEnabled)GetProcAddress(hModule, "Settings_put_IsBuiltInErrorPageEnabled");
	Settings_put_IsZoomControlEnabled = (Importedput_IsZoomControlEnabled)GetProcAddress(hModule, "Settings_put_IsZoomControlEnabled");
	WebView2_Navigate = (ImportedNavigate)GetProcAddress(hModule, "WebView2_Navigate");
	WebView2_remove_WebMessageReceived = (Importedremove_WebMessageReceived)GetProcAddress(hModule, "WebView2_remove_WebMessageReceived");
}

void InitApp() {
#ifdef _CRTDBG_MAP_ALLOC
#  ifdef _DEBUG
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#  endif
#endif
	DebugLog(L"InitApp\n");
	SetEnvironmentVariable(L"WEBVIEW2_USER_DATA_FOLDER", L".\\cache");

	HWND consoleWindow = GetConsoleWindow();
	if (consoleWindow) {
		//ShowWindow(consoleWindow, SW_HIDE);
		ShowWindowAsync(consoleWindow, SW_HIDE);
	}
}

void OnResizeScreen() {
	DebugLog(L"OnResizeScreen\n");
	if (data.webview2 == nullptr) {
		return;
	}
	RECT bounds;
	::GetClientRect(data.hWnd, &bounds);
	Controllers_put_Bounds(data.controllers, bounds);
}

LRESULT WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE: {
		//CREATESTRUCT* tpCreateSt = (CREATESTRUCT*)lParam;
		//ShowWindow(hWnd, SW_SHOWDEFAULT); // SW_SHOWDEFAULT
		//UpdateWindow(hWnd);
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_SIZE:
		OnResizeScreen();
		break;
	}
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

int InitWindow(HINSTANCE hInstance, HWND* hWnd) {
	DebugLog(L"InitWindow\n");
	//*hWnd = test();
	DWORD style = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
	DWORD exstyle = 0; // WS_EX_LAYERED;
	WNDCLASSEX wcex;

	UINT size = sizeof(WNDCLASSEX);
	memset(&wcex, 0, size);
	wcex.cbSize = size;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProcedure;
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = WINDOW_CLASS_NAME;
	wcex.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
	wcex.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);
	wcex.hInstance = nullptr;// hInstance;

	if (!RegisterClassExW(&wcex)) {
		return 1;
	}

	*hWnd = CreateWindowEx(
		exstyle,
		wcex.lpszClassName,
		WINDOW_TITLE,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		400, 300,
		nullptr,
		nullptr,
		nullptr,//wcex.hInstance,
		nullptr
	);
	if (!*hWnd) {
		return 2;
	}

	return 0;
}

/*HRESULT CallbackAddRasterizationScaleChanged(ICoreWebView2Controller* sender, IUnknown* args) {
	double rasterizationScale;
	data.webview2->get_RasterizationScale(&rasterizationScale);
	DebugLog(L"OnRasterizationScaleChanged:");
	WCHAR value[32];
	swprintf_s(value, 32, L"%f\n", rasterizationScale);
	DebugLog(value);
	return S_OK;
}*/

HRESULT CreateCoreWebView2ControllerCallback(HRESULT result, ICoreWebView2Controller* controller) {
	if (controller == nullptr)
	{
		return S_OK;
	}
	Controllers_get_CoreWebView2(data.controllers, data.webview2);
	//data.webview2->add_RasterizationScaleChanged(CallbackAddRasterizationScaleChanged, &(data.token));

	WebView2_get_Settings(data.webview2, data.settings);

	// Resize WebView to fit the bounds of the parent window
	OnResizeScreen();

	// On create webview2
	Settings_put_IsScriptEnabled(data.settings, true);
	Settings_put_IsWebMessageEnabled(data.settings, true);
	Settings_put_AreDefaultScriptDialogsEnabled(data.settings, true);
	Settings_put_AreDevToolsEnabled(data.settings, true);
	Settings_put_IsStatusBarEnabled(data.settings, false);
	Settings_put_AreDefaultContextMenusEnabled(data.settings, false);
	Settings_put_AreHostObjectsAllowed(data.settings, true);
	Settings_put_IsBuiltInErrorPageEnabled(data.settings, true);
	Settings_put_IsZoomControlEnabled(data.settings, false);
	//data.webview2->put_UserAgent();
	//data.webview2->put_AreBrowserAcceleratorKeysEnabled(false);
	//data.webview2->put_IsGeneralAutofillEnabled(false);
	//data.webview2->put_IsPasswordAutosaveEnabled(false);
	//data.webview2->put_IsPinchZoomEnabled(false);
	//data.webview2->put_IsSwipeNavigationEnabled(false);

	HRESULT result2 = WebView2_Navigate(data.webview2, L"https://www.google.co.jp/");

	return S_OK;
}

HRESULT CreateCoreWebView2EnvironmentWithOptionsCallback(HRESULT result, ICoreWebView2Environment* env) {
	HWND hWnd = data.hWnd;

	return Environments_CreateCoreWebView2Controller(data.environments, data.hWnd, CreateCoreWebView2ControllerCallback, data.controllers);
}

int InitWebView(HWND hWnd) {
	DebugLog(L"InitWebView\n");
	HRESULT hresult;
	data.webview2 = WebView2_Create();
	data.environments = Environments_Create();
	data.settings = Settings_Create();
	data.controllers = Controllers_Create();

	hresult = Global_CreateCoreWebView2EnvironmentWithOptions(
		data.environments,
		nullptr,
		nullptr,
		nullptr,
		CreateCoreWebView2EnvironmentWithOptionsCallback
	);

	return hresult;
}

/*HRESULT OnWebMessageReceived(ICoreWebView2* coreWebview2, ICoreWebView2WebMessageReceivedEventArgs* args) {
	return 0;
}*/

//int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
int main() {
	LoadDLL();

	InitApp();

	data.hWnd = nullptr;
	data.webview2 = nullptr;
	HINSTANCE hInstance = GetModuleHandle(0);

	int error = InitWindow(hInstance, &(data.hWnd));
	if (error != 0)
	{
		ExitError(error);
	}

	InitWebView(data.hWnd);
	//data.webview2->get_Settings();
	//data.webview2->initSettings();
	//data.webview2->put_AreDevToolsEnabled(TRUE);

	auto token = EventRegistrationToken_Create();
	//data.webview2->add_WebMessageReceived(OnWebMessageReceived, token);

	DebugLog(L"Start loop.\n");
	MSG msg;
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	WebView2_remove_WebMessageReceived(data.webview2 , *token);
	EventRegistrationToken_Remove(token);
	return (int)msg.wParam;
}
#endif
