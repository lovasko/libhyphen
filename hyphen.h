// Copyright (c) 2018-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stddef.h>
#include <stdint.h>


/// Command-line interface.
typedef struct hyphen hyphen;

/// Create and (possibly) attach a new command.
uint8_t hyphen_cmd(
  hyphen* cli,         ///< Command-line interface.
  uint64_t* cid,       ///< New returned command ID.
  const uint64_t pcid, ///< Parent command ID to attach to (0 for no parent).
  const char* name,    ///< Name.
  void* ptr,           ///< Storage structure pointer.
  const size_t size,   ///< Storage structure size.
  const char* help     ///< Usage help text.
);

/// Create and attach a new option.
uint8_t hyphen_opt(
  hyphen* cli,         ///< Command-line interface.
  const uint64_t cid,  ///< Command ID to attach to.
  const char shtn,     ///< Short name (\0 for no short name).
  const char* lngn,    ///< Long name (NULL for no long name).
  const char* mvar,    ///< Meta variable name.
  const uint64_t rmin, ///< Minimal number of repeats.
  const uint64_t rmax, ///< Maximal number of repeats.
  const char* help     ///< Usage help text.
);

/// Create and attach a new flag.
uint8_t hyphen_flg(
  hyphen* cli,         ///< Command-line interface.
  const uint64_t cid,  ///< Command ID to attach to.
  const char shtn,     ///< Short name (\0 for no short name).
  const char* lngn,    ///< Long name (NULL for no long name).
  const uint64_t rmin, ///< Minimal number of repeats.
  const uint64_t rmax, ///< Maximal number of repeats.
  const char* help     ///< Usage help text.
);

/// Create and attach a new argument.
uint8_t hyphen_arg(
  hyphen* cli,         ///< Command-line interface.
  const uint64_t cid,  ///< Command ID to attach to.
  const char* name,    ///< Name.
  const uint64_t cnt,  ///< Number of repeats (UINT64_MAX for all remaining).
  const char* help     ///< Usage help text.
);

/// Skip a number of bytes in the storage structure.
uint8_t hyphen_pad(
  hyphen* cli,         ///< Command-line interface.
  const uint64_t cid,  ///< Command ID.
  const size_t size    ///< Number of bytes to skip.
);

/// Parse the command-line arguments. This function frees all memory allocated
/// the build functions.
uint8_t hyphen_run(
  hyphen* cli,         ///< Command-line interface.
  const uint64_t rcid, ///< Root command ID (name used as program name).
  const int argc,      ///< Argument count.
  const char* argv[],  ///< Argument vector.
  uint64_t* scid       ///< Selected command ID.
);

/// Convert an error code to an English description.
void hyphen_err(
  hyphen* cli,        ///< Command-line interface.
  const uint8_t code, ///< Function return/error code.
  const char** estr   ///< English description.
);
