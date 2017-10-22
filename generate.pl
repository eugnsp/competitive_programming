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
		next if m{\s*#pragma};
		next if m{\s*//};

		if (/^\s*#include "(.+)"/)
		{
			my $include = $1;
			include_file($include) if -e $include;			
			$include = "../$include";
			include_file($include) if -e $include;			
		}
		else	
		{
			print $out "$_";
		}
	}
	print $out "\n";
	close($f);
}
