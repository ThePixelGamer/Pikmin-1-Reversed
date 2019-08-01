#ifdef SYSCORE_EXPORTS
#define SYSCORE_API __declspec(dllexport)
#else
#define SYSCORE_API __declspec(dllimport)
#endif

#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

class ControllerManager
{
public:
	ControllerManager();
	virtual ~ControllerManager();

};

#endif 