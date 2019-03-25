#!/usr/bin/perl

use strict;
use File::Basename qw/basename dirname/;

my $out;
my %included = ();

my $in_file = $ARGV[0];
my $out_file = $ARGV[1];
my $include_path = $ARGV[2];

open($out, '>' , "$out_file");
include_file($in_file);
close($out);

sub include_file
{
	my $file = $_[0];
	return if defined $included{$file};
	
	open(my $f, '<' , $file) or die "Can't open $_[0]";
	
	my $skip = 1;
	while (<$f>)
	{
		$skip = 0 if m{^\s*#};
		next if $skip;
		
		next if m{^\s*#pragma};
		next if m{^\s*//};

		if (/^\s*#include "(.+)"/)
		{
			my $include_file = $1;
			my $include = dirname($file) . "/$include_file";
			if (-e $include)
			{
				include_file($include);
			} elsif (-e "$include_path/$include_file")
			{
				include_file("$include_path/$include_file");
			}
		}
		else	
		{
			s/(?<=\d)\'(?=\d)//g;
			print $out "$_";
		}
	}
	print $out "\n";
	close($f);
	
	$included{$file} = 1;
}
