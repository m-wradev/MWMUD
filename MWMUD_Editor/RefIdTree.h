#pragma once

#include "Dependencies/nlohmann/json.hpp"

#include <iostream>
#include <string>
#include <list>

struct GroupNode;
struct ItemNode;

// Specializations for conversions of lists to and from JSON
namespace nlohmann
{
	template <>
	struct adl_serializer<std::list<GroupNode>>
	{
		static void to_json(json& j, const std::list<GroupNode>& list);
		static void from_json(const json& j, std::list<GroupNode>& list);
	};

	template <>
	struct adl_serializer<std::list<ItemNode>>
	{
		static void to_json(json& j, const std::list<ItemNode>& list);
		static void from_json(const json& j, std::list<ItemNode>& list);
	};
};

enum class NodeType
{
	INVALID,// Invalid node: when a TreeNode is created directly. 
	GROUP,	// Non-leaf node
	ITEM	// Leaf nodes, contain reference IDs to game objects/data
};

// Allow enum to be serialized into json
NLOHMANN_JSON_SERIALIZE_ENUM
(
	NodeType,
	{
		{NodeType::INVALID, "INVALID"},
		{NodeType::GROUP, "GROUP"},
		{NodeType::ITEM, "ITEM"}
	}
)

// TODO - better system for node IDs
struct TreeNode
{
	static int nextId;

	std::string nodeId;
	NodeType type;

	TreeNode()
		: type(NodeType::INVALID)
	{}

	TreeNode(NodeType _type)
		: type(_type)
	{
		nodeId = std::to_string(TreeNode::nextId++);
	}

	virtual ~TreeNode() {}
};
void to_json(nlohmann::json& json, const TreeNode& node);


struct GroupNode : public TreeNode
{
	std::string label;
	std::list<GroupNode> childGroups;
	std::list<ItemNode> childItems;

	GroupNode()
		: TreeNode(NodeType::GROUP),
		label("Unnamed Group")
	{}

	GroupNode(std::string _label)
		: TreeNode(NodeType::GROUP),
		label(_label)
	{}

	// Add a node to one of the lists of children.
	// The correct list doesn't have to be specified.
	void addNode(const TreeNode& tNode);
};
void from_json(const nlohmann::json& json, GroupNode& node);

struct ItemNode : public TreeNode
{
	std::string refId;	// reference ID pointing to a game object or game data

	ItemNode()
		: TreeNode(NodeType::ITEM),
		refId("")
	{}

	ItemNode(std::string _refId)
		: TreeNode(NodeType::ITEM),
		refId(_refId)
	{}
};
void from_json(const nlohmann::json& json, ItemNode& node);

class RefIdTree
{
public:
	GroupNode root;

	// Load tree information from JSON file
	void loadFromJSON(std::string filepath);
	// Save tree information to JSON file
	void saveToJSON(std::string filepath);

	// Move a subtree or leaf node and make it the child of a different GroupNode
	//void moveNode(TreeNode* moving, GroupNode* to);
};
void to_json(nlohmann::json& json, const RefIdTree& tree);
void from_json(const nlohmann::json& json, RefIdTree& tree);
