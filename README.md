# TrantorEvolution

## Support

Au besoin, vous pouvez contacter les créateurs de ce projet :

* **Baptiste Dunes** _alias_ [@BaptiD](https://github.com/BaptiD)
* **Celian Raguin** _alias_ [@celianrag](https://github.com/celianrag)
* **Jules Delteil** _alias_ [@JulesDELTEIL](https://github.com/JulesDELTEIL)
* **Kerwan Calvier** _alias_ [@Kerwanc](https://github.com/Kerwanc)
* **Luigi Gomes** _alias_ [@Luigianiki](https://github.com/Luigianiki)
* **Pierre Pruvost** _alias_ [@PierrePruvost03](https://github.com/PierrePruvost03)

## Usage

Ce projet contient trois exécutables distincts :
un serveur, une interface graphique et une intelligence artificielle (IA).
Chaque binaire a un rôle précis dans le cadre du jeu distribué.

### Serveur – zappy_server

Le serveur héberge la partie et gère la logique du jeu, les connexions clients (IA et GUI), les ressources, le temps et les équipes.
Lancement :
```bash
./zappy_server -p <port> -x <width> -y <height> -n <team_name1> <team_name2> ... -c <clientsNb> -f <freq> [-d]
```

Paramètres :

    -p <port> : Port d’écoute du serveur.

    -x <width> : Largeur de la carte (max 100, min 5).

    -y <height> : Hauteur de la carte (max 100, min 5).

    -n <names> : Noms des équipes (au moins deux).

    -c <clientsNb> : Nombre maximum de clients autorisés par équipe (min 6 requis pour les incantations).

    -f <freq> : Fréquence d’exécution du serveur (ticks par seconde).

    -d (optionnel) : Active le mode debug.

### GUI – zappy_gui

L’interface graphique permet de visualiser en temps réel l’état de la partie, les joueurs, la carte, les ressources, etc.
Lancement :
```bash
./zappy_gui -p <port> -h <machine>
```

Paramètres :

    -p <port> : Port sur lequel le serveur est accessible.

    -h <machine> : Adresse IP.

### IA – zappy_ai

Ce binaire correspond au client contrôlé par une intelligence artificielle.
Lancement :
```bash
./zappy_ai -p <port> -n <team_name> -h <machine>
```

Paramètres :

    -p <port> : Port du serveur.

    -n <team_name> : Nom de l’équipe à laquelle se connecter.

    -h <machine> : Adresse IP ou nom d’hôte du serveur.

Fonctionnement :

L'IA de Zappy a pour principe de créer un royaume à partir d'une reine.
Cette reine va engendrer ensuite plusieurs autres IA aux rôles précis, qui vont organiser ce royaume.
Ce fonctionnement permet de regrouper les ressources et de faire évoluer les IA rapidement.

Rôles :

    Reine Mère : Engendre les reines, la matriarche et le maître ouvrier avant de devenir une simple reine.

    Reine : Reste statique afin de récupérer les ressources acheminées pour évoluer.

    Matriarche : Reste statique, engendre des kamikazes afin de nourrir les autres IA.

    Kamikazes : Reste statique, lâche sa nourriture initiale avant de mourir pour nourrir les autres IA.

    Maître Ouvrier : Reste statique, engendre un maximum d'ouvriers pour faire évoluer les reines.

    Ouvriers : Partent à la recherche de matériaux d'évolution pour les ramener aux reines.

Cryptage et Décryptage :

Les multiples IA d'une équipe communiquent entre eux secrètement via des messages cryptés.
Ces messages sont cryptés selon le nom de leurs équipes, qu'eux seuls connaissent.

Cependant un "Ouvrier" d'une équipe adversaire peut tenter de décrypter ces messages afin de perturber l'organisation
de cette équipe.

Ces ouvriers utilisent une méthode de "BruteForce" afin de décrypter ces messages grâce à un fichier de potentiels codes.
Si vous souhaitez que les IA puissent tenter de décrypter les messages des adversaires,
veuillez placer le fichier "rockyou.txt" à la racine du programme.

Lien de téléchargement de "rockyou.txt" :

https://www.kaggle.com/datasets/wjburns/common-password-list-rockyoutxt

## Compilation

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

À noter ! Les deux flags ne peuvent pas être utilisé en même temps nettoyer et re-compiler en debug.