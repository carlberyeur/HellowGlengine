#include "stdafx.h"
#include "TiledLoader.h"

#include "LevelLoader.h"
#include "Level.h"
#include "Scene.h"

#include "../CommonUtilities/JsonValue.h"
#include "../CommonUtilities/JsonIterator.h"
#include "../CommonUtilities/base64.h"

namespace TiledLoader
{
	int LoadRoot(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject)
	{
		for (CU::CJsonIterator it = aJsonObject.Begin(); it != aJsonObject.End(); ++it)
		{
			aLevelLoader.CallLoadFunction(it.First(), it.Second());
		}

		return 0;
	}
	
	int LoadLayers(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject)
	{
		for (int i = 0; i < aJsonObject.Size(); ++i)
		{
			CU::CJsonValue layer = aJsonObject[i];
			aLevelLoader.CallLoadFunction(layer["type"].GetString(), layer);
		}

		return 0;
	}

	int LoadTileLayer(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject)
	{
		const std::string& rawData = aJsonObject["data"].GetString();
		std::string decodedData = CU::base64_decode(rawData);

		CU::GrowingArray<STileData>& tileDatas = aLevelLoader.GetTileDatas();
		if (tileDatas.IsInitialized())
		{
			return -1;
		}
		tileDatas.Init(decodedData.size() / 4);

		int layerWidth = aJsonObject["width"].GetInt();
		int layerHeight = aJsonObject["height"].GetInt();

		int tileIndex = 0;
		for (int x = 0; x < layerWidth; ++x)
		{
			for (int y = 0; y < layerHeight; ++y)
			{
				unsigned int gid = decodedData[tileIndex] | decodedData[tileIndex + 1] << 8 | decodedData[tileIndex + 2] << 16 | decodedData[tileIndex + 3] << 24;
				tileIndex += 4;

				const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
				const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
				const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;

				//bool flipped_horizontally = (gid & FLIPPED_HORIZONTALLY_FLAG) > 0;
				//bool flipped_vertically = (gid & FLIPPED_VERTICALLY_FLAG) > 0;
				//bool flipped_diagonally = (gid & FLIPPED_DIAGONALLY_FLAG) > 0;

				gid &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);


				if (gid > 0)
				{
					STileData tile;
					tile.gid = gid;
					tile.posx = x;
					tile.posy = y;

					tileDatas.Add(tile);
				}
			}
		}

		return 0;
	}
	
	int LoadTileSets(CLevelLoader& aLevelLoader, const CU::CJsonValue& aJsonObject)
	{
		CU::GrowingArray<STileSet>& tileSets = aLevelLoader.GetTileSets();
		tileSets.Init(aJsonObject.Size());

		CU::CJsonValue jsonTileSet = aJsonObject[0];
		STileSet tileSet;
		tileSet.texture = jsonTileSet["image"].GetString();
		tileSet.imageSize.Set(jsonTileSet["imagewidth"].GetUInt(), jsonTileSet["imageheight"].GetUInt());
		tileSet.tileSize.Set(jsonTileSet["tilewidth"].GetUInt(), jsonTileSet["tileheight"].GetUInt());
		tileSet.firstgid = jsonTileSet["firstgid"].GetUInt();
		tileSet.columns = jsonTileSet["columns"].GetUInt();
		tileSet.tileCount = jsonTileSet["tilecount"].GetUInt();

		tileSets.Add(tileSet);

		return 0;
	}

	int LoadObjects(CLevelLoader& /*aLevelLoader*/, const CU::CJsonValue& /*aJsonObject*/)
	{
		return 0;
	}
}
