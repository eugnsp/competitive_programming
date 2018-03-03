#!/usr/bin/perl

use strict;

my $out;
my %included = ();

for my $file ($ARGV[0])
{
	my $out_file = $file;
	$out_file =~ s/cpp$/out/;
	open($out, '>' , "$out_file");
	include_file($file);	
	close($out);
}

sub include_file
{
	my $file = $_[0];
	return if defined $included{$file};
	
	open(my $f, '<' , $file) or die "Can't open $_[0]";
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
	
	$included{$file} = 1;
}
