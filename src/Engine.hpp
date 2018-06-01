#pragma once

#include <vector>
#include <string>
#include "Time.hpp"
#include "Window.hpp"

class IState;

//! Manages game States
class Engine
{	
	std::vector<IState*> _states;
	Time _time;
	IState *_deleteMe;
public:

	struct KeyBind
	{
		int up;
		int down;
		int left;
		int right;
		int bomb;
	};	
	
	Window& window;
	i::ISoundEngine& sound;
	bool isRunning;
	KeyBind keyBind;
	Engine(Window& window, i::ISoundEngine& sound);
	~Engine(void);
	void PushState(IState* state);
	void PopState(void);
	void ChangeState(IState* state);
	void Run(void);
};
