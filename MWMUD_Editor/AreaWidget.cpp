#include "AreaWidget.h"

#include <set>

static enum NodeType
{
	GROUP,
	ITEM
};

static struct TreeNode
{
	int val;						// -1 if node not a leaf node
	std::string label;				// only if the node isn't a leaf node
	std::set<TreeNode*> children;	// only if the node isn't a leaf node

	~TreeNode()
	{
		for (TreeNode* node : children)
			delete node;

		children.clear();
	}
};

static struct Tree
{
	TreeNode* root;

	Tree()
	{
		root = new TreeNode();

		root->val = -1;
		root->label = "Root";
	}

	~Tree()
	{
		delete root;
	}
};

AreaWidget::AreaWidget()
{

}

void AreaWidget::draw()
{

}