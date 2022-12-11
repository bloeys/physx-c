#include<PxPhysicsAPI.h>
#include "CPxDefaultCpuDispatcher.h"
#include "CPxDefaultAllocator.h"

#if PX_WINDOWS_FAMILY

#include <Windows.h>
#include <errhandlingapi.h>

constexpr DWORD NS_MS_VC_EXCEPTION = 0x406D1388;

LONG VectoredExceptionHandler(_EXCEPTION_POINTERS* exceptionInfo)
{
	if (exceptionInfo->ExceptionRecord->ExceptionCode == NS_MS_VC_EXCEPTION) {
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

LONG VectoredContinueHandler(_EXCEPTION_POINTERS* exceptionInfo)
{
	if (exceptionInfo->ExceptionRecord->ExceptionCode == NS_MS_VC_EXCEPTION) {
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

#endif // PX_WINDOWS_FAMILY

CPxDefaultCpuDispatcher* CPxDefaultCpuDispatcherCreate(CPxU32 numThreads, CPxU32* affinityMasks)
{
	CPxDefaultCpuDispatcher* cdcd = (CPxDefaultCpuDispatcher*)CPxAlloc(sizeof(CPxDefaultCpuDispatcher));

	// @NOTE: For debugging purposes threads can be named, and one way of doing this in Windows is by throwing an
	// exception with the code 0x406D1388 that gets caught by debuggers :)
	//
	// The default PhysX cpu dispatcher uses this technique when creating its worker threads and has a structured exception handling (SEH)
	// handler ('__except' block, similar to a catch block but only in MS C/C++) that normally would catch this if no debugger exists and everything is fine.
	//
	// However, if vectored exception handling (VEH) is used then the VEH handlers will get called first, and only if no VEH handler does anything will the SEH handler run.
	// This means that if the VEH handler decides to crash the program because of the exception no amount of __except/catch will help us.
	// 
	// As an example, Golang always has a VEH handler in place, and so this innocent exception gets sent to Go which has no idea what to do with it so it decides to crash everything.
	//
	// The only way to combat this is to have our own VEH handler+continue functions that knows how to handle this exception, and to ensure our handlers gets run BEFORE any other
	// and to return EXCEPTION_CONTINUE_EXECUTION from them. After our handler returns EXCEPTION_CONTINUE_EXECUTION our continue handler is called, and it should return the same value.
	//
	// EXCEPTION_CONTINUE_EXECUTION essentially says that this handler knows how to deal with the error and not to call any other VEH handlers, which is important because
	// if we call other handlers we might crash.
	//
	// To disable these VEH handlers (maybe you are using a debugger and want to receive the exception), you can set CPX_WINDOWS_ALLOW_THREAD_NAMING=1
#if PX_WINDOWS_FAMILY && !CPX_WINDOWS_ALLOW_THREAD_NAMING

	auto exceptionHandlerHandle = AddVectoredExceptionHandler(1, VectoredExceptionHandler);
	auto continueHandlerHandle = AddVectoredContinueHandler(1, VectoredContinueHandler);

	cdcd->obj = physx::PxDefaultCpuDispatcherCreate(numThreads, affinityMasks);
	if (exceptionHandlerHandle != NULL) {
		RemoveVectoredExceptionHandler(exceptionHandlerHandle);
	}

	if (continueHandlerHandle != NULL) {
		RemoveVectoredContinueHandler(continueHandlerHandle);
	}

	return cdcd;
#endif // PX_WINDOWS_FAMILY

	cdcd->obj = physx::PxDefaultCpuDispatcherCreate(numThreads, affinityMasks);
	return cdcd;
}

CPxCpuDispatcher* CPxDefaultCpuDispatcher_toCPxCpuDispatcher(CPxDefaultCpuDispatcher* cdcd)
{
	CPxCpuDispatcher* cCpuDisp = (CPxCpuDispatcher*)CPxAlloc(sizeof(CPxCpuDispatcher));
	cCpuDisp->obj = cdcd->obj;
	return cCpuDisp;
}

void CPxDefaultCpuDispatcher_release(CPxDefaultCpuDispatcher* cdcd)
{
	static_cast<physx::PxDefaultCpuDispatcher*>(cdcd->obj)->release();
	CPxDealloc(cdcd);
}