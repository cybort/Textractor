#pragma once
#include "../texthook/hookman.h"
#include "../texthook/textthread.h"
#include "../texthook/host.h"
#include "HostInterop.h"

using namespace System;

std::wstring ToNative(String^ orig)
{
	std::wstring ret = L"";
	auto arr = orig->ToCharArray();
	for each(auto i in arr) ret += i;
	return ret;
}

HookParam ToNative(HostInterop::HookParam% orig)
{
	return {};
}

namespace HostInterop
{
	void Host::Open() { OpenHost(); }
	bool Host::Start() { return StartHost(); }
	void Host::Close() { CloseHost(); }
	HookManager^ Host::GetHookManager() { return gcnew HookManager(GetHostHookManager()); }
	bool Host::InjectProcess(DWORD pid) { return ::InjectProcess(pid); }
	bool Host::DetachProcess(DWORD pid) { return ::DetachProcess(pid); }
	//bool Host::InsertHook(DWORD pid, HookParam hp, std::string name) { return ::InsertHook(pid, ToNative(hp), ""); };
	bool Host::RemoveHook(DWORD pid, DWORD addr) { return ::RemoveHook(pid, addr); }


	HookManager::HookManager(::HookManager* native) : native(native) {}
	TextThread^ HookManager::FindSingle(DWORD number) { return gcnew TextThread(native->FindSingle(number)); }
	IntPtr^ HookManager::GetHostPipe(DWORD pid) { return gcnew IntPtr(native->GetHostPipe(pid)); }
	void HookManager::ClearCurrent() { native->ClearCurrent(); }
	void HookManager::SelectCurrent(DWORD num) { native->SelectCurrent(num); }
	void HookManager::SetCurrent(TextThread it) { native->SetCurrent(it.native); }
	void HookManager::AddConsoleOutput(String^ text) { native->AddConsoleOutput(ToNative(text)); }
	HookParam^ HookManager::GetHookParam(DWORD pid, DWORD addr) { return gcnew HookParam(native->GetHookParam(pid, addr)); }
	String^ HookManager::GetHookName(DWORD pid, DWORD addr) { return gcnew String(native->GetHookName(pid, addr).c_str()); }

	//void RegisterThreadCreateCallback(ThreadEventCallback cf) { create = cf; }
	//void RegisterThreadRemoveCallback(ThreadEventCallback cf) { remove = cf; }
	//void RegisterThreadResetCallback(ThreadEventCallback cf) { reset = cf; }
	//void RegisterProcessAttachCallback(ProcessEventCallback cf) { attach = cf; }
	//void RegisterProcessDetachCallback(ProcessEventCallback cf) { detach = cf; }

	//void SetSplitInterval(unsigned int splitDelay) { this->splitDelay = splitDelay; }


	TextThread::TextThread(::TextThread* native) : native(native) {}


	HookParam::HookParam(::HookParam native) {}
}