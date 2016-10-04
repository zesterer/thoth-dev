#include "thoth/vfs/vfs.h"

#include "libc/string.h"
#include "libc/stdio.h"
#include "libc/stdlib.h"

#include "stddef.h"

#include "thoth/io.h"

typedef struct thoth_vfs_node
{
	THOTH_VFS_NODE_ID id;
	char name[THOTH_VFS_NODE_MAXNAMELEN];
	uint8_t type;
	struct thoth_vfs_node* parent;
	struct thoth_vfs_node* children[THOTH_VFS_NODE_MAXCHILDNUM];
} thoth_vfs_node;

// Static methods
static void thoth_vfs_init_node(thoth_vfs_node* node, enum thoth_vfs_node_type type);
static void thoth_vfs_display_node(thoth_vfs_node* node, int depth);
static thoth_vfs_node* thoth_vfs_find_node(THOTH_VFS_NODE_ID id);

// The static root node
thoth_vfs_node root;

// The static node table
thoth_vfs_node* node_table[THOTH_VFS_NODE_MAX];

// The node counter to make sure nodes have unique names, starting at 1 (0 is NULL)
THOTH_VFS_NODE_ID id_counter = 1;

static void thoth_vfs_init_node(thoth_vfs_node* node, enum thoth_vfs_node_type type)
{
	node->id = id_counter;
	id_counter ++;

	for (int i = 0; i < THOTH_VFS_NODE_MAXNAMELEN; i ++)
		node->name[i] = '\0';

	node->type = type;

	node->parent = NULL;

	for (int i = 0; i < THOTH_VFS_NODE_MAXCHILDNUM; i ++)
		node->children[i] = NULL;

	// Place in table
	for (int i = 0; i < THOTH_VFS_NODE_MAX; i ++)
	{
		if (node_table[i] == NULL)
		{
			node_table[i] = node;
			break;
		}
	}
}

/* Initiate */

int thoth_vfs_init()
{
	// Zero the node table
	for (int i = 0; i < THOTH_VFS_NODE_MAX; i ++)
		node_table[i] = NULL;

	thoth_vfs_init_node(&root, THOTH_VFS_DIRECTORY);
	thoth_vfs_name_node(thoth_vfs_get_root(), "root");

	thoth_io_check("Created VFS root directory", STATUS_SUCCESS);

	return 0;
}

/* Locate */

THOTH_VFS_NODE_ID thoth_vfs_get_root()
{
	return root.id;
}

static thoth_vfs_node* thoth_vfs_find_node(THOTH_VFS_NODE_ID id)
{
	for (int i = 0; i < THOTH_VFS_NODE_MAX; i ++)
	{
		if (node_table[i]->id == id)
			return node_table[i];
	}

	return NULL;
}

/* Action */

THOTH_VFS_NODE_ID thoth_vfs_create_node(const char* name, const THOTH_VFS_NODE_ID parent, uint8_t type)
{
	thoth_vfs_node* new_node = (thoth_vfs_node*)malloc(sizeof(thoth_vfs_node));
	thoth_vfs_node* parent_node = thoth_vfs_find_node(parent);

	printf("$F3INFO$FF : Creating node '%s'\n", name);

	if (new_node == NULL || parent_node == NULL || parent_node->type != THOTH_VFS_DIRECTORY)
		return 0;

	thoth_vfs_init_node(new_node, (thoth_vfs_node_type)type);

	new_node->parent = parent_node;

	for (int i = 0; i < THOTH_VFS_NODE_MAXCHILDNUM; i ++)
	{
		if (parent_node->children[i] == NULL)
		{
			parent_node->children[i] = new_node;
			break;
		}
	}

	strcpy(new_node->name, name);

	return new_node->id;
}

int thoth_vfs_name_node(THOTH_VFS_NODE_ID id, const char* name)
{
	thoth_vfs_node* node = thoth_vfs_find_node(id);

	if (node == NULL)
		return 1;

	strcpy(node->name, name);

	return 0;
}

int thoth_vfs_delete_node(THOTH_VFS_NODE_ID id)
{
	thoth_vfs_node* node = NULL;

	for (int i = 0; i < THOTH_VFS_NODE_MAX; i ++)
	{
		if (node_table[i]->id == id)
		{
			node = node_table[i];
			node_table[i] = NULL;
		}
	}

	if (node == NULL)
		return 1;

	printf("$F3INFO$FF : Deleting node '%s'\n", node->name);

	if (node->parent == NULL)
		return 2;

	for (int i = 0; i < THOTH_VFS_NODE_MAXCHILDNUM; i ++)
	{
		if (node->parent->children[i] == node)
		{
			node->parent->children[i] = NULL;
			break;
		}
	}

	for (int i = 0; i < THOTH_VFS_NODE_MAXCHILDNUM; i ++)
	{
		if (node->children[i] != NULL)
			thoth_vfs_delete_node(node->children[i]->id);
	}

	free(node);

	return 0;
}

/* Display */

static void thoth_vfs_display_node(thoth_vfs_node* node, int depth)
{
	for (int i = 0; i < depth; i ++)
		puts("|  ");

	if (depth > 8)
	{
		puts("$F4Max depth reached!$FF\n");
		return;
	}

	if (node->type == THOTH_VFS_FILE)
	{
		puts("$F2FILE$FF ");
		puts(node->name);
		putchar('\n');
	}
	else if (node->type == THOTH_VFS_DIRECTORY)
	{
		puts("$F3DIR$FF ");
		puts(node->name);
		putchar('\n');

		for (int i = 0; i < THOTH_VFS_NODE_MAXCHILDNUM; i ++)
		{
			if (node->children[i] != NULL)
				thoth_vfs_display_node(node->children[i], depth + 1);
		}
	}
}

void thoth_vfs_display()
{
	puts("$F5--< Virtual Filesystem display >--$FF\n");
	thoth_vfs_display_node(&root, 0);
	puts("$F5--</Virtual Filesystem display >--$FF\n");
}
