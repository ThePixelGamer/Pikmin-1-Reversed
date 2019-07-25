#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef SYSCORE_H
#define SYSCORE_H

	#pragma once	

	#include <winsock2.h>
	#include <Windows.h>
	#pragma comment(lib,"ws2_32.lib") //Winsock Library

	SYSCORE_API HINSTANCE hInstance;

#endif