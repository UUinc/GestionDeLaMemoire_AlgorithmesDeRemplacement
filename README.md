# Gestion De La Memoire

### Algorithmes d'allocation memoire

Il y a défaut de page quand la page n'est pas en mémoire. Ainsi, on commence avec la mémoire vide, et à chaque "t", on charge la page en mémoire. Si la page n'existe pas encore en mémoire, alors il y a défaut de page puisqu'il faut charger la page.

* A la suite d'un defaut de page, le systeme d'exploitation doit ramener en memoire la page manquante a partir du disque.

* S'il n'y a pas de cadres libres en memoire, il doit retirer une page de la memoire pour la remplacer par celle demandee.

* Si la page a retirer a ete modifiee depuis son chargement en memoire, il faut la reecrire sur le disque.

### Program :
![Input](https://user-images.githubusercontent.com/63449913/158077627-fffe53c1-3521-4e9b-851d-d63d1b2370f0.JPG)
![Output](https://user-images.githubusercontent.com/63449913/158077641-d60556a0-fd08-4bf5-bce4-528b25c2c567.JPG)
