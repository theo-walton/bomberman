#include "SettingState.hpp"
#include "components.hpp"
#include "MenuState.hpp"
#include "systems.hpp"

namespace c = components;

static int	keyFromAction(c::ActionType action, Engine& engine)
{
	switch (action)
	{
	case (c::BOMB_ACTION):
		return engine.keyBind.bomb;
	case (c::UP_ACTION):
		return engine.keyBind.up;
	case (c::LEFT_ACTION):
		return engine.keyBind.left;
	case (c::RIGHT_ACTION):
		return engine.keyBind.right;
	case (c::DOWN_ACTION):
		return engine.keyBind.down;
	}
	return 0;
}

static std::string	keyToString(int key)
{
	std::string out;

        if (key == ' ')
                out += "space";
        else if (key == GLFW_KEY_RIGHT)
                out += "right arrow";
        else if (key == GLFW_KEY_LEFT)
                out += "left arrow";
        else if (key == GLFW_KEY_UP)
                out += "up arrow";
        else if (key == GLFW_KEY_DOWN)
                out += "down arrow";
        else
                out += (char)key;
	
	return out;
}

static void	keybind_button(entt::DefaultRegistry& r,
			       glm::vec2 botleft,
			       glm::vec2 topright,
			       std::string imagePath,
			       c::ActionType action,
			       Engine& engine)
{
	auto bind = r.create();
	auto event = [action](entt::DefaultRegistry& r, uint32_t e)
	{
		auto &text = r.get<c::Text>(e);
		text.words = "press a key";
		if (!r.has<c::KeyBind>(e))
			r.assign<c::KeyBind>(e, action);
	};
	r.assign<c::Button>(bind, event, botleft, topright);
	r.assign<c::Image>(bind, imagePath, botleft, topright);	
	r.assign<c::Text>(bind,
			  keyToString(keyFromAction(action, engine)),
			  botleft + 0.1 * (topright - botleft),
			  topright - 0.1 * (topright - botleft));
}

static void	resolution_button(entt::DefaultRegistry& r,
				  glm::vec2 botleft,
				  glm::vec2 topright,
				  std::string imagePath,
				  int width,
				  int height,
				  bool fullscreen,
				  Window& window,
				  std::string text)
{
	auto reso = r.create();
	auto event = [&window, width, height, fullscreen](entt::DefaultRegistry& r, uint32_t e)
	{
		const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		int MinW = std::min(width, mode->width);
		int MinH = std::min(height, mode->height);

		if (MinW * 9 > MinH * 16)
			MinW = MinH * 16 / 9;
		else
			MinH = MinW * 9 / 16;
		
		if (fullscreen)
		{
			glfwSetWindowMonitor(window.GetGLWindow(),
					     glfwGetPrimaryMonitor(),
					     0, 0, MinW, MinH, mode->refreshRate);
		}
		else
			glfwSetWindowMonitor(window.GetGLWindow(), NULL,
					     0, 0, MinW, MinH, GLFW_DONT_CARE);
	};
	r.assign<c::Button>(reso, event, botleft, topright);
	r.assign<c::Image>(reso, imagePath, botleft, topright);
	r.assign<c::Text>(reso,
			  text,
			  botleft + 0.1 * (topright - botleft),
			  topright - 0.1 * (topright - botleft));
}

