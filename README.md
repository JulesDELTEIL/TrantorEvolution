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