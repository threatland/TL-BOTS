#!/bin/bash

clear
sleep 2
clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""
	echo -e "\x1b[31mFirst Name:\x1b[37m"
    read FN
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ " 
	echo -e ""
	echo -e "\x1b[31mMiddle Name:\x1b[37m"
	read MN
	clear
	echo -e ""	
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "
	echo -e ""
	echo -e "\x1b[31mLast Name:\x1b[37m"
	read LM
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "
	echo -e ""
	echo -e "\x1b[31mAddress:\x1b[37m"
	read AD
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "
	echo -e ""
	echo -e "\x1b[31mPhone Number:\x1b[37m"
	read PN
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""	
	echo -e "\x1b[31mAge:\x1b[37m"
	read AG
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""	
	echo -e "\x1b[31mCountry:\x1b[37m"
	read CT
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""	
	echo -e "\x1b[31mState:\x1b[37m"
	read ST
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""
	echo -e "\x1b[31mCity:\x1b[37m"
	read CY
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""	
	echo -e "\x1b[31mZip Code:\x1b[37m"
	read ZC
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""	
	echo -e "\x1b[31mAlias':\x1b[37m"
	read AS
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""	
	echo -e "\x1b[31mEmails:\x1b[37m"
	read ES
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""	
	echo -e "\x1b[31mSocial Media:\x1b[37m"
	read SM
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""
	echo -e "\x1b[31mISP INFO:\x1b[37m"
	read IS
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""
	echo -e "\x1b[31mExtra Information:\x1b[37m"
	read EX
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""
	echo -e "\x1b[31mDox Date:\x1b[37m"
	read DD
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""
	echo -e "\x1b[31mDox Reason:\x1b[37m"
	read DR
	clear
	echo -e ""
	echo -e " +-----------------------------------------------------------------------+ "
    echo -e " |                       Dox Organizer By DNS.DUMP                       |"
    echo -e " +-----------------------------------------------------------------------+ "                                                         
    echo -e ""
	echo -e "\x1b[31mDoxed By:\x1b[37m"
	read DB
    echo -e "PRESS ENTER TWICE!!!"
    read creator

    #######################################
    clear
    echo -e "\x1b[32mORGANIZING YOUR DOX MASTER!\x1b[37m"
echo -ne '[---                                         ] 12/100\r' 
sleep 0.5
echo -ne '[-------                                     ] 24/100\r'
sleep 0.5
echo -ne '[----------                                  ] 36/100\r'
sleep 0.5
echo -ne '[-------------                               ] 48/100\r'
sleep 0.5
echo -ne '[--------------------                        ] 60/100\r'
sleep 0.5
echo -ne '[--------------------------                  ] 72/100\r'
sleep 0.5
echo -ne '[------------------------------------        ] 84/100\r'
sleep 0.5
echo -ne '[------------------------------------------  ] 96/100\r'
sleep 0.5
echo -ne '[--------------------------------------------]'
echo -e '100/100 Dox Organized!\r'
echo -e "LINK: http://YOURIP/Dox.txt\r"
sleep 2.5
clear
echo -e "  "       >> Dox.txt
echo -e "          Dox Date: $DD"      >> Dox.txt
echo -e "         Dox Reason: $DR"     >> Dox.txt
echo -e "       Dox Dropped By: $DB"    >> Dox.txt
echo -e "-----------------------------"   >> Dox.txt
echo -e ""                             >> Dox.txt
echo -e "First Name: $FN"             >> Dox.txt  
echo -e "Middle Name: $MN"             >> Dox.txt  
echo -e "Last Name: $LM"             >> Dox.txt  
echo -e "Address: $AD"             >> Dox.txt  
echo -e "Phone Number: $PN"             >> Dox.txt  
echo -e "Age: $AG"             >> Dox.txt  
echo -e "Country: $CT"             >> Dox.txt
echo -e "State: $ST"             >> Dox.txt  
echo -e "City: $CY"             >> Dox.txt  
echo -e "Zip Code: $ZC"             >> Dox.txt  
echo -e "Alias': $AS"             >> Dox.txt
echo -e "Emails: $ES"             >> Dox.txt
echo -e "Social Media: $SM"             >> Dox.txt
echo -e "ISP INFO: $IS"             >> Dox.txt
echo -e "Extra Information: $EX"             >> Dox.txt

echo -e "----------------------------------------------" >> Dox.txt
echo -e "        Dox Organizer By DNS.DUMP" >> Dox.txt
