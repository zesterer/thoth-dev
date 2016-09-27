#ifndef THOTH_KERNEL_THOTH_VFS_VFS
#define THOTH_KERNEL_THOTH_VFS_VFS

#include "stdint.h"

#define THOTH_VFS_NODE_MAX 2048
#define THOTH_VFS_NODE_MAXNAMELEN 256
#define THOTH_VFS_NODE_MAXCHILDNUM 64

// Node Types
enum thoth_vfs_node_type
{
	THOTH_VFS_FILE		= 0,
	THOTH_VFS_DIRECTORY	= 1,
};

// A File Handler
typedef uint32_t THOTH_VFS_NODE_ID;

// Initiate
int thoth_vfs_init();

// Locate
THOTH_VFS_NODE_ID thoth_vfs_get_root();

// Action
THOTH_VFS_NODE_ID thoth_vfs_create_node(const char* name, const THOTH_VFS_NODE_ID parent, uint8_t type);
int thoth_vfs_name_node(THOTH_VFS_NODE_ID id, const char* name);
int thoth_vfs_delete_node(THOTH_VFS_NODE_ID id);

// Inquiry
int thoth_vfs_get_name(THOTH_VFS_NODE_ID id, char* name);
uint8_t thoth_vfs_get_type(THOTH_VFS_NODE_ID id);
THOTH_VFS_NODE_ID* thoth_vfs_get_children(THOTH_VFS_NODE_ID id);

// Display
void thoth_vfs_display();

#endif
