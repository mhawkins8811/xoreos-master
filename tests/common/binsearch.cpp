/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  Unit tests for our generic binary search.
 */

#include "gtest/gtest.h"

#include "src/common/util.h"
#include "src/common/binsearch.h"

typedef Common::BinSearchValue<uint8, uint8> TestBinSearch;

static const TestBinSearch kTestBinSearch[] = {
	{ 5, 23 },
	{ 6, 42 },
	{ 7, 60 }
};

GTEST_TEST(BinSearch, positive) {
	const TestBinSearch *entry = Common::binarySearch(kTestBinSearch, ARRAYSIZE(kTestBinSearch), (uint8) 6);

	ASSERT_NE(entry, static_cast<const TestBinSearch *>(0));
	EXPECT_EQ(entry->value, 42);
}

GTEST_TEST(BinSearch, negative) {
	const TestBinSearch *entry = Common::binarySearch(kTestBinSearch, ARRAYSIZE(kTestBinSearch), (uint8) 42);

	ASSERT_EQ(entry, static_cast<const TestBinSearch *>(0));
}
