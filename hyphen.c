// Copyright (c) 2018-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "hyphen.h"


// Implementation limits.
#define HYPHEN_CMD_MAX     48 ///< Overall maximal number of commands.
#define HYPHEN_OPT_MAX     56 ///< Overall maximal number of options.
#define HYPHEN_FLG_MAX     56 ///< Overall maximal number of flags.
#define HYPHEN_ARG_MAX     32 ///< Overall maximal number of arguments.
#define HYPHEN_CMD_OPT_MAX 24 ///< Maximal number of options per command.
#define HYPHEN_CMD_FLG_MAX 24 ///< Maximal number of flags per command.
#define HYPHEN_CMD_ARG_MAX 16 ///< Maximal number of arguments per command.

// Function return codes.
#define HYPHEN_OK      1 ///< Success.
#define HYPHEN_E_NULL  2 ///< One or more function arguments were NULL.
#define HYPHEN_E_INPUT 3 ///< One or more function arguments were invalid.
#define HYPHEN_E_SIZE  4 ///< The storage structure size has overflown.

// Helper for padding.
#define PAD(n) (sizeof(void*) - (n))

/// Internal representation of a flag.
struct flg {
  char    fl_sht;         ///< Short name.
  uint8_t fl_max;         ///< Maximal number of repeated occurrences.
  uint8_t fl_pad[PAD(2)]; ///< Padding (unused).
  char*   fl_lng;         ///< Long name.
  char*   fl_hlp;         ///< Help text.
};

/// Internal representation of an option.
struct opt {
  char    op_sht;         ///< Short name.
  uint8_t op_max;         ///< Maximal number of repeated occurrences.
  uint8_t op_pad[PAD(2)]; ///< Padding (unused).
  char*   op_lng;         ///< Long name.
  char*   op_hlp;         ///< Help text.
  char*   op_var;         ///< Variable name.
};

/// Internal representation of an argument.
struct arg {
  uint8_t ar_min;         ///< Minimal number of repeated occurrences.
  uint8_t ar_max;         ///< Maximal number of repeated occurrences.
  uint8_t ar_pad[PAD(2)]; ///< Padding (unused).
  char*   ar_var;         ///< Variable name.
};

/// Internal representation of a command.
struct cmd {
  char*   cm_nam;                     ///< Name.
  uint8_t cm_flg[HYPHEN_CMD_FLG_MAX]; ///< Shared flag pool indices.
  uint8_t cm_opt[HYPHEN_CMD_OPT_MAX]; ///< Shared option pool indices.
  uint8_t cm_arg[HYPHEN_CMD_ARG_MAX]; ///< Shared argument pool indices.
  void*   cm_mem;                     ///< Storage structure memory.
  size_t  cm_siz;                     ///< Storage structure size.
  size_t  cm_off;                     ///< Current storage structure offset.
  uint8_t cm_nop;                     ///< Number of associated options.
  uint8_t cm_nfl;                     ///< Number of associated flags.
  uint8_t cm_nar;                     ///< Number of associated arguments.
  uint8_t cm_pad[PAD(3)];             ///< Padding (unused).
};

/// Command-line interface.
struct hyphen {
  struct cmd hy_cmd[HYPHEN_CMD_MAX]; ///< Shared command object pool.
  struct opt hy_opt[HYPHEN_OPT_MAX]; ///< Shared option object pool.
  struct flg hy_flg[HYPHEN_FLG_MAX]; ///< Shared flag object pool.
  struct arg hy_arg[HYPHEN_ARG_MAX]; ///< Shared argument object pool.
  uint8_t    hy_ncm;                 ///< Number of used commands.
  uint8_t    hy_nop;                 ///< Number of used options.
  uint8_t    hy_nfl;                 ///< Number of used flags.
  uint8_t    hy_nar;                 ///< Number of used arguments.
  uint32_t   hy_pad;                 ///< Padding (unused).
};

