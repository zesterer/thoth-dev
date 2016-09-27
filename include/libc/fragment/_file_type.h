/*
* 	filename	: _file_type.h
* 	component	: libc
* 	description	: The FILE type
*
* 	This file is part of Thoth.
*
* 	Thoth is free software: you can redistribute it and/or modify
* 	it under the terms of the GNU General Public License as published by
* 	the Free Software Foundation, either version 3 of the License, or
* 	(at your option) any later version.
*
* 	Thoth is distributed in the hope that it will be useful,
* 	but WITHOUT ANY WARRANTY; without even the implied warranty of
* 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* 	GNU General Public License for more details.
*
* 	You should have received a copy of the GNU General Public License
* 	along with Thoth.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __FILE_TYPE_H
#define __FILE_TYPE_H 1

/* FILE type */

typedef struct _file_handle
{
	long file_handle;
}_file_handle;

#endif
