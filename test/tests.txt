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
//----

C    echo "hello"                       // 2 lignes "hello"
R    hello

C    echo -n "hello"                    //ok meme ligne
R    hello

C    echo "hello" "world"               // 1 ligne "hello"
R    hello world                        // 1 ligne "hello" "world"

C    echo $                             //$ + 1 ligne
R    $

C    echo -nn                           //rien
R    (rien)

C    echo ---n                          //2lignes ---n
R    ---n

C    echo -n $                          //pas bon
R    $

C    echo $?+$?                         //pas bon
R    0+0

C   echo "hello" < test1.txt          //Erreur ouverture fichier d'entrée: No such file or directory
R   bash: test1.txt: No such file or directory //"hello" < test1.txt 

C   echo "hello" > test1.txt          //pas bon
R   ecrase les elements de test1 et remplace cf test1.txt 

C   echo "hello" >> test1.txt         //pas bon
R	laisse les elements et ajoute les nouveaux elements dans test1.txt //"hello" >> test1.txt 

C	echo $USER                        //OK affiche la veleur et aussi le code de retour 1 
R	Affiche la valeur de la variable d'environnement USER. //mess : Erreur ouverture fichier d'entrée: Bad address
    spagliar

C   echo $?                          //ok affiche le code retour de la derniere commande
R	Affiche le code de retour de la dernière commande. //mes : Erreur ouverture fichier d'entrée: Bad address
    0
    
C	echo $NONEXISTANT               //ok chaine vide + code de retour et mess d erreur
R	Si la variable d'environnement n'existe pas, afficher une chaîne vide ou ignorer cet argument.

//HEREDOC
//-------
C	ls | cat << END	//on utlise les fichiers listes par ls et on redirige ds une autres commande
Ajout	I HATE YOU //on ajoute le texte
Ajout	END //on ajoute le delimiteur
Affiche:I HATE YOU
//le fait de mettre un pipe permet de jouer avec les commandes


//export
//------









COMMANDES POUR GIT









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
