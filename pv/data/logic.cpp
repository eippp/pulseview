/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include <cassert>

#include "logic.hpp"
#include "logicsnapshot.hpp"

using std::deque;
using std::max;
using std::shared_ptr;

namespace pv {
namespace data {

Logic::Logic(unsigned int num_channels) :
	SignalData(),
	num_channels_(num_channels)
{
	assert(num_channels_ > 0);
}

int Logic::get_num_channels() const
{
	return num_channels_;
}

void Logic::push_snapshot(
	shared_ptr<LogicSnapshot> &snapshot)
{
	snapshots_.push_front(snapshot);
}

const deque< shared_ptr<LogicSnapshot> >& Logic::logic_snapshots() const
{
	return snapshots_;
}

void Logic::clear()
{
	snapshots_.clear();
}

uint64_t Logic::get_max_sample_count() const
{
	uint64_t l = 0;
	for (std::shared_ptr<LogicSnapshot> s : snapshots_) {
		assert(s);
		l = max(l, s->get_sample_count());
	}
	return l;
}

} // namespace data
} // namespace pv
