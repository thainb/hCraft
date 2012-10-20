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

#include "miscc.hpp"
#include "../server.hpp"
#include "../player.hpp"
#include <sstream>


namespace hCraft {
	namespace commands {
		
		const char*
		c_ping::get_name ()
			{ return "ping"; }
		
		const char*
		c_ping::get_summary ()
			{ return "Checks how much time it takes (in milliseconds) to ping and get a response from a player."; }
		
		int
		c_ping::get_usage_count ()
			{ return 3; }
		
		const char*
		c_ping::get_usage (int n)
		{
			static const char *usage[3] =
				{
					"/ping",
					"/ping <player>",
					"/ping [--help/--summary]",
				};
			
			return (n >= this->get_usage_count ()) ? "" : usage[n];
		}
		
		const char*
		c_ping::get_usage_help (int n)
		{
			static const char *help[3] =
				{
					"Displays the amount of time (in milliseconds) to both send and retreive"
					"a ping packet (keep alive) to/from the calling player.",
					
					"Measures ping time for <player> instead.",
					
					"Same as calling >/help< on >ping< (\"/help [-s] ping\")",
				};
			
			return (n >= this->get_usage_count ()) ? "" : help[n];
		}
		
		const char**
		c_ping::get_examples ()
		{
			static const char *examples[] =
				{
					"/ping",
					"/ping user1234",
					nullptr,
				};
			
			return examples;
		}
		
		const char**
		c_ping::get_permissions ()
		{
			static const char *perms[] =
				{
					"command.misc.ping",
					nullptr,
				};
			
			return perms;
		}
		
		
		
	//----
		
		void
		c_ping::execute (player *pl, command_reader& reader)
		{
			reader.add_option ("help", "h", false, false, false);
			reader.add_option ("summary", "s", false, false, false);
			if (!reader.parse_args (pl))
				return;
			
			if (reader.get_option ("help")->found)
				{ this->show_help (pl); return; }
			else if (reader.get_option ("summary")->found)
				{ this->show_summary (pl); return; }
			
			if (reader.arg_count () > 1)
				{ this->show_usage (pl); return; }
			
			if (reader.have_args ())
				{
					player *target = pl->get_server ().get_players ().find (reader.arg (0).c_str ());
					if (!target)
						{
							pl->message ("§c * §eThe player §c" + reader.arg (0) + " §eis not logged in§f.");
							return;
						}
					
					std::ostringstream ss;
					ss << "§a" << target->get_username () << "§e's ping§f: §c" << target->get_ping () << " §emilliseconds§f.";
					pl->message_nowrap (ss.str ());
					return;
				}
			
			std::ostringstream ss;
			ss << "§ePing§f: §c" << pl->get_ping () << " §emilliseconds§f.";
			pl->message_nowrap (ss.str ());
		}
	}
}

