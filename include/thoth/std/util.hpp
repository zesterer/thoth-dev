/*
* 	filename	: util.hpp
* 	component	: thoth
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

// Header guard
#ifndef _THOTH_STD_UTIL_HPP
#define _THOTH_STD_UTIL_HPP 1

namespace Thoth
{
	enum { STATUS_SUCCESS = 0, };

	/* Status type */

	struct Status
	{
		int status;

		Status(int status)
		{
			this->status = status;
		}

		bool getSuccessful() { return this->status == STATUS_SUCCESS; }
		int getError() { return this->status; }
	};

	/* Result type */

	template <typename T>
	struct Result : public Status
	{
		T value;

		Result(T value, int status) : Status(status)
		{
			this->value = value;
		}

		T getValue() { return this->value; }
	};
}

// Header guard
#endif