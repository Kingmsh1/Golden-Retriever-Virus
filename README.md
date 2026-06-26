# Golden Retriever Virus
My exploration into malware development using the C programming language - making a Trojan virus.

**This project was for educational purposes only. I do not condone malware development in an effort to cause harm. This virus was not, and will not, be used as a tool of attack. I do not accept any liability for use and/or abuse of my virus code or any other part of my project by anyone else, apart from myself. If you intend to study this virus, do so legally and carefully and in an isolated, sandbox-style environment.**

## Author
Maahir Shah

## Overview
This project was an experiment to explore how hackers develop malware in an effort to understand malware behaviour, structure and evasion techniques.

I learned C and malware development practices in order to create this virus, which gave me an improved understanding of low-level programming and and Windows Registry can be exploited for malicious purposes. 

I am fascinated by Red Team operations and how malicious applications/individuals can stay hidden from security systems, leading me to pursue this project for a greater understanding.

This virus is my first attempt at malware development and so it isn't the strongest virus out there. It's not meant to be either. This whole project was intended to be proof-of-concept and educational, rather than focusing on refining the virus to be potent.

## What the Virus Does
The virus is programmed to target Windows systems. It performs 4 different phases of attack:

#### 1. Launching on Startup
The virus modifies the Windows Registry to write its application file path to a value in the "HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run" key path.

This ensures that the virus is activated when the computer turns on for any user. This can be further modified, if a hypothetical attacker so wished, to execute particular instructions within the virus on startup.

#### 2. Disable User Access Control (UAC)
Disable UAC prevents Windows from opening the dialogue that confirms with the user whether they intend to elevate privileges. This allows for malicious programs to run silently without confirmed administrator approval.

It does this by editing the values of "ConsentPromptBehaviorAdmin" from 5 to 0 and "EnableLUA" from 1 to 0 in the key path "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System".

#### 3. Disable Installer Detection
This prevents Windows from detecting and prompting for elevation when installing applications that require administrative privileges. This can be particularly useful when installing more malicious application in later phases of attack.

It does this by editing the value of "EnableInstallerDetection" from 1 to 0 in the key path "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System".

#### 4. Creating a New Administrative Use through Invoking CMD
The C program for the virus utilises the system() function to execute CMD commands through the C program in a separate session. This allows the virus to execute CMD commands to create a new user with administrative privileges on the machine without notifying the user, allowing the attacker a privileged backdoor for future attack. This phase assumes the user being targeted has administrative privileges.

## Evasion Technique
The virus aims to evade suspicion by being concealed as an image file of a Golden Retriever dog (hence the name of the virus). An unsuspecting user, who hasn't enabled the "Show File Extensions" option in their Windows File Explorer, may open the file which would display an image of a Golden Retriever whilst the malicious program runs in the background without notifying them.

## Assumptions
1. The user being targeted has administrative privileges (to allow for another admin user to be created in phase 4).
2. The user being targeted doesn't have "Show File Extensions" enabled in their File Explorer (the majority of Windows users don't), which would increase the likelihood of suspicion.
3. Windows Defender/AntiVirus is disabled and not scanning.

## Detection Engineering & Blue-Team Analysis
To extend this malware dev project and understand how my virus would be detected in a real-world environment, I mapped its behaviour to techniques documented in the MITRE ATT&CK Framework. I then mapped each behaviour to Sysmon (more-detailed Windows system activity logger) Event IDs and used both mappings to write Sigma detection rules as YAML files to simulate SOC monitoring of malware behaviour.

***

# Golden Retriever Virus Behaviour -> MITRE ATT&CK Technique ID Mapping -> Sysmon Event ID Mapping -> Detection Goal
### Persistence via Registry Run Key
- TechniqueID: T1547.001 (Boot or Logon Autostart Execution: Registry Run Keys)
- Sysmon EventIDs: 12 (Registry key creation), 13 (Registry value set)
- Detection Goal: identify malware persistence via Run key modification to run on start-up
### UAC Disabling 
- TechniqueID: T1112 (Modify Registry)
- Sysmon EventID: 13 (Registry value set)
- Detection Goal: detect attempts to disable Windows security prompts by weakening UAC protection
### Installer Detection Disabling
- TechniqueID: T1112 (Modify Registry)
- Sysmon EventID: 13 (Registry value set)
- Detection Goal: detect attempts to disable Windows security prompts by suppressing Windows Installer elevation prompts
### CMD Command Execution for Local Account Creation
- TechniqueID: T1059.003 (Command and Scripting Interpreter: Windows Command Shell), T1136.001 (Create Local Account)
- Sysmon EventID: 1 (Process Creation)
- Detection Goal: detect usage of cmd.exe for local account creation for persistence
### Privilege Escalation via Local Admin Group Modification
- TechniqueID: T1059.003 (Command and Scripting Interpreter: Windows Command Shell), T1136.001 (Create Local Account)
- Sysmon EventID: 1 (Process Creation)
- Detection Goal: detect addition of local accounts to the local administrators group for persistence with elevated privileges

***

# Lessons
Overall, my malware development project and learning to construct Sigma detection rules helped me understand:
- how malware behaves
- why Windows Registry can be an important target for adversaries
- defence evasion techniques
- how WindowsOS can log activity
- how malware behaviour can be translated into detection rules
- MITRE ATT&CK framework mapping of malware behaviour
- the importance of Sigma rules and Sigma's flexibility as a cross-platform detection engineering tool

# Project Artefacts
1. The virus itself called "goldenretriever.exe" within the Virus folder.
2. The virus source code in C within the Virus folder.
3. Sigma YAML rule files.
4. My personal notes on malware development in C made during my C learning journey.
5. My personal notes on the MITRE ATT&CK Framework, Sysmon and Sigma rule-writing.

