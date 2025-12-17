#pragma once

#ifdef DEBUG
  #define DEBUG_BREAK() __builtin_debugtrap()
#else
  #define DEBUG_BREAK() ((void)0)
#endif