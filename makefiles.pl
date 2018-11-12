#!/usr/bin/perl

use strict;

# ----------------------------------------------------

my @dirs = split(/\n/, `find . -type d`);
for (@dirs)
{
	my $dir = $_;
	my $rel_dir = $dir;
	$rel_dir =~ s{^\./}{};
	$rel_dir =~ s{[^/]+}{..}g;

	my @cpp_files = glob("$dir/*.cpp");
	next unless @cpp_files > 0;
	
	system("chmod 644 $dir/*.cpp");
	open(my $makefile, ">$dir/Makefile");

	print $makefile "CXX = g++-7.1.0\n";
	print $makefile "#CFLAGS = -Wall -std=c++17 -O0 -ggdb -D_DEBUG -I$rel_dir\n";
	print $makefile "CFLAGS = -Wall -std=c++17 -O2 -DNDEBUG -I$rel_dir\n";

	print $makefile "GEN = $rel_dir/generate.pl\n";

	print $makefile "\n";
	print $makefile 'SRCS = $(wildcard *.cpp)' . "\n";
	print $makefile 'PROGS = $(patsubst %.cpp,%,$(SRCS))' . "\n";
	print $makefile 'OUTS = $(patsubst %.cpp,%.out,$(SRCS))' . "\n";
	print $makefile "\n";

	print $makefile 'all: $(PROGS)' . "\n";
	print $makefile "\n";

	print $makefile 'out: $(OUTS)' . "\n";
	print $makefile "\n";

	print $makefile "%: %.cpp\n";
    print $makefile "\t" . '$(CXX) $(CFLAGS) -o $@ $<' . "\n";
	print $makefile "\n";

	print $makefile "%.out: %.cpp\n";
    print $makefile "\t" . '$(GEN) $<' . "\n";
	print $makefile "\n";

	print $makefile "clean:\n";
    print $makefile "\t" . 'rm -f $(PROGS)' . "\n";
    print $makefile "\t" . 'rm -f $(OUTS)' . "\n";

	close($makefile);
	
#	system("make -C $dir all out");
}