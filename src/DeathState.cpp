#include "DeathState.hpp"

DeathState::DeathState(Engine& engine, std::string level) :
_engine(engine), _window(engine.window)
{
	auto e = _registry.create();
	_registry.attach<c::EngineTag>(e, engine);

	auto entity = _registry.create();

	_registry.assign<c::Button>(entity,
		scripts::switch_level(level)
	);

	_registry.assign<c::Image>(entity,
		"assets/textures/death.png"
	);
}

DeathState::~DeathState(void) {}

void	DeathState::Update(double dt)
{
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
}
