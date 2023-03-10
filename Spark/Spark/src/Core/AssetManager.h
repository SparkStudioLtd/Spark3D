#include "pch.h"
#include "Core/JSON.h"


enum AssetType {
	FONT
};

struct LoadedAsset {
public:
	std::string description;
	std::vector<char> blob;
	char type[4];
	int version;
};

class Asset {
public:
	std::any m_Handle;
	AssetType m_AssetType;
	std::string m_ToSavePath;
	std::string m_Name;
	std::string m_AssetFilePath;
	nlohmann::json m_AssetInfo;
	LoadedAsset m_LoadedAsset;
	AssetType m_Type;
	void save();
	void load();
	void typeLoad();
	std::vector<char> getTypeShort();
	std::vector<char> getBlob();
	AssetType getEnum(std::vector<char> type);
	std::string getDescription();
};

class AssetManager {
public:
	static std::vector<Asset*> m_Assets;
	static void loadFromFolder();
	static Asset* getAsset(std::string m_Name);
};