#pragma once

#define REL_PTR(ptr) if(ptr) { delete (ptr); (ptr) = nullptr; }