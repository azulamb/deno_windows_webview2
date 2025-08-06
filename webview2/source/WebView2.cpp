#ifndef _WINDOWS
#include "WebView2.hpp"
#include "../exports.h"

WebView2Connector* WC::setWebView2Environment(ICoreWebView2Environment* env) {
	Log(__FUNCTIONW__ L"\n");
	this->env = env;
	return this;
}

EXPORT WebView2Connector* SetWebview2Environment(
	WebView2Connector* webview2,
	ICoreWebView2Environment* env
) {
	return webview2->setWebView2Environment(env);
}

WebView2Connector* WC::initSettings() {
	Log(__FUNCTIONW__ L"\n");
	this->settings2 = this->settings1.try_query<ICoreWebView2Settings2>();
	this->settings3 = this->settings1.try_query<ICoreWebView2Settings3>();
	this->settings4 = this->settings1.try_query<ICoreWebView2Settings4>();
	this->settings5 = this->settings1.try_query<ICoreWebView2Settings5>();
	this->settings6 = this->settings1.try_query<ICoreWebView2Settings6>();
	this->settings7 = this->settings1.try_query<ICoreWebView2Settings7>();
	this->settings8 = this->settings1.try_query<ICoreWebView2Settings8>();
	this->settings9 = this->settings1.try_query<ICoreWebView2Settings9>();

	return this;
}

EXPORT WebView2Connector* InitSettings(WebView2Connector* webview2)
{
	return webview2->initSettings();
}

WebView2Connector* WC::initControllers(ICoreWebView2Controller* controller) {
	Log(__FUNCTIONW__ L"\n");
	this->controller1 = controller;
	this->controller2 = controller1.query<ICoreWebView2Controller2>();
	this->controller3 = controller1.query<ICoreWebView2Controller3>();
	this->controller4 = controller1.query<ICoreWebView2Controller4>();

	return this;
}

EXPORT WebView2Connector* InitControllers(
	WebView2Connector* webview2,
	ICoreWebView2Controller* controller
) {
	return webview2->initControllers(controller);
}

#endif
