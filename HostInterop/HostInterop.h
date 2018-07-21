#pragma once

using namespace System;

namespace HostInterop
{
	ref class HookManager;
	ref class TextThread;
	ref class HookParam;
	ref class ThreadParam;

	public ref class Host abstract sealed
	{
	public:
		static void Open();
		static bool Start();
		static void Close();
		static HookManager^ GetHookManager();
		static bool InjectProcess(DWORD pid);
		static bool DetachProcess(DWORD pid);
		//static bool InsertHook(DWORD pid, HookParam hp, std::string name);
		static bool RemoveHook(DWORD pid, DWORD addr);
	};

	public ref class HookManager
	{
	internal:
		HookManager(::HookManager* native);
		::HookManager* native;
	public:
		TextThread^ FindSingle(DWORD number);
		IntPtr^ GetHostPipe(DWORD pid);
		void ClearCurrent();
		void SelectCurrent(DWORD num);
		void SetCurrent(TextThread it);
		void AddConsoleOutput(String^ text);
		HookParam^ GetHookParam(DWORD pid, DWORD addr);
		String^ GetHookName(DWORD pid, DWORD addr);

		//void RegisterThreadCreateCallback(ThreadEventCallback cf) { create = cf; }
		//void RegisterThreadRemoveCallback(ThreadEventCallback cf) { remove = cf; }
		//void RegisterThreadResetCallback(ThreadEventCallback cf) { reset = cf; }
		//void RegisterProcessAttachCallback(ProcessEventCallback cf) { attach = cf; }
		//void RegisterProcessDetachCallback(ProcessEventCallback cf) { detach = cf; }

		//void SetSplitInterval(unsigned int splitDelay) { this->splitDelay = splitDelay; }
	};

	public ref class TextThread
	{
	internal:
		TextThread(::TextThread* native);
		::TextThread* native;
	};

	public ref class HookParam
	{
	internal:
		HookParam(::HookParam native);
	};

	public ref class ThreadParam
	{

	};
}