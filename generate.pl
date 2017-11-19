#!/usr/bin/perl

use strict;

my $out;

for my $file ($ARGV[0])
{
	open($out, '>' , "$file.out");
	include_file($file);	
	close($out);
}

sub include_file
{
	open(my $f, '<' , $_[0]) or die "Can't open $_[0]";
	while (<$f>)
	{
		next if m{^\s*#pragma};
		next if m{^\s*//};

		if (/^\s*#include "(.+)"/)
		{
			my $include = $1;
			if (-e $include)
			{
				include_file($include);
			}
			elsif (-e "../$include")
			{
				include_file("../$include");
			}
			elsif (-e "../../$include")
			{
				include_file("../../$include");
			}
		}
		else	
		{
			print $out "$_";
		}
	}
	print $out "\n";
	close($f);
}
