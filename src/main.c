/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:47:16 by zramahaz          #+#    #+#             */
/*   Updated: 2024/09/03 15:56:05 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

/*definir le prompt*/
#define PROMPT "MyShell> "

void    execute_command(char *cmdline)
{
    
}

int main(int argc, char **argv)
{
    char    *cmdline;

    cmdline = NULL;
    while (42)
    {
        //  pour afficher un texte qui indique que le terminale
        //  est pret a recevoir une commande
        cmdline = readline(PROMPT);
        
        //  gestion d'erreur car readline utilise Malloc 
        if (cmdline == NULL)
        {
            perror("readline error");
            exit(EXIT_FAILURE);
        }

        // Si la cmdline existe, on l'ajoute au historique et
        // execute cette fonction execute_command
        if (*cmdline != '\0')
        {
            add_history(cmdline);
            execute_command(cmdline);
        }
        
        // A la fin, on libere cmdline
        free(cmdline);
    }
    return (0);
}




// #define PROMPT "MyShell> "

// void execute_command(char *cmdline) {
//     pid_t pid, wpid;
//     int status;

//     if ((pid = fork()) == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid == 0) { // Processus fils
//         char *argv[] = {"/bin/sh", "-c", cmdline, NULL};
//         execvp(argv[0], argv);
//         perror("execvp"); // Si execvp échoue
//         exit(EXIT_FAILURE);
//     } else { // Processus père
//         do {
//             wpid = waitpid(pid, &status, WUNTRACED);
//         } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//     }
// }