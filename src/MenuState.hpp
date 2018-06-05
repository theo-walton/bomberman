#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "IState.hpp"
#include "Model.hpp"
#include "Sprite2D.hpp"
#include <entt/entt.hpp>

class MenuState : public IState
{
	Engine& _engine;
	Window& _window;
	Camera _camera;
	i::ISound *_music;
	entt::DefaultRegistry _registry;
	entt::ResourceCache<Sprite2D> _imageCache;
	
public:
	MenuState(Engine& engine);
	~MenuState(void);
	void Update(double dt);
};
