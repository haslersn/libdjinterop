/*
    This file is part of libdjinterop.

    libdjinterop is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libdjinterop is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with libdjinterop.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <djinterop/enginelibrary/database.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE database_test

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <ostream>
#include <string>

#define STRINGIFY(x) STRINGIFY_(x)
#define STRINGIFY_(x) #x

namespace el = djinterop::enginelibrary;
namespace fs = boost::filesystem;
using namespace std;

const std::string sample_path{STRINGIFY(TESTDATA_DIR) "/el1"};
const std::string fake_path{STRINGIFY(TESTDATA_DIR) "/elfake"};

static fs::path create_temp_dir()
{
    fs::path temp_dir{fs::temp_directory_path()};
    temp_dir /= fs::unique_path();
    if (!fs::create_directory(temp_dir))
    {
        throw std::runtime_error{"Failed to create tmp_dir"};
    }
    return temp_dir;
}

BOOST_AUTO_TEST_CASE (ctor__sample_path__constructed)
{
    // Simply try to construct the database on the provided path
    // Arrange/Act/Assert
    el::database{sample_path};
}

BOOST_AUTO_TEST_CASE (exists__valid_db__true)
{
    // Check that a valid database is reported as existing
    // Arrange/Act
    el::database db{sample_path};

    // Assert
    BOOST_CHECK_EQUAL(db.exists(), true);
}

BOOST_AUTO_TEST_CASE (exists__fake_db__false)
{
    // Check that a fake database is reported as not existing
    // Arrange/Act
    el::database db{fake_path};

    // Assert
    BOOST_CHECK_EQUAL(db.exists(), false);
}

BOOST_AUTO_TEST_CASE(is_supported__valid_db__valid_version)
{
    // Arrange
    el::database db{sample_path};

    // Act
    auto supported = db.is_supported();

    // Assert
    BOOST_CHECK_EQUAL(supported, true);
}

BOOST_AUTO_TEST_CASE(verify__valid_db__no_throw)
{
    // Arrange
    el::database db{sample_path};

    // Act/Assert
    db.verify();
}

BOOST_AUTO_TEST_CASE (information__valid_db__expected)
{
    // Assess correctness of values sourced from the 'Information' table
    // Arrange/Act
    el::database db{sample_path};
    
    // Assert
    BOOST_CHECK_EQUAL(db.directory_path(), sample_path);
    BOOST_CHECK_EQUAL(db.music_db_path(), sample_path + "/m.db");
    BOOST_CHECK_EQUAL(db.performance_db_path(), sample_path + "/p.db");
    
	BOOST_CHECK_EQUAL(db.uuid(), "e535b170-26ef-4f30-8cb2-5b9fa4c2a27f");
	BOOST_CHECK_EQUAL(db.version(), el::version_1_6_0);
}

BOOST_AUTO_TEST_CASE (create_database__version_1_6_0__creates_verified)
{
    // Arrange
    auto temp_dir = create_temp_dir();

    // Act
    auto db = el::create_database(temp_dir.string(), el::version_1_6_0);

    // Assert
    BOOST_CHECK_EQUAL(db.exists(), true);
    BOOST_CHECK_EQUAL(db.is_supported(), true);
    BOOST_CHECK_EQUAL(db.directory_path(), temp_dir.string());
    BOOST_CHECK_EQUAL(db.music_db_path(), (temp_dir / "m.db").string());
    BOOST_CHECK_EQUAL(db.performance_db_path(), (temp_dir / "p.db").string());
    BOOST_CHECK_EQUAL(db.version(), el::version_1_6_0);
    db.verify();
    fs::remove_all(temp_dir);
}

BOOST_AUTO_TEST_CASE (create_database__version_1_7_1__creates_verified)
{
    // Arrange
    auto temp_dir = create_temp_dir();

    // Act
    auto db = el::create_database(temp_dir.string(), el::version_1_7_1);

    // Assert
    BOOST_CHECK_EQUAL(db.exists(), true);
    BOOST_CHECK_EQUAL(db.is_supported(), true);
    BOOST_CHECK_EQUAL(db.directory_path(), temp_dir.string());
    BOOST_CHECK_EQUAL(db.music_db_path(), (temp_dir / "m.db").string());
    BOOST_CHECK_EQUAL(db.performance_db_path(), (temp_dir / "p.db").string());
    BOOST_CHECK_EQUAL(db.version(), el::version_1_7_1);
    db.verify();
    fs::remove_all(temp_dir);
}
