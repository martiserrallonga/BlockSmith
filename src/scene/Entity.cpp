#include "Entity.h"

#include "EngineGetter.h"
#include "LoggerGetter.h"
#include "Renderer.h"
#include <format>

Entity::Entity() {
	Log::Warning("Entity default constructor should not be called.");
}

Entity::Entity(const int id, std::string name, const SDL_Rect rect, const ImColor color)
	:_id(id)
	, _name(std::move(name))
	, _rect(rect)
	, _color(color) {}

const std::string& Entity::getName() {
	return _name;
}

std::string Entity::getNameId() const {
	return std::format("{}_{:0>3}", _name, _id);
}

SDL_Point Entity::getPosition() const {
	return { .x = _rect.x, .y = _rect.y };
}

void Entity::addPosition(const SDL_Point& offset) {
	_rect.x += offset.x;
	_rect.y += offset.y;
}

void Entity::setPosition(const SDL_Point& position) {
	_rect.x = position.x;
	_rect.y = position.y;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void Entity::update() {}

void Entity::render() const {
	const Renderer& renderer = Engine::Get().getRenderer();
	renderer.setColor(_color);
	if (_fillRect) SDL_RenderFillRect(renderer.get(), &_rect);
	else SDL_RenderDrawRect(renderer.get(), &_rect);
}

void Entity::renderImGui() {
	ImGui::ColorEdit4("Color", &_color.Value.x);
	ImGui::DragInt4("Rect", &_rect.x, 1.0f);
	ImGui::Checkbox("Filled", &_fillRect);
}

Entity Entity::clone(const int id) {
	return Entity(id,
		_name,
		{ _rect.x, _rect.y, _rect.w, _rect.h },
		{ _color.Value.x, _color.Value.y, _color.Value.z, _color.Value.w }
	);
}

bool Entity::getRemoved() const {
	return _isRemoved;
}

void Entity::remove() {
	_isRemoved = true;
}
