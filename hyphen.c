// Copyright (c) 2018 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stddef.h>
#include <stdint.h>

#include "hyphen.h"


// Implementation limits.
#define HYPHEN_CMD_MAX     24 ///< Overall maximal number of commands.
#define HYPHEN_OPT_MAX     56 ///< Overall maximal number of options.
#define HYPHEN_FLG_MAX     56 ///< Overall maximal number of flags.
#define HYPHEN_ARG_MAX     32 ///< Overall maximal number of arguments.
#define HYPHEN_CMD_OPT_MAX 24 ///< Maximal number of options per command.
#define HYPHEN_CMD_FLG_MAX 24 ///< Maximal number of flags per command.
#define HYPHEN_CMD_ARG_MAX 16 ///< Maximal number of arguments per command.

// Function return codes.
#define HYPHEN_OK      0 ///< Success.
#define HYPHEN_E_NULL  1 ///< One or more function arguments were NULL.
#define HYPHEN_E_INPUT 2 ///< One or more function arguments were invalid.

// Helper for padding.
#define PAD(n) (sizeof(void*) - (n))

/// Internal representation of a flag.
struct flg {
  char    fl_shrt;         ///< Short name.
  uint8_t fl_rmax;         ///< Maximal number of repeated occurrences.
  uint8_t fl_upad[PAD(2)]; ///< Padding (unused).
  char*   fl_long;         ///< Long name.
  char*   fl_help;         ///< Help text.
};

/// Internal representation of an option.
struct opt {
  char    op_shrt;         ///< Short name.
  uint8_t op_rmax;         ///< Maximal number of repeated occurrences.
  uint8_t op_upad[PAD(2)]; ///< Padding (unused).
  char*   op_long;         ///< Long name.
  char*   op_help;         ///< Help text.
  char*   op_mvar;         ///< Meta variable name.
};

/// Internal representation of an argument.
struct arg {
  uint8_t ar_rmin;         ///< Minimal number of repeated occurrences.
  uint8_t ar_rmax;         ///< Maximal number of repeated occurrences.
  uint8_t ar_upad[PAD(2)]; ///< Padding (unused).
  char*   ar_mvar;         ///< Meta variable name.
};

/// Internal representation of a command.
struct cmd {
  char*   cm_name;                     ///< Name.
  uint8_t cm_flgs[HYPHEN_CMD_FLG_MAX]; ///< Shared flag pool indices.
  uint8_t cm_opts[HYPHEN_CMD_OPT_MAX]; ///< Shared option pool indices.
  uint8_t cm_args[HYPHEN_CMD_ARG_MAX]; ///< Shared argument pool indices.
  void*   cm_data;                     ///< Storage structure memory.
  size_t  cm_size;                     ///< Storage structure size.
};

/// Command-line interface.
struct hyphen {
  struct cmd hy_cmds[HYPHEN_CMD_MAX]; ///< Shared command object pool.
  struct opt hy_opts[HYPHEN_OPT_MAX]; ///< Shared option object pool.
  struct flg hy_flgs[HYPHEN_FLG_MAX]; ///< Shared flag object pool.
  struct arg hy_args[HYPHEN_ARG_MAX]; ///< Shared argument object pool.
};
