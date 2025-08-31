import { createStringPointer, getString } from './convert.ts';
import type { Webview2Context } from './types.ts';

function getBool(
  webview2Connector: Deno.PointerValue,
  func: (
    webview2Connector: Deno.PointerValue,
    bool: Deno.PointerValue,
  ) => unknown,
): boolean {
  const data = new Int32Array([0]);
  const bool = Deno.UnsafePointer.of(data);
  func(webview2Connector, bool);
  return data[0] !== 0;
}

export class Settings {
  protected settings!: Deno.PointerValue<unknown>;

  public get pointer(): Deno.PointerValue<unknown> {
    return this.settings;
  }

  protected get symbols() {
    return this.context.lib.symbols;
  }

  protected getString(
    func: (
      w: Deno.PointerValue,
      buffer: Deno.PointerValue,
      size: Deno.PointerValue,
    ) => number,
  ): string {
    return getString(this.settings, func);
  }

  constructor(protected context: Webview2Context) {
    this.settings = context.lib.symbols.CreateSettings();
  }

  /**
   * Gets whether script execution is enabled in the WebView2 control.
   * @returns True if script execution is enabled; false otherwise.
   */
  public get isScriptEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsScriptEnabled,
    );
  }

  /**
   * Enables or disables script execution in the WebView2 control.
   * @param enable True to enable script execution; false to disable it.
   */
  public set isScriptEnabled(enable: boolean) {
    this.symbols.put_IsScriptEnabled(
      this.settings,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether web message handling is enabled in the WebView2 control.
   * @returns True if web message handling is enabled; false otherwise.
   */
  public get isWebMessageEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsWebMessageEnabled,
    );
  }

  /**
   * Enables or disables web message handling in the WebView2 control.
   * @param enable True to enable web message handling; false to disable it.
   */
  public set isWebMessageEnabled(enable: boolean) {
    this.symbols.put_IsWebMessageEnabled(
      this.settings,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether default script dialogs are enabled in the WebView2 control.
   * @returns True if default script dialogs are enabled; false otherwise.
   */
  public get areDefaultScriptDialogsEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_AreDefaultScriptDialogsEnabled,
    );
  }

  /**
   * Enables or disables default script dialogs in the WebView2 control.
   * @param enable True to enable default script dialogs; false to disable them.
   */
  public set areDefaultScriptDialogsEnabled(enable: boolean) {
    this.symbols.put_AreDefaultScriptDialogsEnabled(
      this.settings,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether the status bar is enabled in the WebView2 control.
   * @returns True if the status bar is enabled; false otherwise.
   */
  public get isStatusBarEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsStatusBarEnabled,
    );
  }

  /**
   * Enables or disables the status bar in the WebView2 control.
   * @param enable True to enable the status bar; false to disable it.
   */
  public set isStatusBarEnabled(enable: boolean) {
    this.symbols.put_IsStatusBarEnabled(
      this.settings,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether Developer Tools are enabled in the WebView2 control.
   * @returns True if Developer Tools are enabled; false otherwise.
   */
  public get areDevToolsEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_AreDevToolsEnabled,
    );
  }

  /**
   * Enables or disables the Developer Tools in the WebView2 control.
   * @param enable True to enable Developer Tools; false to disable them.
   */
  public set areDevToolsEnabled(enable: boolean) {
    this.symbols.put_AreDevToolsEnabled(
      this.settings,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether default context menus are enabled in the WebView2 control.
   * @returns True if default context menus are enabled; false otherwise.
   */
  public get areDefaultContextMenusEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_AreDefaultContextMenusEnabled,
    );
  }

  /**
   * Enables or disables the default context menus in the WebView2 control.
   * @param enable True to enable default context menus; false to disable them.
   */
  public set areDefaultContextMenusEnabled(enable: boolean) {
    this.symbols.put_AreDefaultContextMenusEnabled(
      this.settings,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether host objects are allowed in the WebView2 control.
   * @returns True if host objects are allowed; false otherwise.
   */
  public get areHostObjectsAllowed(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_AreHostObjectsAllowed,
    );
  }

  /**
   * Enables or disables host objects in the WebView2 control.
   * @param enable True to allow host objects; false to disallow them.
   */
  public set areHostObjectsAllowed(enable: boolean) {
    this.symbols.put_AreHostObjectsAllowed(
      this.settings,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether the zoom control is enabled in the WebView2 control.
   * @returns True if the zoom control is enabled; false otherwise.
   */
  public get isZoomControlEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsZoomControlEnabled,
    );
  }

  /**
   * Enables or disables the zoom control in the WebView2 control.
   * @param enable True to enable the zoom control; false to disable it.
   */
  public set isZoomControlEnabled(enable: boolean) {
    this.symbols.put_IsZoomControlEnabled(
      this.settings,
      enable ? 1 : 0,
    );
  }

  /**
   * Gets whether the built-in error page is enabled in the WebView2 control.
   * @returns True if the built-in error page is enabled; false otherwise.
   */
  public get isBuiltInErrorPageEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsBuiltInErrorPageEnabled,
    );
  }

  /**
   * Enables or disables the built-in error page in the WebView2 control.
   * @param enable True to enable the built-in error page; false to disable it.
   */
  public set isBuiltInErrorPageEnabled(enable: boolean) {
    this.symbols.put_IsBuiltInErrorPageEnabled(
      this.settings,
      enable ? 1 : 0,
    );
  }

  public get userAgent(): string {
    try {
      return this.getString(this.symbols.get_UserAgent);
    } catch (error) {
      throw new Error(`Failed to get UserAgent: ${error}`);
    }
  }

  public set userAgent(value: string) {
    this.symbols.put_UserAgent(
      this.settings,
      createStringPointer(value),
    );
  }

  /**
   * Gets whether browser accelerator keys are enabled in the WebView2 control.
   * @returns True if browser accelerator keys are enabled; false otherwise.
   */
  public get areBrowserAcceleratorKeysEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_AreBrowserAcceleratorKeysEnabled,
    );
  }

  /**
   * Enables or disables browser accelerator keys in the WebView2 control.
   * @param value True to enable browser accelerator keys; false to disable them.
   */
  public set areBrowserAcceleratorKeysEnabled(value: boolean) {
    this.symbols.put_AreBrowserAcceleratorKeysEnabled(
      this.settings,
      value ? 1 : 0,
    );
  }

  /**
   * Gets whether password autosave is enabled in the WebView2 control.
   * @returns True if password autosave is enabled; false otherwise.
   */
  public get isPasswordAutosaveEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsPasswordAutosaveEnabled,
    );
  }

  /**
   * Enables or disables password autosave in the WebView2 control.
   * @param value True to enable password autosave; false to disable it.
   */
  public set isPasswordAutosaveEnabled(value: boolean) {
    this.symbols.put_IsPasswordAutosaveEnabled(
      this.settings,
      value ? 1 : 0,
    );
  }

  /**
   * Gets whether general autofill is enabled in the WebView2 control.
   * @returns True if general autofill is enabled; false otherwise.
   */
  public get isGeneralAutofillEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsGeneralAutofillEnabled,
    );
  }

  /**
   * Enables or disables general autofill in the WebView2 control.
   * @param value True to enable general autofill; false to disable it.
   */
  public set isGeneralAutofillEnabled(value: boolean) {
    this.symbols.put_IsGeneralAutofillEnabled(
      this.settings,
      value ? 1 : 0,
    );
  }

  /**
   * Gets whether pinch zoom is enabled in the WebView2 control.
   * @returns True if pinch zoom is enabled; false otherwise.
   */
  public get isPinchZoomEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsPinchZoomEnabled,
    );
  }

  /**
   * Enables or disables pinch zoom in the WebView2 control.
   * @param value True to enable pinch zoom; false to disable it.
   */
  public set isPinchZoomEnabled(value: boolean) {
    this.symbols.put_IsPinchZoomEnabled(
      this.settings,
      value ? 1 : 0,
    );
  }

  /**
   * Gets whether swipe navigation is enabled in the WebView2 control.
   * @returns True if swipe navigation is enabled; false otherwise.
   */
  public get isSwipeNavigationEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsSwipeNavigationEnabled,
    );
  }

  /**
   * Enables or disables swipe navigation in the WebView2 control.
   * @param value True to enable swipe navigation; false to disable it.
   */
  public set isSwipeNavigationEnabled(value: boolean) {
    this.symbols.put_IsSwipeNavigationEnabled(
      this.settings,
      value ? 1 : 0,
    );
  }

  /**
   * Gets whether reputation checking is required in the WebView2 control.
   * @returns True if reputation checking is required; false otherwise.
   */
  public get isReputationCheckingRequired(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsReputationCheckingRequired,
    );
  }

  /**
   * Enables or disables reputation checking in the WebView2 control.
   * @param value True to require reputation checking; false to disable it.
   */
  public set isReputationCheckingRequired(value: boolean) {
    this.symbols.put_IsReputationCheckingRequired(
      this.settings,
      value ? 1 : 0,
    );
  }

  /**
   * Gets whether non-client region support is enabled in the WebView2 control.
   * @returns True if non-client region support is enabled; false otherwise.
   */
  public get isNonClientRegionSupportEnabled(): boolean {
    return getBool(
      this.settings,
      this.symbols.get_IsNonClientRegionSupportEnabled,
    );
  }

  /**
   * Enables or disables non-client region support in the WebView2 control.
   * @param value True to enable non-client region support; false to disable it.
   */
  public set isNonClientRegionSupportEnabled(value: boolean) {
    this.symbols.put_IsNonClientRegionSupportEnabled(
      this.settings,
      value ? 1 : 0,
    );
  }
}