/// Verify that a option/flag name is valid.
/// @return decision
///
/// @param[in] str option/flag name
/// @param[in] len length of the name 
static bool
valid_name(const char* str, const size_t len)
{
  if ( 
}

/// Reset the command-line interface.
/// @return code
/// @retval HYPHEN_OK     success
/// @retval HYPHEN_E_NULL cli is NULL
///
/// @param[in] cli command-line interface
int8_t
hyphen_rst(hyphen* cli)
{
  uint16_t i;

  // Verify that the command-line interface is valid.
  if (cli == NULL)
    return HYPHEN_E_NULL;

  // Reset all values and pointers to zero.
  (void)memset(cli, 0, sizeof(*cli));

  return HYPHEN_OK;
}

/// Attach a new flag to the command.
/// @return code
/// @retval HYPHEN_OK      success
/// @retval HYPHEN_E_NULL  cli is NULL
/// @retval HYPHEN_E_NAME  sht and/or lng are invalid names
/// @retval HYPHEN_E_INPUT cid is an invalid command ID
/// @retval HYPHEN_E_COUNT no more flags can be added
///
/// @param[in] cli command-line interface
/// @param[in] cid command ID
/// @param[in] sht short name (can be NUL)
/// @param[in] lng long name (can be NULL)
/// @param[in] max maximal number of repeats
/// @param[in] hlp help text
int8_t
hyphen_flg(hyphen* cli,
           const uint16_t cid,
           const char sht,
           const char* lng,
           const uint64_t max,
           const char* hlp)
{
  struct cmd* c;
  struct flg* f;

  // Verify that the interface handle is valid.
  if (cli == NULL)
    return HYPHEN_E_NULL;

  // Verify that at least one of short/long names were provided.
  if (sht == '\0' && (lng == NULL || lng[0] == '\0'))
    return HYPHEN_E_NAME;

  // Verify that the short name is a valid character.
  if (sht != '\0') {
    retb = valid_name(&sht, 1);
    if (retb == false) {
      return HYPHEN_E_NAME;
    }
  }

  // Verify that the long name consists of only valid characters.
  if (lngn != NULL || lngn[0] == '\0') {
    retb = valid_name(lngn, strlen(lngn));
    if (retb == false) {
      return HYPHEN_E_NAME;
    }
  }

  // Verify that the command exists.
  if (cid >= cli->hy_ncm)
    return HYPHEN_E_INPUT;

  // Verify that more flags can be added to the interface.
  if (cli->hy_nfl >= HYPHEN_FLG_MAX)
    return HYPHEN_E_COUNT;

  // Verify that more flags can be added to the command.
  c = &cli->hy_cmd[cid];
  if (c->cm_nfl >= HYPHEN_CMD_FLG_MAX)
    return HYPHEN_E_COUNT;

  // Register the flag with the command.
  c->cm_flg[c->cm_nfl] = cli->hy_nfl;

  // Setup the new flag.
  f = &c->hy_flg[cli->hy_nfl];
  f->fl_sht = sht;
  f->fl_lng = lng;
  f->fl_hlp = hlp;
  f->fl_max = max;
  f->fl_mem = c->cm_mem + c->cm_off;

  // Advance the command-local and overall number of flags.
  cli->hy_nfl++;
  c->cm_nfl++;

  // Advance the storage offset of the storage object.
  c->cm_off += sizeof(uint64_t);

  return HYPHEN_OK;
}

/// Attach a command.
/// @return code
/// @retval HYPHEN_OK      success
/// @retval HYPHEN_E_NULL  cli and/or cid is NULL
/// @retval HYPHEN_E_NAME  the name is not valid
/// @retval HYPHEN_E_INPUT 
/// @retval HYPHEN_E_COUNT nd more commands can be added
///
/// @param[in]  cli
/// @param[out] cid
/// @param[in]  par
/// @param[in]  nam
/// @param[in]  mem
/// @param[in]  siz
/// @param[in]  hlp
uint8_t
hyphen_cmd(hyphen* cli,
           uint16_t* cid,
           const uint64_t par,
           const char* nam,
           void* mem,
           const size_t siz,
           const char* hlp)
{
  struct cmd* c;

  if (cli == NULL || cid == NULL || ptr == NULL)
    return HYPHEN_E_NULL;

  return HYPHEN_OK;
}

/// Skip a number of bytes in the storage structure.
/// @return code
/// @retval HYPHEN_OK
/// @retval HYPHEN_E_NULL
/// @retval HYPHEN_E_INPUT
///
/// @param[in] cli
/// @param[in] cid
/// @param[in] pad
int8_t
hyphen_pad(hyphen* cli,
           const uint16_t cid,
           const size_t pad)
{
  struct cmd* c;

  // Verify the pointer validity.
  if (cli == NULL)
    return HYPHEN_E_NULL;

  // Verify the validity of the pad.
  if (pad == 0)
    return HYPHEN_E_INPUT;

  // Find the relevant command.
  if (cid >= cli->cm_ncm)
    return HYPHEN_E_INPUT;

  // Verify that padding would not overflow the storage structure.
  c = &cli->hy_cmd[cid];
  if (c->cm_off + pad > c->cm_len)
    return HYPHEN_E_SIZE;

  // Move the structure offset.
  c->cm_off += pad;

  return HYPHEN_OK;
}

///
int8_t
hyphen_run(hyphen* cli, int argc, char* argv[])
{
  int64_t i;
  uint8_t st;

  // Traverse through all strings in the array.
  for (i = 0; i < argc; i++) {
    // Check if the argument is the 
  }

  return HYPHEN_OK;
}

/// 
///
/// @param[in] cli command-line interface
void
hyphen_err(hyphen* cli, int8_t ret, const char** str)
{
  
}