SettingState::SettingState(Engine& e) :
_engine(e), _window(e.window)
{

//create the settings backdrop

	auto settingMenu = _registry.create();
	_registry.assign<c::Image>(settingMenu, "assets/textures/setting_menu.png");
	
//creating a button to go back to menu
	
	auto menuButton = _registry.create();
	auto gotoMenu = [this](entt::DefaultRegistry& r, uint32_t e)
	{
		_engine.PopState();
	};
	_registry.assign<c::Button>(menuButton,
				    gotoMenu,
				    glm::vec2(-0.2, -0.9),
				    glm::vec2(0.2, -0.7));
	_registry.assign<c::Image>(menuButton,
				   "assets/textures/metal_sheet.png",
				   glm::vec2(-0.2, -0.9),
				   glm::vec2(0.2, -0.7));
	_registry.assign<c::Text>(menuButton,
				  "BACK",
				  glm::vec2(-0.16, -0.88),
				  glm::vec2(0.16, -0.72));

//creating a keybind buttons

	keybind_button(_registry,
		       glm::vec2(-0.6, 0.7),
		       glm::vec2(-0.4, 0.8),
		       "assets/textures/metal_sheet.png",
		       c::BOMB_ACTION,
		       _engine);
	keybind_button(_registry,
		       glm::vec2(-0.6, 0.55),
		       glm::vec2(-0.4, 0.65),
		       "assets/textures/metal_sheet.png",
		       c::UP_ACTION,
		       _engine);
	keybind_button(_registry,
		       glm::vec2(-0.6, 0.4),
		       glm::vec2(-0.4, 0.5),
		       "assets/textures/metal_sheet.png",
		       c::DOWN_ACTION,
		       _engine);
	keybind_button(_registry,
		       glm::vec2(-0.6, 0.25),
		       glm::vec2(-0.4, 0.35),
		       "assets/textures/metal_sheet.png",
		       c::RIGHT_ACTION,
		       _engine);
	keybind_button(_registry,
		       glm::vec2(-0.6, 0.1),
		       glm::vec2(-0.4, 0.2),
		       "assets/textures/metal_sheet.png",
		       c::LEFT_ACTION,
		       _engine);

//creating text to accompany keybind buttons

	auto bombText = _registry.create();
	_registry.assign<c::Text>(bombText,
				  "place bomb:",
				  glm::vec2(-0.85, 0.7),
				  glm::vec2(-0.6, 0.8));
	auto upText = _registry.create();
	_registry.assign<c::Text>(upText,
				  "move up:",
				  glm::vec2(-0.85, 0.55),
				  glm::vec2(-0.6, 0.65));
	auto downText = _registry.create();
	_registry.assign<c::Text>(downText,
				  "move down:",
				  glm::vec2(-0.85, 0.4),
				  glm::vec2(-0.6, 0.5));
	auto rightText = _registry.create();
	_registry.assign<c::Text>(rightText,
				  "move right:",
				  glm::vec2(-0.85, 0.25),
				  glm::vec2(-0.6, 0.35));
	auto leftText = _registry.create();
	_registry.assign<c::Text>(leftText,
				  "move left:",
				  glm::vec2(-0.85, 0.1),
				  glm::vec2(-0.6, 0.2));

//create resolution buttons

	resolution_button(_registry,
                          glm::vec2(0.6, 0.7),
                          glm::vec2(0.85, 0.8),
                          "assets/textures/metal_sheet.png",
                          1200,
                          675,
                          false,
                          _window,
                          "1200 X 675");
	
	resolution_button(_registry,
			  glm::vec2(0.6, 0.55),
			  glm::vec2(0.85, 0.65),
			  "assets/textures/metal_sheet.png",
			  1600,
			  900,
			  false,
			  _window,
			  "1600 X 900");

        resolution_button(_registry,
                          glm::vec2(0.6, 0.4),
                          glm::vec2(0.85, 0.5),
                          "assets/textures/metal_sheet.png",
                          2400,
                          1350,
                          false,
                          _window,
			  "2400 X 1350");

	resolution_button(_registry,
                          glm::vec2(0.6, 0.25),
                          glm::vec2(0.85, 0.35),
                          "assets/textures/metal_sheet.png",
                          4000,
                          2250,
                          false,
                          _window,
                          "4000 X 2250");
	
	resolution_button(_registry,
                          glm::vec2(0.6, 0.1),
                          glm::vec2(0.85, 0.2),
                          "assets/textures/metal_sheet.png",
                          100000,
                          100000,
                          true,
                          _window,
			  "Fullscreen");

}

SettingState::~SettingState(void) {}

void	SettingState::Update(double dt)
{
	systems::BindCheck(_registry, _window, _engine);
	systems::Buttons(_registry, _window);
	systems::Images(_registry, _imageCache, _window);
	systems::Texts(_registry, _window);
}
