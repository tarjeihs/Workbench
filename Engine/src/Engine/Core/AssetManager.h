#pragma once

#include <unordered_map>

namespace Workbench
{
	template<typename T>
	class AssetManager
	{
	public:
		//void LoadAsset();
		//T& GetAsset();
	private:
		template<typename T>
		struct Asset
		{
			T Asset;
		};
	private:
		std::unordered_map<std::string, Asset> m_Assets;
	};
}
