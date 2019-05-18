#pragma once

#include "Dependencies/nlohmann/json.hpp"

#include <iostream>
#include <string>
#include <forward_list>

struct TreeNode;
struct GroupNode;
struct ItemNode;

enum class NodeType
{
	GROUP,	// Non-leaf node
	ITEM	// Leaf nodes, contain reference IDs to game objects/data
};

// Allow enum to be serialized into json
NLOHMANN_JSON_SERIALIZE_ENUM
(
	NodeType,
	{
		{NodeType::GROUP, "GROUP"},
		{NodeType::ITEM, "ITEM"}
	}
)

struct TreeNode
{
	static int nextId;


	std::string nodeId;
	NodeType type;

	TreeNode()
		: type(NodeType::GROUP)
	{
		nodeId = std::to_string(TreeNode::nextId++);
		printDebug();
	}

	TreeNode(NodeType _type)
		: type(_type)
	{
		nodeId = std::to_string(TreeNode::nextId++);
		printDebug();
	}

	void printDebug()
	{
		std::cout << "Created node: ID = " + nodeId + ", ";
		std::string typestr = (type == NodeType::GROUP) ? "GROUP" : "ITEM";
		std::cout << "type = " + typestr << std::endl;
	}

	virtual ~TreeNode() {}
};
void to_json(nlohmann::json& json, const TreeNode* node);
void from_json(const nlohmann::json& json, TreeNode* node);

struct GroupNode : public TreeNode
{
	std::string label;
	std::vector<TreeNode*> children;

	GroupNode()
		: TreeNode(NodeType::GROUP),
		label("Unnamed Group")
	{}

	GroupNode(std::string _label)
		: TreeNode(NodeType::GROUP),
		label(_label)
	{}

	~GroupNode();
};

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

class RefIdTree
{
public:
	GroupNode* root;

	RefIdTree();
	~RefIdTree();

	void save();

	// Move a subtree or leaf node and make it the child of a different GroupNode
	//void moveNode(TreeNode* moving, GroupNode* to);
};
void to_json(nlohmann::json& json, const RefIdTree& tree);
void from_json(const nlohmann::json& json, RefIdTree& tree);
