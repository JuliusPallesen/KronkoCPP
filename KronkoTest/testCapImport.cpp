#include "pch.h"

TEST(TestCapImport, TestNoFatalFailConstructor) {
	ColorPicker cp = ColorPoint();
	CapDB * db = new JsonDB("./db.json");
	EXPECT_NO_FATAL_FAILURE(CapImport ci = CapImport(db,&cp));
}

TEST(TestCapImport, TestNoThrowConstructor) {
	ColorPicker cp = ColorPoint();
	CapDB* db = new JsonDB("./db.json");
	EXPECT_NO_THROW(CapImport ci = CapImport(db, &cp));
}

TEST(TestCapImport, TestNo) {
	ColorPicker cp = ColorPoint();
	CapDB* db = new JsonDB("./db.json");
	CapImport ci = CapImport(db, &cp);
	EXPECT_NO_THROW(ci.addFolder(TEST_IMG_FOLDER));
	EXPECT_NO_THROW(ci.addFolder(TEST_REAL_CAPS_FOLDR));
}
