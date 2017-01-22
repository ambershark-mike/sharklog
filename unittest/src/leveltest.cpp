////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016-17, by Ambershark, LLC.
//
// Distributed under the L-GPL license.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You sould have received a copy of the GNU Lesser General Public
// License along with this program.  If not see
// <http://www.gnu.org/licenses>.
//
// This notice must remain in the source code and any derived source.
//
////////////////////////////////////////////////////////////////////////////////

#include "leveltest.h"
#include "level.h"

using namespace sharklog;
using namespace std;

TEST_F(LevelTest, FatalCreationWorks)
{
    ASSERT_EQ(Level::FATAL, Level::fatal().level());
}

TEST_F(LevelTest, ErrorCreationWorks)
{
    ASSERT_EQ(Level::ERROR, Level::error().level());
}

TEST_F(LevelTest, WarnCreationWorks)
{
    ASSERT_EQ(Level::WARN, Level::warn().level());
}

TEST_F(LevelTest, InfoCreationWorks)
{
    ASSERT_EQ(Level::INFO, Level::info().level());
}

TEST_F(LevelTest, TraceCreationWorks)
{
    ASSERT_EQ(Level::TRACE, Level::trace().level());
}

TEST_F(LevelTest, DebugCreationWorks)
{
    ASSERT_EQ(Level::DEBUG, Level::debug().level());
}

TEST_F(LevelTest, FuncTraceCreationWorks)
{
    ASSERT_EQ(Level::FUNCTRACE, Level::functrace().level());
}

TEST_F(LevelTest, NamesResolveProperly)
{
    ASSERT_STREQ("FATAL", Level::fatal().name().c_str());
    ASSERT_STREQ("ERROR", Level::error().name().c_str());
    ASSERT_STREQ("WARN", Level::warn().name().c_str());
    ASSERT_STREQ("INFO", Level::info().name().c_str());
    ASSERT_STREQ("TRACE", Level::trace().name().c_str());
    ASSERT_STREQ("DEBUG", Level::debug().name().c_str());
    ASSERT_STREQ("FUNC", Level::functrace().name().c_str());
    ASSERT_STREQ("ALL", Level::all().name().c_str());
    ASSERT_STREQ("NONE", Level().name().c_str());
}

TEST_F(LevelTest, HasLevelWorksOnSameLevel)
{
    ASSERT_TRUE(Level::fatal().hasLevel(Level::fatal()));
}

TEST_F(LevelTest, HasLowerLevel)
{
    ASSERT_TRUE(Level::warn().hasLevel(Level::fatal()));
    ASSERT_TRUE(Level::warn().hasLevel(Level::error()));
}

TEST_F(LevelTest, HasHigherLevelFails)
{
    ASSERT_FALSE(Level::warn().hasLevel(Level::info()));
}

TEST_F(LevelTest, HasFatalWorks)
{
    ASSERT_TRUE(Level::fatal().hasFatal());
}

TEST_F(LevelTest, HasErrorWorks)
{
    ASSERT_TRUE(Level::error().hasError());
}

TEST_F(LevelTest, HasWarnWorks)
{
    ASSERT_TRUE(Level::warn().hasWarn());
}

TEST_F(LevelTest, HasInfoWorks)
{
    ASSERT_TRUE(Level::info().hasInfo());
}

TEST_F(LevelTest, HasTraceWorks)
{
    ASSERT_TRUE(Level::trace().hasTrace());
}

TEST_F(LevelTest, HasDebugWorks)
{
    ASSERT_TRUE(Level::debug().hasDebug());
}

TEST_F(LevelTest, HasFuncTraceWorks)
{
    ASSERT_TRUE(Level::functrace().hasFuncTrace());
}

TEST_F(LevelTest, EqualsWorks)
{
    ASSERT_TRUE(Level::debug() == Level::debug());
}

TEST_F(LevelTest, NotEqualsWorks)
{
    ASSERT_FALSE(Level::debug() != Level::debug());
    ASSERT_TRUE(Level::info() != Level::error());
}

TEST_F(LevelTest, LessThanWorks)
{
    ASSERT_TRUE(Level::fatal() < Level::error());
}

TEST_F(LevelTest, GreaterThanWorks)
{
    ASSERT_TRUE(Level::error() > Level::fatal());
}

TEST_F(LevelTest, LessThanEqualsWorks)
{
    ASSERT_TRUE(Level::error() <= Level::info());
    ASSERT_TRUE(Level::error() <= Level::error());
    ASSERT_FALSE(Level::error() <= Level::fatal());
}

TEST_F(LevelTest, GreaterThanEqualsWorks)
{
    ASSERT_TRUE(Level::error() >= Level::fatal());
    ASSERT_TRUE(Level::error() >= Level::error());
    ASSERT_FALSE(Level::error() >= Level::warn());
}

TEST_F(LevelTest, HasAllWorks)
{
    ASSERT_TRUE(Level::all().hasAll());
}

TEST_F(LevelTest, AllIncludesEverything)
{
    auto all = Level::all();
    ASSERT_TRUE(all.hasFuncTrace());
    ASSERT_TRUE(all.hasDebug());
    ASSERT_TRUE(all.hasTrace());
    ASSERT_TRUE(all.hasInfo());
    ASSERT_TRUE(all.hasWarn());
    ASSERT_TRUE(all.hasError());
    ASSERT_TRUE(all.hasFatal());
    ASSERT_TRUE(all.hasNone());
}

TEST_F(LevelTest, HasNoneWorks)
{
    ASSERT_TRUE(Level().hasNone());
}

TEST_F(LevelTest, NamedConstructorWorks)
{
	Level l("debug");
	ASSERT_TRUE(l == Level::debug());
}

TEST_F(LevelTest, BadNameToConstructorIsNone)
{
	Level none;
	ASSERT_TRUE(Level::name("random") == none);
}

TEST_F(LevelTest, StaticNameCreationWorks)
{
	ASSERT_TRUE(Level::name("info") == Level::info());
}

TEST_F(LevelTest, FatalNameWorks)
{
	ASSERT_TRUE(Level("fatal") == Level::fatal());
}

TEST_F(LevelTest, ErrorNameWorks)
{
	ASSERT_TRUE(Level("error") == Level::error());
}

TEST_F(LevelTest, WarnNameWorks)
{
	ASSERT_TRUE(Level("warn") == Level::warn());
}

TEST_F(LevelTest, InfoNameWorks)
{
	ASSERT_TRUE(Level("info") == Level::info());
}

TEST_F(LevelTest, TraceNameWorks)
{
	ASSERT_TRUE(Level("trace") == Level::trace());
}

TEST_F(LevelTest, DebugNameWorks)
{
	ASSERT_TRUE(Level("debug") == Level::debug());
}

TEST_F(LevelTest, FuncNameWorks)
{
	ASSERT_TRUE(Level("func") == Level::functrace());
}

TEST_F(LevelTest, AllNameWorks)
{
	ASSERT_TRUE(Level("all") == Level::all());
}
