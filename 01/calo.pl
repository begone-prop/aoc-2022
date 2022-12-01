#!/usr/bin/perl

my $input_file = './input';

open(my $input_data, '<', $input_file);

my $current_sum = 0;
my $max = 0;

my @sums;
my $sum_idx = 0;

while(<$input_data>) {
    chomp $_;

    if($_ ne "") {
        $current_sum += int($_);
        next if not eof $input_data;
    }

    $sums[$sum_idx++] = $current_sum;
    $max = $current_sum if $current_sum > $max;
    $current_sum = 0;
}

@sorted_sums = sort { $b <=> $a } @sums;

my $idx = 0;
my $top_sum = 0;

while($idx < 3) {
    $top_sum += $sorted_sums[$idx];
    $idx++;
}

print "Answer for part 1 is $max\n";
print "Answer for part 2 is $top_sum\n";
