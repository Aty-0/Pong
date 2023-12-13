#pragma once
#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <functional>
#include <memory>
#include <typeindex>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Singleton.h"

// TODO: Function will be better 
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = NULL; } }

#define SBT_ASSERT(a) if(!(a)) FATAL("Assertion failed %s\n File:%s\n Line:%d", #a, __FILE__, __LINE__); 