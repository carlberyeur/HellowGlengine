#pragma once

namespace CU
{
	class CJsonValue;
}

class CLevelLoader;

namespace TiledLoader
{
	int LoadRoot(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject);
	int LoadLayers(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject);
	int LoadTileLayer(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject);
	int LoadTileSets(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject);
	int LoadObjects(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject);
};
