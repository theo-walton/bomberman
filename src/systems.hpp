#pragma once

#include "bomberman.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Sprite2D.hpp"
#include "components.hpp"
#include "ParticleExplosion.hpp"
#include "Cells.hpp"
#include "Effects.hpp"
#include "scripts.hpp"
#include "Text.hpp"

#define FACE_UP glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0, 0, 1))
#define FACE_DOWN glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0, 0, 1))
#define FACE_LEFT glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0, 0, 1))
#define FACE_RIGHT glm::mat4(1)

/*!
ECS systems, these systems are routines that operate on components. Components are
simple structs of data. Systems contain all the logic of the game.
Our ECS also uses scripts much like Unity.

It is recommended to alias this namespace like so: `namespace s = systems`;
Each system documents the components that it operates on.
Requirements in [] are optional and might provide additional functionality.
*/
namespace systems
{
	struct	ModelLoader : entt::ResourceLoader<ModelLoader, Model>
	{
		std::shared_ptr<Model>	load(const std::string modelPath) const
		{
			return std::shared_ptr<Model>(new Model(modelPath));
		}
	};

	//! requires: Model, Position, [Lighting]
	void	RenderModels(entt::DefaultRegistry&, entt::ResourceCache<Model>&, Window&, Camera&, double dt);

	//! requires: Particles, Position, TimedEffect
	void	RenderParticles(entt::DefaultRegistry&, Camera&);

	//! requires: Image
	void	Images(entt::DefaultRegistry&, entt::ResourceCache<Sprite2D>&, Window&);

	//! requires: TimedEffect
	void	TimedEffect(entt::DefaultRegistry&, double dt);

	//! requires: Button
	void	Buttons(entt::DefaultRegistry&, Window&);

	//! requires: Text
	void	Texts(entt::DefaultRegistry&, Window&);
	
	//! requires: Lighting; Applies falloff delta
	void	Lighting(entt::DefaultRegistry&, double dt);

	//! requires: Position, Velocity, [Collide]
	void	Velocity(entt::DefaultRegistry&, Cells&, double dt);

	//! requires: Player, Position, Velocity, Model
	void	Player(entt::DefaultRegistry&, Window&, Engine::KeyBind, Cells&, Camera&, double dt);

	//! requires: Explosion
	void	Explosion(entt::DefaultRegistry&, Cells&);

	//! requires: AI, Model, Velocity, [Position]
	void	AI(entt::DefaultRegistry&, Cells&, double dt);

	//! requires: Vulnerable, Position [Dangerous]
	void	Danger(entt::DefaultRegistry&, Cells&);

	//! requires: Text, KeyBind
	void	BindCheck(entt::DefaultRegistry&, Window&, Engine&);
	
	//! requires: Sound
	void	Sound(entt::DefaultRegistry&, double dt);
};
