#include "pch.h"

TEST(TestCapImport, TestNoFatalFailConstructor) {
	EXPECT_NO_FATAL_FAILURE(CapImport ci(new JsonDB("./db.json"), new ColorPoint()));
}

TEST(TestCapImport, TestNoThrowConstructor) {

	EXPECT_NO_THROW(CapImport ci(new JsonDB("./db.json"), new ColorPoint()));
}

TEST(TestCapImport, TestNo) {
	CapImport ci = CapImport(new JsonDB("./db.json"), new ColorPoint::ColorPicker());
	EXPECT_NO_THROW(ci.addFolder(TEST_IMG_FOLDER));
	EXPECT_NO_THROW(ci.addFolder(TEST_REAL_CAPS_FOLDR));
}
