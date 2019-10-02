## Etymology: QBOT / P2P / BASHLITE

Sources categorized under TL.P2P/P2P.* are from an older set of files that were then organized. 
The sources categorized under QBOT.* are similar in many ways to the P2P sources. 

They both trace origins back to the BASHLITE family of malware, originally authored by 
LizardSquad for DDoS purposes. BASHLITE could also be found under the names Gafgyt, 
Lizkebab, Qbot, Torlus and LizardStresser, among many others.

The original version of these was written to exploit the ShellShock vulnerability in 
embedded Linux devices running BusyBox around 2014. After the source was leaked, it caused 
endless variants of dubious quality to be be released, which is what you see here. 

One way to differentiate an older BASHLITE/P2P/QBOT source is by the use of the Ogre figlet
font in the comments to seperate the different sections of the source file. Example:

    //     ___      __ _
    //    /   \___ / _(_)_ __   ___  ___
    //   / /\ / _ \ |_| | '_ \ / _ \/ __|
    //  / /_//  __/  _| | | | |  __/\__ \
    // /___,' \___|_| |_|_| |_|\___||___/

A near universal feature of these bots is the use of a Multiply-with-carry PRNG based on the constant PHI:

    #define PHI 0x9e3779b9

This can be used as a signature for identification, summarized by these yara rules.

    rule phiLE : QBOT {
    meta:
      Author = "u"
      Description = "Checks for PHI-based PRNG - Little Endian"
    strings:
      $phi0 = {b9 79 37 9e}
    condition:
      $phi0
    }
    rule phiBE : QBOT {
    meta:
      Author = "u"
      Description = "Checks for PHI-based PRNG - Big Endian"
    strings:
      $phi0 = {9e 37 79 b9}
    condition:
      $phi0
    }

Important Note: The term QBOT in this context is different from the QBOT or QAKBOT 
banking malware, which has been around for many years prior to these sources. 

## Etymology: MIRAI 

Mirai first appeared in August 2016 and has been covered extensively by numerous outlets. 
The collection of Mirai variants here represents a similar development pattern to the 
evolution of the BASHLITE/QBOT/P2P bots as detailed above.

While a good number of elements are shared between current variants of QBOT and MIRAI,
a distinguishing feature of MIRAI is the command and control server structure that is 
written in Go and has a more streamlined method of managing tasks and bots. 

Since earlier IoT malware relied generally on having single source files to represent 
a server, a client, and a script to cross compile for different architectures, the 
codebase for Mirai is markedly more robust. The sources for bots in Mirai are generally 
still written in C, but there is a greater deal of organization of various modules, 
allowing for much more rapid extension of bot capabilities.

## Targets 

Modern MIRAI and QBOT sources target a core set of processor architectures used in IoT 
devices. They also use a very standard set of cross compilation tools and an easily 
configurable toolchain.

Table of targets 

* arm
* arm4
* arm5
* arm6
* arm7
* m68k
* mips
* mpsl
* ppc
* sh4
* spc
* x86
* x86_32
* x86_64

## Exploits 

The BASHLITE malware family originally exploited ShellShock, but in the years since, 
new exploits for embedded devices have inevitably appeared, leading to a much larger 
variety of exploits being deployed by a given botnet. 

Many of these are standard, publicly known exploits. In an attempt to appear to have 
an unknown or "private" exploit, some botnet owners attempt to sell modified versions 
of public exploits with very basic obfuscation in order to trick an inexperienced
malware author into purchasing it.

Some exploits are also backdoored themselves, containing tricks to add users to the C2 
and to the bots.

