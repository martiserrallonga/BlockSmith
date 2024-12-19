#pragma once
#include "Entity.h"
#include <memory>
#include <queue>
#include <vector>


class Scene
{
public:
	Scene();

	void addEntity(Entity entity);

	void cloneEntity(const std::unique_ptr<Entity>& entity);

	void update();
	void render() const;
	void renderImGui();

	void onWindowShown(int width, int height);
	void onWindowResized(int width, int height);

private:
	int consumeId();

	ImColor _backgroundColor;

	int _uniqueId = 0;
	std::vector<std::unique_ptr<Entity>> _entities;
	std::queue<std::unique_ptr<Entity>> _pendingEntities;
};
