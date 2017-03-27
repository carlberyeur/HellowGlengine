#pragma once

namespace CU
{
	class CJsonValue;
}

class CLevel;
class CScene;
class CLevelLoader;

struct SLayerData
{

};

struct STileData
{
	int gid;
	short posx, posy;
};

struct STileSet
{
	std::string texture;
	CU::Vector2ui imageSize;
	unsigned int firstgid, columns, tileCount;
};

using LoadObjectFunction = int(*)(CLevelLoader&, const CU::CJsonValue&);

class CLevelLoader
{
public:
	CLevelLoader(CLevel& aLevel, CScene& aScene);
	CLevelLoader(const CLevelLoader&) = delete;
	~CLevelLoader();

	bool LoadLevel(const std::string& aJsonPath);
	void RegisterLoadFunction(const std::string& aFunctionName, const LoadObjectFunction aLoadFunction);
	int CallLoadFunction(const std::string& aJsonObjectKey, const CU::CJsonValue& aJsonObjectValue);

	inline CLevel& GetLevel();
	inline CScene& GetScene();

	inline CU::GrowingArray<STileSet>& GetTileSets();
	inline CU::GrowingArray<STileData>& GetTileDatas();

private:
	std::map<std::string, LoadObjectFunction> myLoadFunctions;
	CU::GrowingArray<STileData> myTileDatas;
	CU::GrowingArray<STileSet> myTileSets;

	CLevel& myLevel;
	CScene& myScene;
};

inline CLevel& CLevelLoader::GetLevel()
{
	return myLevel;
}

inline CScene& CLevelLoader::GetScene()
{
	return myScene;
}

inline CU::GrowingArray<STileSet>& CLevelLoader::GetTileSets()
{
	return myTileSets;
}

inline CU::GrowingArray<STileData>& CLevelLoader::GetTileDatas()
{
	return myTileDatas;
}
