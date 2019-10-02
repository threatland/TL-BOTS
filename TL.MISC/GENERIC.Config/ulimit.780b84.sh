#!/bin/bash
cd
echo -e 'Fixing The Ulimit'
ulimit -Hn 999999; ulimit -Sn 99999
echo -e 'ulimit -s 999999; ulimit -n 999999; ulimit -u 999999\n' > ~/.bashrc
ulimit -s 999999; ulimit -n 999999; ulimit -u 999999
sysctl -w fs.file-max=999999 >/dev/null
nano /etc/security/limits.conf