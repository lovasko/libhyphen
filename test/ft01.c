// Copyright (c) 2018-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stdlib.h>
#include <inttypes.h>

#include "../hyphen.h"


/// Storage structure for the command-line interface.
struct storage {
  uint64_t st_vrb; ///< Verbose flag.
  uint64_t st_rcv; ///< Recursive flag.
};

/// Test of a single non-repeatable short flag.
int
main(void)
{
  hyphen cli;
  struct storage st;
  int ret;
  int argc;
  char* argv[3];
  uint64_t root;
  char* estr;

  // Prepare the artificial command-line.
  argv[0] = "ft01";
  argv[1] = "-v";
  argc    = 2;

  // Prepare the storage structure.
  st.st_vrb = 0;
  st.st_rcv = 0;

  // Reset the interface.
  ret = hyphen_rst(&cli);
  if (ret != HYPHEN_OK) {
    hyphen_err(&cli, ret, &estr);
    printf("reseting the interface failed: %s\n", estr);
    return EXIT_FAILURE;
  }

  // Create a root command.
  ret = hyphen_cmd(&cli, &root, 0, "ft01", &st, sizeof(st), "Flag test 01");
  if (ret != HYPHEN_OK) {
    hyphen_err(&cli, ret, &estr);
    printf("creating a root command failed: %s\n", estr);
    return EXIT_FAILURE;
  }

  // Add a short non-repeatable flag.
  ret = hyphen_flg(&cli, root, 'v', NULL, 1, 1, "Increase output verbosity");
  if (ret != HYPHEN_OK) {
    hyphen_err(&cli, ret, &estr);
    printf("attaching a flag failed: %s\n", estr);
    return EXIT_FAILURE;
  }

  // Skip the following flag.
  ret = hyphen_pad(&cli, root, sizeof(uint64_t));
  if (ret != HYPHEN_OK) {
    hyphen_err(&cli, ret, &estr);
    printf("adding padding failed: %s\n", estr);
    return EXIT_FAILURE;
  }

  // Parse the command-line.
  ret = hyphen_run(&cli, root, argc, argv);
  if (ret != HYPHEN_OK) {
    hyphen_err(&cli, ret, &estr);
    printf("parsing command-line failed: %s\n", estr);
    return EXIT_FAILURE;
  }

  // Verify the value in the storage structure.
  if (st.st_verbose == 0 || st.st_recursive > 0) {
    printf("expected 'st_vrb' = 1, 'st_rcv' = 0\n");
    printf("actual   'st_vrb' = %" PRIu64 ", 'st_rcv' = %" PRIu64 "\n",
      st.st_vrb, st.st_rcv);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
