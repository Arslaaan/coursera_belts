#pragma once

#include <memory>
#include <iostream>
#include <map>

#include "node.h"

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);