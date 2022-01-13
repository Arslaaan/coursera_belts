#pragma once

#include <iostream>

#include "database.h"
#include "event_parser.h"
#include "condition_parser.h"

using namespace std;

void commandHandler(Database& db, istream& input_stream, ostream& output_stream);


