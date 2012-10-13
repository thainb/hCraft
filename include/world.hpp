/* 
 * hCraft - A custom Minecraft server.
 * Copyright (C) 2012	Jacob Zhitomirsky
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _hCraft__WORLD_H_
#define _hCraft__WORLD_H_

#include "map.hpp"
#include "playerlist.hpp"


namespace hCraft {
	
	class player;
	
	
	/* 
	 * Represents a world.
	 */
	class world
	{
		char name[33]; // 32 chars max
		map *mp;
		playerlist *players;
		
	public:
		inline const char* get_name () { return this->name; }
		inline map& get_map () { return *this->mp; }
		inline playerlist& get_players () { return *this->players; }
		
	public:
		/* 
		 * Constructs a new empty world with the given name.
		 */
		world (const char *name, map_generator *gen, map_provider *prov);
		
		/* 
		 * Class destructor.
		 */
		~world ();
	};
}

#endif

