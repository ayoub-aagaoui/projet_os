# Projet Systèmes d'Exploitation : Ordonnancement et Synchronisation

Ce dépôt contient un projet complet de Systèmes d'Exploitation (OS) réalisé en langage C. Il illustre deux concepts fondamentaux : l'ordonnancement de processus (CPU Scheduling) et la programmation concurrente/réseau (Client-Serveur avec gestion de ressources).

##  Architecture du Projet

Le projet est divisé en deux grandes parties indépendantes :

### Partie 1 : Simulateur d'Ordonnanceur CPU
Un programme qui simule l'allocation du processeur à différents processus selon trois politiques d'ordonnancement classiques :
*   **FIFO** (First In, First Out)
*   **SJF** (Shortest Job First - version non préemptive)
*   **Round-Robin** (Tourniquet avec un quantum défini)

**Fichiers associés :**
*   `politiques.h` : Définition de la structure `Processus` et signatures des algorithmes.
*   `main.c` / `politiques.c` : Lecture du fichier de configuration et exécution des algorithmes.

### Partie 2 : Gestion de Ressources Réseau (Client-Serveur)
Une simulation d'un environnement industriel où des "bras robotiques" (clients) demandent l'accès à des "outils" partagés gérés par un serveur central. 
*   **Serveur TCP** : Gère 10 outils partagés. Utilise des **Threads** pour écouter plusieurs clients simultanément et des **Mutex** 
*   **Client TCP** : Simule un bras robotique exécutant plusieurs tâches (réflexion, demande réseau, assemblage) de manière séquentielle grâce à `pthread_join`.

**Fichiers associés :**
*   `com.h` : Définition du protocole de communication (`TrameReseau`) et du port.
*   `serveur.c` : Code du serveur de ressources.
*   `client.c` : Code du client (bras robotique).

---

##  Concepts Techniques Abordés
*   **Langage :** C
*   **Gestion de la mémoire :** Allocation dynamique (`malloc`, `free`), structures de données.
*   **Programmation Système :** Lecture de fichiers texte, manipulation de l'horloge (`time.h`).
*   **Programmation Concurrente (POSIX) :** `pthread_create`, `pthread_join`, `pthread_detach`.
*   **Synchronisation :** Exclusion mutuelle avec `pthread_mutex_lock` / `pthread_unlock`.



### Prérequis
Assurez-vous d'avoir `gcc` installé sur votre machine (Linux/macOS). Pour la partie Client-Serveur, la bibliothèque `pthread` est requise.

### Compiler et lancer la Partie 1 (Ordonnanceur)
1. Créez un fichier `config.txt` contenant la liste des processus (Nom, Arrivée, Temps CPU).
   ```text
   P1 0 5
   P2 2 3
   P3 4 1
