#include "pch.h"

enum AssetType {
	SHADER
};

class Asset {
public:
	AssetType m_AssetType;
	std::string m_Path;
	void save();
	void load();
	std::vector<char> getTypeShort();
	std::vector<char> getBlob();
	std::string getDescription();
};

class AssetManager {
public:
	static std::vector<Asset*> m_Assets;
	static void loadFromFolder();
};