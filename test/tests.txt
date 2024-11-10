/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spagliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:21:23 by spagliar          #+#    #+#             */
/*   Updated: 2024/10/07 13:21:24 by spagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//ECHO :
//-----------------------------------------------------------------------------

C	echo "hello"
T	hello
M	//OK

C	echo -n "hello"		//ok meme ligne
T	hello
M	//OK

C	echo "hello" "world"	
T	hello world	
M	//OK

C	echo $	
T    	$
M	//OK

C	echo -nn		
T	(rien)
M	//OK

C	echo ---n
T	---n
M	//OK

C    echo -n $			
R    $

// $ :
//-----------------------------------------------------------------------------

C	echo $?+$?
T	0+0
M	//OK

C	echo $USER                        
T	Affiche la valeur de la variable d'environnement USER -> spagliar
M

C	echo $?                          //ok affiche le code retour de la derniere commande
T	Affiche le code de retour de la dernière commande.
M	
    
C	echo $NONEXISTANT               //ok chaine vide + code de retour et mess d erreur
T	Si la variable d'environnement n'existe pas, afficher une chaîne vide ou ignorer cet argument.
M





//REDIRECTION :
//-------------

C   echo "hello" < test1.txt          //Erreur ouverture fichier d'entrée: No such file or directory
R   bash: test1.txt: No such file or directory //"hello" < test1.txt 

C   echo "hello" > test1.txt          //pas bon
R   ecrase les elements de test1 et remplace cf test1.txt 

C   echo "hello" >> test1.txt         //pas bon
R	laisse les elements et ajoute les nouveaux elements dans test1.txt //"hello" >> test1.txt 

C	 ls > output.txt
R	//cette fonction redirigerait la sortie de la commande ls vers le fichier output.txt au lieu de l'afficher sur l'écran.


//HEREDOC
//-------
C	ls | cat << END	//on utlise les fichiers listes par ls et on redirige ds une autres commande
Ajout	I HATE YOU //on ajoute le texte
Ajout	END //on ajoute le delimiteur
Affiche:I HATE YOU
//le fait de mettre un pipe permet de jouer avec les commandes
	
C	 cat < input.txt, 
R	//la fonction redirigerait l'entrée du fichier input.txt pour que cat lise ce fichier au lieu de lire les entrées du clavier.
C	echo "hello" >> log.txt
R	//la sortie serait ajoutée à la fin du fichier log.txt sans en effacer le contenu existant.


// controler le mode d ouverture des fichiers cf inout_files
//------------------------------------------------------------
- Creer un fichier txt avec une phrase
C echo "Première ligne" > fichier_test.txt
C echo "Ligne sans append" > fichier_test.txt
R : Résultat attendu : Le fichier fichier_test.txt ne devrait contenir que Ligne 
sans append, car le contenu précédent aura été écrasé.

- echo "Ligne avec append" >> fichier_test.txt
R : Résultat attendu : Le fichier fichier_test.txt devrait maintenant
 contenir les lignes suivantes : 
Ligne sans append
Ligne avec append


























/*
* check exit code

* check files perm

* test with tab and/or space and/or enter and/or "" and/or " "

* echo $USER$TESTNOTFOUND$HOME$WTF$PWD

* echo $/ $/ 

* export ___TEST=123

* export HELLO42=T=""

* export T=e E=c S=h L=o test="hey there"
* echo $T$E$S$L$test

* <<a<<"b"<<'c' cat -e|cat -e

* <a<"b"<'c' cat -e|cat -e

* ls|cat Makefile|cat<<'asd'>out

* ls|cat Makefile|cat<<"asd">out

* echo "cat lol.c | cat > lol.c"

* /bin/cat file | /bin/grep bla | more

* <Makefile cat -e| echo hello|cat -e 

* echo hellooo>out|<Makefile cat -e|cat -e>out1>out2

* pwd|cat -e

* <Makefile env|cat -e

* <no_existing|<Makefile cat -e|cat -e

* <Makefile cat -e|<signal.c cat -e >out|wc

* <no_existing|<no_existing2

* exit|exit

* cat >outfile -e<Makefile

* echo $?+$?

* cat -e<<end|cat -e|wc -l>out1

* export USER+=hello

* export salut coucou = bonsoir="hey" cmd="echo salut"
*/
