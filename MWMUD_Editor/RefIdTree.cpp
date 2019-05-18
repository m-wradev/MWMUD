#include "RefIdTree.h"

/*
 * TREE NODE
 */
int TreeNode::nextId = 0;

void to_json(nlohmann::json& json, const TreeNode* node)
{
	json["NodeType"] = node->type;
	json["NodeId"] = node->nodeId;

	switch (node->type)
	{
		case NodeType::GROUP:
		{
			const GroupNode* gNode = static_cast<const GroupNode*>(node);
			json["Label"] = gNode->label;
			json["Children"] = gNode->children;
			break;
		}

		case NodeType::ITEM:
		{
			const ItemNode* iNode = static_cast<const ItemNode*>(node);
			json["RefId"] = iNode->refId;
			break;
		}
	}
}

void from_json(const nlohmann::json& json, TreeNode* node)
{
	json.at("NodeType").get_to(node->type);
	json.at("NodeId").get_to(node->nodeId);

	switch (node->type)
	{
		case NodeType::GROUP:
		{
			GroupNode* gNode = static_cast<GroupNode*>(node);
			json.at("Label").get_to(gNode->label);
			json.at("Children").get_to(gNode->children);
			break;
		}

		case NodeType::ITEM:
		{
			ItemNode* iNode = static_cast<ItemNode*>(node);
			json.at("RefId").get_to(iNode->refId);
			break;
		}
	}
}

/*
 *	GROUP NODE
 */
GroupNode::~GroupNode()
{
	for (TreeNode* node : children)
		delete node;
}

/*
 * ITEM NODE
 */

/*
 * REF ID TREE
 */
RefIdTree::RefIdTree()
{
	root = new GroupNode;
}

RefIdTree::~RefIdTree()
{
	delete root;
}

void RefIdTree::save()
{
	for (TreeNode* node : root->children)
	{
		if (node->type == NodeType::GROUP)
		{

		}
		else
		{

		}
	}
}

void to_json(nlohmann::json& json, const RefIdTree& tree)
{
	json["ROOT"] = tree.root;
}

void from_json(const nlohmann::json& json, RefIdTree& tree)
{
	json.at("ROOT").get_to(tree.root);
}
