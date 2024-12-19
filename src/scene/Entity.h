#pragma once
#include <imgui.h>
#include <SDL.h>

#include <string>


class Entity
{
public:
	Entity();
	Entity(int id, std::string name, SDL_Rect rect, ImColor color);

	const std::string& getName();
	std::string getNameId() const;

	SDL_Point getPosition() const;
	void addPosition(const SDL_Point& offset);
	void setPosition(const SDL_Point& position);

	void update();
	void render() const;
	void renderImGui();

	Entity clone(int id);

	bool getRemoved() const;
	void remove();

private:
	int _id = -1;
	std::string _name;
	SDL_Rect _rect{};
	ImColor _color{};

	bool _fillRect = true;
	bool _isRemoved = false;
};
