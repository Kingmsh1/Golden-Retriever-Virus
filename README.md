# Golden-Retriever-Test-Virus
My exploration into malware development using the C programming language - making a Trojan virus.

**This project was for educational purposes only. I do not condone malware development in an effort to cause harm. This virus was not, and will not, be used as a tool of attack. I do not accept any liability for use and/or abuse of my virus code or any other part of my project by anyone else, apart from myself. If you intend to study this virus, do so legally and carefully and in an isolated, sandbox-style environment.**

## Author
Maahir Shah

## Overview
This project was an experiment to explore how hackers develop malware in an effort to understand malware behaviour, structure and evasion techniques.

I learned C and malware development practices in order to create this virus, which gave me an improved understanding of low-level programming and how it can be exploited for malicious purposes. 

I am fascinated by Red Team operations and how malicious applications/individuals can stay hidden from security systems, leading me to pursue this project for a greater understanding.

This virus is my first attempt at malware development and so it isn't the strongest virus out there. It's not meant to be either. This whole project was intended to be proof-of-concept and educational, rather than focusing on refining the virus to be potent.

## What the Virus Does
The virus is programmed to target Windows systems. It performs 4 different phases of attack:

#### 1. Launching on Startup
The virus modifies the Windows Registry to write its application file path to a value in the "HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run" key path.

This ensures that the virus is activated when the computer turns on for any user. This can be further modified, if a hypothetical attacker so wished, to execute particular instructions within the virus on startup.

#### 2. Disable User Access Control (UAC)
Disable UAC prevents Windows from opening the dialogue that confirms with the user whether they intend to elevate privileges. This allows for malicious programs to run silently without confirmed administrator approval.

#### 3. Disable Installer Detection
This prevents Windows from detecting and prompting for elevation when installing applications that require administrative privileges. This can be particularly useful when installing more malicious application in later phases of attack.

#### 4. Creating a New Administrative Use through Invoking CMD
The C program for the virus utilises the system() function to execute CMD commands through the C program in a separate session. This allows the virus to execute CMD commands to create a new user with administrative privileges on the machine without notifying the user, allowing the attacker a privileged backdoor for future attack. This phase assumes the user being targeted has administrative privileges.

## Evasion Technique
The virus aims to evade suspicion by being concealed as an image file of a Golden Retriever dog (hence the name of the virus). An unsuspecting user, who hasn't enabled the "Show File Extensions" option in their Windows File Explorer, may open the file which would display an image of a Golden Retriever whilst the malicious program runs in the background without notifying them.

## Assumptions
1. The user being targeted has administrative privileges (to allow for another admin user to be created in phase 4).
2. The user being targeted doesn't have "Show File Extensions" enabled in their File Explorer (the majority of Windows users don't), which would increase the likelihood of suspicion.
3. Windows Defender/AntiVirus is enabled and scanning.

