#include "pch.h"

TEST(TestCapImport, TestNoFatalFail) {
	ColorPicker cp = ColorPoint();
	CapDB * db = new JsonDB("./db.json");
	EXPECT_NO_FATAL_FAILURE(CapImport ci = CapImport(db,&cp));
}

TEST(TestCapImport, TestNoThrow) {
	ColorPicker cp = ColorPoint();
	CapDB* db = new JsonDB("./db.json");
	EXPECT_NO_THROW(CapImport ci = CapImport(db, &cp));
}

