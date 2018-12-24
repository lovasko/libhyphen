// Copyright (c) 2018 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "../hyphen.h"


/// Storage structure for the command-line interface.
struct storage {
  bool st_verbose;
};

/// Test of a single non-repeatable long flag.
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
  argv[0] = "ft02";
  argv[1] = "--verbose";
  argc    = 2;

  // Prepare the storage structure.
  st.st_verbose = false;

  // Create a root command.
  ret = hyphen_cmd(&cli, &root, 0, "ft02", &st, sizeof(st), "Flag test 02");
  if (ret != HYPHEN_OK) {
    hyphen_err(&cli, ret, &estr);
    printf("creating a root command failed: %s\n", estr);
    return EXIT_FAILURE;
  }

  // Add a short non-repeatable flag.
  ret = hyphen_flg(&cli, root, '\0', "verbose", 1, 1,
    "Increase output verbosity");
  if (ret != HYPHEN_OK) {
    hyphen_err(&cli, ret, &estr);
    printf("attaching a flag failed: %s\n", estr);
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
  if (st.st_verbose != true) {
    printf("expected st_verbose to be true\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
