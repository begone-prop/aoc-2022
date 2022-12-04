#!/usr/bin/env perl

use strict;
use warnings;

my $input_file = './input';

open(my $input_data, '<', $input_file);

my $count = 0;
my $count2 = 0;

while(<$input_data>) {
    /(\d+)-(\d+),(\d+)-(\d+)/;
    $count++ if ($1 - $3) * ($2 - $4) <= 0;
    $count2++ if $3 <= $2 and $1 <= $4;
}

print "$count\n";
print "$count2\n";
