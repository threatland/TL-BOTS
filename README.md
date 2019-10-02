# TL-BOTS #

Welcome to the TL-BOTS repo. This collection contains source files, tools, and
other components of a vast array of botnet families. The families covered here
range from 2014/2015 to the present day.

Files in this collection have been gathered via distributed trawling of the 
internet, and deduplicated where applicable.

## Disclaimer ##

The files contained in this repo are for research purposes only. They are 
provided as-is and have no guarantee of functionality.

## What is a botnet? ##

A botnet is a network of infected devices that contact a Command and Control 
Server (C2) to receive instructions for attacks. Botnets are used for many 
different purposes, including DDoS, fraud, and loading/spreading other malware.

## Mitigations ##

Mitigations vary from system to system, but the core security principles apply 
to each of them. Regular patching, network segmentation, and proper device 
configuration are crucial to maintaining the security of devices.

## Navigating the Repo ##

The repo is divided into several folders, containing specific categories of 
activity.

Zip files may have the same or similar names, so each filename contains an 
identifier based on the first 6 characters of the SHA1 hash of the file. 
The formula is:

    FILENAME.SHA1.EXTENSION

Non Zip files may contain this naming pattern as well.

## Collection Highlights ## 

Nearly every version of Mirai and QBot since the beginning of both of these 
malware families is contained in this repo. For more information about the 
origin of these malware families, check out HISTORY.md

## Researching This Collection ## 

This collection contains a vast number of botnets that have come and gone, 
and others that are still around in some form. While the bots themselves 
are steadily evolving, the core of many of them rely on exploiting whatever 
low hanging fruit is available at the time. A more detailed analysis of this 
collection, and resources to research further, is located in RESEARCH.md

## Contributing ## 

Contributions to this repo are welcome. Simply fork this repo, open a pull 
request and consult with the repo maintainers about it. 

### Guidelines ###

- Please submit larger files (> 5 MB) as a zip file in order to make cloning this a reasonable exercise.
- Please try and follow our naming convention for zip files in order to deduplicate and identify hashes. 

Files are subject to rejection if they do not meet our guidelines.

### We will NOT accept the following ###

- Combolists
- Database dumps
- Any credentials for active sites or devices, user, admin or otherwise

## Special Thanks ##

Special thanks goes to GreyNoise.io, who has catalogued nearly every exploit used 
in this collection. More information on using their tools to further research these 
botnets is located in RESEARCH.md
