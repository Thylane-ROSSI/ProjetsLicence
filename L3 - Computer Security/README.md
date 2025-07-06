# Labs de Cybersécurité – Toronto Metropolitan University 🇨🇦

Ce dépôt présente huit laboratoires pratiques réalisés durant mon échange universitaire à la Toronto Metropolitan University. Chaque lab m’a permis de manipuler directement des outils, attaques et mécanismes de défense en cybersécurité. Voici un aperçu de chaque lab :

---

### 1. Spectre Attack

**Objectif :** Comprendre et exploiter la vulnérabilité Spectre basée sur l'exécution spéculative des processeurs modernes.

**Tâches principales :**

* Manipulation de canaux auxiliaires via les caches (Flush+Reload).
* Déclenchement d'exécutions spéculatives pour contourner les protections mémoire.
* Extraction de secrets à l’aide d'effets résiduels dans les caches.

---

### 2. Secret-Key Encryption

**Objectif :** Apprendre les bases du chiffrement symétrique et les erreurs courantes.

**Tâches principales :**

* Fréquence d’analyse sur des textes chiffrés par substitution.
* Expériences avec différents modes de chiffrement (ECB, CBC, etc.).
* Étude de l’impact du padding, de la corruption et du choix d’IV.

---

### 3. Public-Key Infrastructure (PKI)

**Objectif :** Mettre en place une infrastructure PKI avec des certificats signés.

**Tâches principales :**

* Création d’une autorité de certification (CA).
* Génération et déploiement de certificats pour un site HTTPS.
* Simulation d’attaques Man-in-the-Middle (MITM) avec un CA compromis.

---

### 4. RSA Public-Key Cryptography

**Objectif :** Implémenter manuellement le chiffrement RSA, la signature et la vérification.

**Tâches principales :**

* Génération de clés RSA avec de grands nombres premiers.
* Chiffrement, déchiffrement, signature et validation de messages.
* Vérification manuelle de certificats X.509.

---

### 5. Buffer Overflow (Set-UID)

**Objectif :** Exploiter une faille de dépassement de tampon dans un programme Set-UID.

**Tâches principales :**

* Injection de shellcode pour obtenir un shell root.
* Dépassement de la pile pour écraser l’adresse de retour.
* Contournement de protections comme ASLR, StackGuard et exécution non autorisée.

---

### 6. Packet Sniffing & Spoofing

**Objectif :** Comprendre et implémenter l’interception et la falsification de paquets réseau.

**Tâches principales :**

* Sniffing de paquets avec Scapy et pcap.
* Spoofing ICMP, manipulation ARP, faux traceroute.
* Combinaison d’interception et réponse immédiate falsifiée.

---

### 7. VPN Tunneling

**Objectif :** Mettre en place un tunnel VPN simple basé sur les interfaces TUN/TAP.

**Tâches principales :**

* Création d'une interface virtuelle pour encapsuler les paquets IP.
* Routage du trafic réseau via un tunnel UDP.
* Transmission bidirectionnelle des paquets entre deux réseaux.

---

### 8. Firewall Evasion

**Objectif :** Contourner des règles de pare-feu via le tunneling et la redirection de ports.

**Tâches principales :**

* Tunneling statique et dynamique via SSH.
* Configuration d’un proxy SOCKS5 avec curl et Firefox.
* Création d’un VPN (SSH-based) pour contourner les filtrages d’entrée/sortie.

---

Chaque lab a été réalisé dans un environnement sécurisé (VM SEED), avec une approche « hands-on » pour renforcer ma compréhension des concepts de sécurité informatique.
Les comptes rendus et quelques scripts sont dans les sous-répertoires.


