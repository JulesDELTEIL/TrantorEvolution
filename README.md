# TrantorEvolution

TrantorEvolution est un projet visant à simuler la vie sur une planète: `Trantor`.

## Sommaire

[1. Fonctionnement](#1-fonctionnement)

[2. Compilation](#2-compilation)

[3. Usage](#3-usage)

[4. Support](#4-support)

## 1. Fonctionnement

Ce projet contient 3 parties :
- **Intelligence artificielle** : simule un Trantorian sur la planète Trantor.
- **Interface graphique** : permet de visualiser en temps réel l’état de la partie, les joueurs, la carte, les ressources, etc.
- **Serveur** : héberge la partie et gère la logique du jeu, les connexions clients (intelligence artificielle et interface graphique), les ressources, le temps et les équipes.

Notre intelligence artificielle a pour principe de créer un *royaume* à partir d'une **reine**.
Cette reine va engendrer ensuite plusieurs autres IA aux **rôles précis** qui vont organiser ce royaume.
Ce fonctionnement permet de regrouper les ressources et de faire évoluer les IA rapidement.

**Rôles**

    Reine mère : engendre les reines, la matriarche et le maître ouvrier avant de devenir une simple reine.

    Reine : reste statique afin de récupérer les ressources acheminées pour évoluer.

    Matriarche : reste statique, engendre des kamikazes pour faire survivre le royaume.

    Kamikazes : reste statique, lâche sa nourriture initiale avant de mourir pour nourrir les autres IA.

    Maître Ouvrier : reste statique, engendre un maximum d'ouvriers pour faire évoluer les reines.

    Ouvriers : partent à la recherche de matériaux d'évolution pour les ramener aux reines.

**Cryptage et décryptage**

Les multiples IA d'une équipe communiquent entre elles secrètement via des **messages cryptés**.
Ces messages sont cryptés selon le nom de leurs équipes, qu'elles seules connaissent.

Cependant, un "Ouvrier" d'une équipe adversaire peut tenter de décrypter ces messages afin de perturber l'organisation
de cette équipe.

Ces ouvriers utilisent une méthode de "BruteForce" dans le but de décrypter ces messages grâce à un fichier de potentiels codes.
Si vous souhaitez que les IA puissent tenter de décrypter les messages des adversaires,
veuillez placer le fichier "rockyou.txt" à la racine du programme.

Lien de téléchargement de "rockyou.txt" :

https://www.kaggle.com/datasets/wjburns/common-password-list-rockyoutxt

## 2. Compilation

Pour compiler le projet, un script compile.sh est fourni à la racine du dépôt.
Il utilise CMake pour générer les Makefiles et compiler les trois exécutables :

    - zappy_server
    - zappy_gui
    - zappy_ai

Script de compilation :

```bash
./compile.sh [c] [d]
```

Options disponibles :

    -c : Nettoie le dossier avant compilation.

    -d : Compile en mode debug (utile pour valgrind).

**À noter !** Les deux flags ne peuvent pas être utilisé en même temps.

## 3. Usage

Ce projet contient trois exécutables distincts pour les 3 parties du projet.

### Serveur – zappy_server

Lancement :
```bash
./zappy_server -p <port> -x <width> -y <height> -n <team_name1> <team_name2> ... -c <clientsNb> -f <freq> [-d] [-b]
```

Paramètres :

    -p <port> : Port d’écoute du serveur.

    -x <width> : Largeur de la carte (max 100, min 5).

    -y <height> : Hauteur de la carte (max 100, min 5).

    -n <names> : Noms des équipes (au moins deux).

    -c <clientsNb> : Nombre maximum de clients autorisés par équipe (min 6 requis pour les incantations).

    -f <freq> : Fréquence d’exécution du serveur (ticks par seconde).

    -d (optionnel) : Active le mode debug.

    -b (optionnel) : Active le placement des ressources selon les biomes.

### GUI – zappy_gui

Lancement :
```bash
./zappy_gui -p <port> -h <machine>
```

Paramètres :

    -p <port> : Port sur lequel le serveur est accessible.

    -h <machine> : Adresse IP.

### IA – zappy_ai

Lancement :
```bash
./zappy_ai -p <port> -n <team_name> -h <machine>
```

Paramètres :

    -p <port> : Port du serveur.

    -n <team_name> : Nom de l’équipe à laquelle se connecter.

    -h <machine> : Adresse IP ou nom d’hôte du serveur.


## 4. Support

Au besoin, vous pouvez contacter les créateurs de ce projet :

* **Baptiste Dunes** _alias_ [@BaptiD](https://github.com/BaptiD)
* **Celian Raguin** _alias_ [@celianrag](https://github.com/celianrag)
* **Jules Delteil** _alias_ [@JulesDELTEIL](https://github.com/JulesDELTEIL)
* **Kerwan Calvier** _alias_ [@Kerwanc](https://github.com/Kerwanc)
* **Luigi Gomes** _alias_ [@Luigianiki](https://github.com/Luigianiki)
* **Pierre Pruvost** _alias_ [@PierrePruvost03](https://github.com/PierrePruvost03)
