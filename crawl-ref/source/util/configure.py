#!/usr/bin/env python3

"""
Works with both Python 2 & 3. If that changes, update how the Makefile calls
this.
"""

from subprocess import Popen, PIPE

import os
import shlex
import sys

if len(sys.argv) < 2:
    sys.stderr.write('CXX not specified\n')
    sys.exit(1)

# Not just the name of the compiler, it can have arguments to
CXX = sys.argv[1]
command = shlex.split(CXX) + ['-c', 'conftest.cc']

out = open('conftest.cc', 'w')
out.write("""
#include <unistd.h>
int main()
{
    fdatasync(1);
    return 0;
}
""")
out.close()

process = Popen(command, stdout=PIPE, stderr=PIPE)
(output, err) = process.communicate()
exit_code = process.wait()
FDATASYNC = "#define CRAWL_HAVE_FDATASYNC" if exit_code == 0 else "#undef CRAWL_HAVE_FDATASYNC"

out = open('conftest.cc', 'w')
out.write("""
#include <cstring>
using namespace std;
int main()
{
    const char *src = "hello";
    char dst[10];
    strlcpy(dst, src, sizeof(dst));
    return 0;
}
""")
out.close()

process = Popen(command, stdout=PIPE, stderr=PIPE)
(output, err) = process.communicate()
exit_code = process.wait()
STRLCPY = "#define CRAWL_HAVE_STRLCPY" if exit_code == 0 else "#undef CRAWL_HAVE_STRLCPY"

out = open('conftest.cc', 'w')
out.write("""
#include <cstdlib>
using namespace std;
int main()
{
    char file[] = "XXXXXX";
    mkstemp(file);
    return 0;
}
""")
out.close()

process = Popen(command, stdout=PIPE, stderr=PIPE)
(output, err) = process.communicate()
exit_code = process.wait()
MKSTEMP = "#define CRAWL_HAVE_MKSTEMP" if exit_code == 0 else "#undef CRAWL_HAVE_MKSTEMP"

out = open('conftest.cc', 'w')
out.write("""
#include <unistd.h>
int main()
{
    usleep(0);
    return 0;
}
""")
out.close()

process = Popen(command, stdout=PIPE, stderr=PIPE)
(output, err) = process.communicate()
exit_code = process.wait()
USLEEP = "#define CRAWL_HAVE_USLEEP" if exit_code == 0 else "#undef CRAWL_HAVE_USLEEP"

try:
    os.remove('conftest.cc')
except OSError:
    pass

try:
    os.remove('conftest.o')
except OSError:
    pass

try:
    os.remove('conftest.obj')
except OSError:
    pass

output_contents = """#pragma once

// Generated by util/configure.py

"""
output_contents += FDATASYNC
output_contents += '\n'
output_contents += STRLCPY
output_contents += '\n'
output_contents += MKSTEMP
output_contents += '\n'
output_contents += USLEEP
output_contents += '\n'

contents_match = False
try:
    config_file = open('config.h', 'r')
    current_contents = config_file.read()
    config_file.close()
    contents_match = current_contents == output_contents
except OSError:
    pass

if not contents_match:
    out = open('config.h', 'w')
    out.write(output_contents)
    out.close()
