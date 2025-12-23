#pragma once

#ifdef DEBUG
  #define debugger __builtin_debugtrap()
#else
  #define debugger ((void)0)
#endif