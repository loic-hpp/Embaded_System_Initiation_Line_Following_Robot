# INF1900_embaded_system_initiation
Initial project at the second semester at Polytechnic Montreal

                                    +------------+----------------+------------+
                                    |       PROJET FINAL D'INF1900 RÉALISÉ PAR |
                                    | - Arman Lidder                           |
                                    | - Hamza Boukaftane                       |
                                    | - Jonathan Arrobas-Gilbert               |
                                    | - Loïc Nguemegne                         |
                                    +------------+----------------+------------+

Ce projet a a pour but d'effectuer un parcous à l'aide d'un robot suiveur de ligne.
Le parcous est subdivisé est 3 départs différent A, B et S.
Pour réaliser ce projet nous avons subdiviser notre code en 2 parties:
    - Un dossier app contenat le fichier main.cpp responsable de la mise en route de notre application.
    - Un dossier lib contenant une bibliothèque de toutes les fonctions nécessaires au projet.

Ci-dessous nous présenterons les classes et fonctions principales du projet ainsi que le mode de fonctionnement:
    * La classe Motor utilisée pour faire fonctionner les 2 moteurs il faudra se référer à la documentation
      pour les branchements.   
    * la classe Timer permet de chronométrer jusqu'à 8 secondes pour effectuer des actions en parallèle.
    * La fonction FollowLineTrajetA qui contient toute la logique pour effectuer la portion de trajet A.
    * La fonction FollowLineTrajetB qui contient toute la logique pour effectuer la portion de trajet B.
    * La fonction targetSVisitor qui contient toute la logique pour effectuer la portion de trajet S.
    * La fonction selectRoute qui contient la machine à états implémentée pour le choix de la portion de parcours 

Important: Veuillez prendre note ques les seuls messages d'erreur présents à la compilation de la librairie
sont dûs à la classe mémoire qui nous a été fournie. 

Ces fonctions ont été implémentées de manière à être réutilisables pour d'autres projets.
Pour toutes questions vous pouvez vous référer aux membres d'équipe déclarés ci-haut.
