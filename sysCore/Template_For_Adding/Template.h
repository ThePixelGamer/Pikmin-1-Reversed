#pragma once

#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef TEMPLATE_H
#define TEMPLATE_H

//
//	Add any headers here!
//

class SYSCORE_API Template
{
public:
	Template();
	~Template();
};

#endif