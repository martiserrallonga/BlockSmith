#include "Scene.h"

#include "EngineGetter.h"
#include "LoggerGetter.h"

#include <format>
#include <optional>


namespace Const
{
	constexpr SDL_Rect kDefaultRect{ 500, 200, 100, 100 };
	constexpr ImColor kDefaultColor{ 120, 200, 120, 255 };
	constexpr SDL_Point kNewEntityOffset{ 50, 50 };
}

Scene::Scene() {
	_backgroundColor = ImColor(0.45f, 0.55f, 0.60f, 1.00f);

	initializeFrameBuffer();
}

void Scene::addEntity(Entity entity) {
	_pendingEntities.push(std::make_unique<Entity>(std::move(entity)));
}

void Scene::cloneEntity(const std::unique_ptr<Entity>& entity) {
	Entity clone = entity->clone(consumeId());
	clone.addPosition(Const::kNewEntityOffset);
	addEntity(clone);
}

void Scene::update() {
	std::erase_if(_entities, [](const auto& entity) { return entity->getRemoved(); });

	while (!_pendingEntities.empty()) {
		_entities.push_back(std::move(_pendingEntities.front()));
		_pendingEntities.pop();
	}

	for (const auto& entity : _entities) {
		entity->update();
	}
}

void Scene::render() const {
	const auto& renderer = Engine::Get().getRenderer();

	const ImGuiIO& io = ImGui::GetIO();
	SDL_RenderSetScale(renderer.get(), io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y); // TODO: Can be deleted

	renderer.setColor(_backgroundColor);
	SDL_RenderClear(renderer.get());

	for (const auto& entity : _entities) {
		entity->render();
	}
}

void Scene::renderInMenu() {
	ImGui::ColorEdit3("Background", &_backgroundColor.Value.x);

	SDL_Point size = Engine::Get().getWindow().getSize();
	ImGui::Text(std::format("Scene width and height: {} x {}", size.x, size.y).c_str());

	ImGui::Separator();
	if (!ImGui::CollapsingHeader("Entities", ImGuiTreeNodeFlags_DefaultOpen)) return;

	// TODO: Create a Color class to unify behavior
	const auto cloneColor = static_cast<ImVec4>(ImColor{ 25, 100, 25, 255 });
	const auto removeColor = static_cast<ImVec4>(ImColor{ 128, 30, 10, 255 });

	for (const auto& entity : _entities) {
		std::string nameId = entity->getNameId();

		const bool showEntity = ImGui::TreeNode(nameId.c_str());

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, cloneColor);
		ImGui::SmallButton("Clone");
		if (ImGui::IsItemClicked()) {
			Log::Debug(std::format("{} Clone Button Clicked", nameId));
			cloneEntity(entity);
		}
		ImGui::PopStyleColor();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, removeColor);
		ImGui::SmallButton("Remove");
		if (ImGui::IsItemClicked()) {
			Log::Debug(std::format("{} Remove Button Clicked", nameId));
			entity->remove();
		}
		ImGui::PopStyleColor();

		if (showEntity) {
			entity->renderInMenu();
			ImGui::TreePop();
		}
	}
}

void Scene::onWindowShown(int width, int height) {
	resetFrameBuffer(width, height);
}

void Scene::onWindowResized(int width, int height) {
	resetFrameBuffer(width, height);
}

void Scene::resetFrameBuffer(int width, int height) {
	_entities.clear();
	_uniqueId = 0;

	int entitySize = std::min(width / 16, height / 16);
	int sceneSize = entitySize * 16;
	SDL_Point sceneOffset{ (width - sceneSize) / 2 , (height - sceneSize) / 2 };

	for (int i = 0; i < _frameBuffer.size(); ++i) {
		SDL_Point point{ i % 16 , i / 16 };
		SDL_Point position{ point.x * entitySize + sceneOffset.x, point.y * entitySize + sceneOffset.y };
		addEntity(Entity(consumeId(), "Pixel", { position.x, position.y, entitySize, entitySize }, _frameBuffer.at(i)));
	}
}

void Scene::initializeFrameBuffer() {
	ImColor Void = { 255,255,255,0 };
	ImColor Black = { 0,0,0,255 };
	ImColor White = { 255,255,255,255 };
	ImColor Green = { 28,148,134,255 };
	ImColor Red = { 206,52,52,255 };

	_frameBuffer = {
		Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,
		Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Black,Black,Void,Void,
		Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Black,Black,Green,Green,Black,Void,
		Void,Void,Void,Void,Void,Void,Void,Void,Black,Black,Green,Green,Green,Green,Black,Void,
		Void,Void,Void,Void,Void,Void,Void,Black,Green,Green,Black,Green,Black,Black,Void,Void,
		Void,Void,Void,Black,Black,Black,Black,Green,Black,Black,Black,Green,Black,Void,Void,Void,
		Void,Void,Black,Red,Red,Red,Red,Black,Black,Black,Green,Black,Void,Void,Void,Void,
		Void,Black,Red,Red,Red,Red,Red,Red,Black,Green,Black,Black,Void,Void,Void,Void,
		Void,Black,Red,Red,Red,Red,Red,Black,Red,Red,Red,Red,Black,Void,Void,Void,
		Void,Black,Red,White,Red,Red,Black,Red,Red,Red,Red,Red,Red,Black,Void,Void,
		Void,Black,Red,Red,White,White,Black,Red,Red,Red,Red,Red,Red,Black,Void,Void,
		Void,Void,Black,Red,Red,Red,Black,Red,White,Red,Red,Red,Red,Black,Void,Void,
		Void,Void,Void,Black,Black,Black,Black,Red,Red,White,White,Red,Red,Black,Void,Void,
		Void,Void,Void,Void,Void,Void,Void,Black,Red,Red,Red,Red,Black,Void,Void,Void,
		Void,Void,Void,Void,Void,Void,Void,Void,Black,Black,Black,Black,Void,Void,Void,Void,
		Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,Void,
	};
}

int Scene::consumeId() {
	return _uniqueId++;
}