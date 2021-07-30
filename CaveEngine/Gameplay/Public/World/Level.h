/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <unordered_map>

#include "Engine.h"
#include "CoreTypes.h"
#include "Object/Object.h"

namespace cave
{
	class World;
	class GameObject;
	class Tag;

	class Level final : public Object
	{
	public:
		friend class GameObject;

		Level();
		Level(std::string& name);
		Level(const char* name);
		Level(const Level&) = delete;
		Level(Level&&) = delete;

		~Level();
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

		void AddGameObject(GameObject& gameObject);
		void AddGameObjects(std::vector<GameObject*>& gameObjects);

		void DefferedRemoveGameObject(GameObject& gameObject);
		void DefferedRemoveGameObjects(std::vector<GameObject*>& gameObjects);

		GameObject* FindGameObjectByName(std::string& name);
		GameObject* FindGameObjectByName(const char* name);
		std::vector<GameObject*>&& FindGameObjectsByName(std::string& name);
		std::vector<GameObject*>&& FindGameObjectsByName(const char* name);

		GameObject* FindGameObjectByTag(std::string& tag);
		GameObject* FindGameObjectByTag(const char* tag);
		std::vector<GameObject*>&& FindGameObjectsByTag(std::string& tag);
		std::vector<GameObject*>&& FindGameObjectsByTag(const char* tag);

		void InitializeGameObjectsInLevel();
		void UpdateGameObjectsInLevel();
		void FixedUpdateGameObjectsInLevel();

#ifdef CAVE_BUILD_DEBUG
		void PrintGameObjects();
#endif // CAVE_BUILD_DEBUG

	private:
		void addActiveGameObject(GameObject& gameObject);
		void removeActiveGameObject(GameObject& gameObject);

		void addTagGameObject(GameObject& gameObject);
		void removeTagGameObject(GameObject& gameObject);

		void removeGameObjects();

		bool findGameObject(GameObject& gameObject);
		bool findActiveGameObject(GameObject& gameObject);

	private:
		std::unordered_multimap<std::string, GameObject*> mAllGameObjects;
		std::unordered_multimap<uint32_t, GameObject*> mActiveGameObjects;
		std::unordered_multimap<Tag*, GameObject*> mTagGameObjects;

		std::vector<GameObject*> mDeferredRemoveGameObjects;

		World* mOwner;
	};

#ifdef CAVE_BUILD_DEBUG
	namespace LevelTest
	{
		void Test();
		Level* CreateTmpLevel();
	}
#endif //CAVE_BUILD_DEBUG
}
