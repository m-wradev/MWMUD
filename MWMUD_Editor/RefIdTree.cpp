#include "RefIdTree.h"

#include <fstream>

/*
 * ADL SERIALIZATION SPECIALIZATIONS
 */
void nlohmann::adl_serializer<std::list<GroupNode>>::to_json(json& j, const std::list<GroupNode>& list)
{
	for (GroupNode gNode : list)
	{
		json temp_j;
		::to_json(temp_j, gNode);
		j += temp_j;
	}
}

void nlohmann::adl_serializer<std::list<GroupNode>>::from_json(const json& j, std::list<GroupNode>& list)
{
	for (json arrItem : j)
		list.push_back(arrItem.get<GroupNode>());
}

void nlohmann::adl_serializer<std::list<ItemNode>>::to_json(json& j, const std::list<ItemNode>& list)
{
	for (ItemNode iNode : list)
	{
		json temp_j;
		::to_json(temp_j, iNode);
		j += temp_j;
	}
}

void nlohmann::adl_serializer<std::list<ItemNode>>::from_json(const json& j, std::list<ItemNode>& list)
{
	for (json arrItem : j)
		list.push_back(arrItem.get<ItemNode>());
}

/*
 * TREE NODE
 */
int TreeNode::nextId = 0;

void to_json(nlohmann::json& json, const TreeNode& node)
{
	json["NodeType"] = node.type;
	json["NodeId"] = node.nodeId;

	switch (node.type)
	{
		case NodeType::GROUP:
		{
			const GroupNode* p_gNode = static_cast<const GroupNode*>(&node);
			json["Label"] = p_gNode->label;
			json["Children"]["Groups"] = p_gNode->childGroups;
			json["Children"]["Items"] = p_gNode->childItems;
			break;
		}

		case NodeType::ITEM:
		{
			const ItemNode* p_iNode = static_cast<const ItemNode*>(&node);
			json["RefId"] = p_iNode->refId;
			break;
		}
	}
}

/*
 *	GROUP NODE
 */
void GroupNode::addNode(const TreeNode& tNode)
{
	switch (tNode.type)
	{
		case NodeType::GROUP:
		{
			const GroupNode gNode = *static_cast<const GroupNode*>(&tNode);
			childGroups.push_back(gNode);
			break;
		}

		case NodeType::ITEM:
		{
			const ItemNode iNode = *static_cast<const ItemNode*>(&tNode);
			childItems.push_back(iNode);
			break;
		}

		// TODO - Add case for NodeType::INVALID
	}
}

void from_json(const nlohmann::json& json, GroupNode& node)
{
	node.nodeId = json.at("NodeId").get<std::string>();
	node.label = json.at("Label").get<std::string>();
	node.childGroups = json.at("Children").at("Groups").get<std::list<GroupNode>>();
	node.childItems = json.at("Children").at("Items").get<std::list<ItemNode>>();
}

/*
 * ITEM NODE
 */

void from_json(const nlohmann::json& json, ItemNode& node)
{
	node.nodeId = json.at("NodeId").get<std::string>();
	node.refId = json.at("RefId").get<std::string>();
}

/*
 * REF ID TREE
 */
void RefIdTree::loadFromJSON(std::string filepath)
{
	std::ifstream file(filepath);
	nlohmann::json jsonData;
	file >> jsonData;
	root = jsonData.get<GroupNode>();
	file.close();
}

void RefIdTree::saveToJSON(std::string filepath)
{
	// Convert the RefIdTree to json
	nlohmann::json saveData = *this;

	// Overwrite the current file
	std::ofstream file(filepath, std::ofstream::trunc);
	file << saveData;
	file.close();
}

void to_json(nlohmann::json& json, const RefIdTree& tree)
{
	json = tree.root;
}

void from_json(const nlohmann::json& json, RefIdTree& tree)
{
	tree.root = json.get<GroupNode>();
}
