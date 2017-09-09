#include "TestConstants.h"

//Global variables definitions

void* gsi_items[] = {"first_gsi_item, second_gsi_item, third_gsi_item"};
gsi_item *local_gsi_itemP = &gsi_items[0];

void* arguments[] = {"first_argument", "second_argument"};

const char* gla_home_variable = getenv("GHLA_HOME");

const char* errorResult = 0;

bool createIsOk = true;
bool joinIsOk = true;
bool isErrorResult = false;
